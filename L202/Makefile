obj-m += pagetable.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

insmod:
	insmod pagetable.ko

rmmod:
	rmmod pagetable
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
