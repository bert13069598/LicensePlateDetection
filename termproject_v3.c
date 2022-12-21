#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

static struct termios init_setting, new_setting;
char seg_num[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x90};
char seg_dnum[10] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x58, 0x00, 0x10};

#define D1 0x01
#define D2 0x02
#define D3 0x04
#define D4 0x08

void init_keyboard()
{

	tcgetattr(STDIN_FILENO, &init_setting);
	new_setting = init_setting;
	new_setting.c_lflag &= ~ICANON;
	new_setting.c_lflag &= ~ECHO;
	new_setting.c_cc[VMIN] = 0;
	new_setting.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &new_setting);
}

void close_keyboard()
{
	tcsetattr(0, TCSANOW, &init_setting);
}

char get_key()
{
	char ch = -1;

	if (read(STDIN_FILENO, &ch, 1) != 1)
		ch = -1;
	return ch;
}

void print_menu()
{
	printf("\n----------menu----------\n");
	printf("[i] : register a license\n");
	printf("[o] : print a license\n");
	printf("[c] : take a picture\n");
	printf("[d] : detect a license\n");
	printf("[r] : reset result folder\n");
	printf("[q] : program exit\n");
	printf("------------------------\n\n");
}

int main(int argc, char **argv)
{
	unsigned short data[4];
	char key;
	int tmp_n;
	int delay_time;

	int tmp_d;
	int tmp_d1, tmp_d2, tmp_d3, tmp_d4;

	int size=0;
	int *license = (int *)malloc(sizeof(int) * 5);

	int isSame = 0;
	int led_RG=0;

	int system (const char * string);

	char buff;
	char tmp;
	char prev = 'r';

	int dev_seg = open("/dev/my_segment", O_RDWR);
	int dev_gpio = open("/dev/my_gpio", O_RDWR);

	if (dev_seg == -1)
	{
		printf("Seg opening was not possible!\n");
		return -1;
	}
	if (dev_gpio == -1)
	{
		printf("Gpio opening was not possible!");
		return -1;
	}
	printf("device opening was successfull!\n");

	init_keyboard();
	print_menu();
	tmp_n = 0; // related to pos
	tmp_d = 0; // related to cnt
	char string[4];

	// delay_time = 500000;
	delay_time = 500;

	while (1)
	{
		tmp_d1 = tmp_d / 1000; // related to seg
		tmp_d2 = (tmp_d % 1000) / 100;
		tmp_d3 = (tmp_d % 100) / 10;
		tmp_d4 = tmp_d % 10;

		data[0] = (seg_num[tmp_d1] << 4) | D1;
		data[1] = (seg_num[tmp_d2] << 4) | D2;
		data[2] = (seg_num[tmp_d3] << 4) | D3;
		data[3] = (seg_num[tmp_d4] << 4) | D4;

		key = get_key();
		if (key == 'q')
		{
			printf("exit this program.\n");
			free(license);
			break;
		}
		if (key == 'r')
		{
			printf("reset result folder.\n");
			int reset = system("sudo rm -r ./results");
			isSame = 0;
		}
		else if (key == 'c')
		{
			
			int ret = system("raspistill -v -o test_license2.png");
			printf("take a picture!\n");
		}
		else if (key == 'd')
		{
			printf("detect a license\n");
			

			while (1){
				read(dev_gpio, &buff, 1);
				prev = tmp;
				tmp = buff;
				if (prev == '0' && tmp == '1'){

					//-------------------------------------crop plate
					int crop_plate = system("python3 TFLite_detection_image_license.py --modeldir= --labels=labelmap.txt --image=test_license2.png --save_results --noshow_results --graph=detect_plate.tflite");

					//-------------------------------------detect number
					int detect_number = system("python3 TFLite_detection_image.py --modeldir= --labels=labelmap2.txt --image=./results/test_license2_crop0.png --save_results --noshow_results --graph=detect_number2.tflite");
					
					printf("align!\n");
					//-------------------------------------algin number
					FILE* inputFile = NULL;
					char filename[] = "./results/test_license2_crop0.txt";

					inputFile = fopen(filename, "r");

					char* strs[7];
					int number[7];

					int kindex = 0;
					int temp[1][2] = { 0 };
					int resultNum = 0;
					int linecount = 0;
					char c;

					if (inputFile != NULL)
					{
						while (1)
						{
							char  buffer[1024];
							fgets(buffer, sizeof(buffer), inputFile);
							if (feof(inputFile))
								break; 

							linecount++;
						}
						fclose(inputFile);
					}
					int** dataNum;
					dataNum = (int**)calloc(linecount, sizeof(int*));
					for (int i = 0; i < linecount; i++)
					{
						dataNum[i] = (int*)calloc(2, sizeof(int));
					}

					inputFile = fopen(filename, "r");
					if (inputFile != NULL) {
						char  buffer[1024];

						// printf("linecount is %d\n", linecount);       
						while (1) {
							fgets(buffer, sizeof(buffer), inputFile);
							if (feof(inputFile))
								break; 


							char* ptr = strtok(buffer, " ,\n");
							while (ptr != NULL) {
								for (int i = 0; i < 7; i++) {

									strs[i] = ptr;
									ptr = strtok(NULL, " ");
								}
							}

							for (int i = 0; i < 7; i++) {
								number[2] = 0;
								if (i == 0 || i == 2) {

									// printf("strs : %c\n", *strs[i]);

									if (*strs[i] - 48 >= 0 && *strs[i] - 48 < 10)
									{
										number[i] = atoi(strs[i]);

									}
									else
									{
										number[0] = -1;

									}


									if (number[0] != -1 && number[2] != 0) {
										dataNum[kindex][0] = number[0];
										dataNum[kindex][1] = number[2];
									}
								}
								// printf("%d %d\n", number[0], number[2]);


							}
							// printf("count end\n");
							kindex++;
						}
					}

					printf("\n");

					for (int i = 0; i < linecount; i++)
						printf("%d %d\n", dataNum[i][0], dataNum[i][1]);
					// printf("count end!!!\n");
					printf("\n");

					for (int i = 0; i < linecount; i++) {
						for (int j = 0; j < (linecount - 1) - i; j++) {
							if (dataNum[j][1] > dataNum[j + 1][1]) {	
								temp[0][0] = dataNum[j][0];
								temp[0][1] = dataNum[j][1];

								dataNum[j][0] = dataNum[j + 1][0];
								dataNum[j][1] = dataNum[j + 1][1];

								dataNum[j + 1][0] = temp[0][0];
								dataNum[j + 1][1] = temp[0][1];

							}
						}
					}

					for (int i = 0; i < linecount; i++)
						printf("%d %d\n", dataNum[i][0], dataNum[i][1]);
					printf("\n");



					if (linecount >= 4)
					{
						resultNum = dataNum[linecount - 1][0] + 10 * dataNum[linecount - 2][0] + 100 * dataNum[linecount - 3][0] + 1000 * dataNum[linecount - 4][0];
					}

					else if (linecount == 3)
					{
						resultNum = dataNum[linecount - 1][0] + 10 * dataNum[linecount - 2][0] + 100 * dataNum[linecount - 3][0];
					}

					else if (linecount == 2)
					{
						resultNum = dataNum[linecount - 1][0] + 10 * dataNum[linecount - 2][0];
					}

					else if (linecount == 1)
					{
						resultNum = dataNum[linecount - 1][0];
					}

					else
						resultNum = 0;
				
					printf("detect num : %04d\n", resultNum);
					fclose(inputFile);

					//--------------------------------------compare resultNum with license
					for (int i=0; i<size; i++){
						if(license[i]==resultNum){
							isSame=1;
						}
							
					}

					

					//--------------------------------------led+servo
					if (isSame == 1)
						led_RG = system("python3 led_RG.py --isSame=1");
					else if (isSame == 0)
						led_RG = system("python3 led_RG.py --isSame=0");

					//--------------------------------------seg
					tmp_d = resultNum;






					break;
				}
			}
		}
		else if (key == 'o')
		{
			printf("print a license\n");
			for (int i = 0; i < size; i++)
				printf("plate[%d] : %04d\n", i + 1, license[i]);
			printf("\n");
		}
		else if (key == 'i')
		{
			printf("register a license\n");

			for (int i = 0; i < 4; i++)
			{
				while (1)
				{
					key = get_key();
					if (key == '0' || key == '1' || key == '2' || key == '3' || key == '4' ||
						key == '5' || key == '6' || key == '7' || key == '8' || key == '9')
					{
						string[i] = key;
						key = -1;
						break;
					}
				}
			}

			tmp_d1 = (int)string[0] - 48;
			tmp_d2 = (int)string[1] - 48;
			tmp_d3 = (int)string[2] - 48;
			tmp_d4 = (int)string[3] - 48;

			tmp_d = tmp_d1 * 1000 + tmp_d2 * 100 + tmp_d3 * 10 + tmp_d4;
			size++;
			license[size - 1] = tmp_d;
			printf("%04d registered!\n\n", tmp_d);
		}

		write(dev_seg, &data[tmp_n], 2);
		// write(dev_gpio, &data[tmp_n],2);
		usleep(delay_time);

		tmp_n++;
		if (tmp_n > 3)
		{
			tmp_n = 0;
		}
	}

	close_keyboard();
	write(dev_seg, 0x0000, 2);
	close(dev_seg);
	close(dev_gpio);
	return 0;
}