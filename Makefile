obj-m += gpio_driver.o
obj-m += seg_driver.o
KDIR = ~/working/Raspbian/kernel
RESULT = termproject_v3
SRC = $(RESULT).c
CCC = arm-linux-gnueabihf-gcc

all:
	make -C $(KDIR) M=$(PWD) modules
	$(CCC) -o $(RESULT) $(SRC)

clean:
	make -C $(KDIR) M=$(PWD) clean
	rm -f $(RESULT)