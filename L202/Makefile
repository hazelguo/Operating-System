obj-m += walkpage.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

rmmod:
	rmmod walkpage
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
