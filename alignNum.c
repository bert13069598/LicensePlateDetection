#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* inputFile = NULL;
    char filename[] = "test_license2_crop0.txt";

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

        printf("linecount is %d\n", linecount);       
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
                        number[0] = 0;

                    }


                    if (number[0] != 0 && number[2] != 0) {
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

    // printf("\n");

    for (int i = 0; i < linecount; i++)
        printf("%d %d\n", dataNum[i][0], dataNum[i][1]);
    // printf("count end!!!\n");
    // printf("\n");

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
}