obj-m += L5_print_hex_dump.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

install:
	insmod L5_print_hex_dump.ko

unins:
	rmmod L5_print_hex_dump 
