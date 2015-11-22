#EXTRA_CFLAGS += -mhard-float

obj-m += bind.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules 

insmod:
	insmod hello.ko

rmmod:
	rmmod hello
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
