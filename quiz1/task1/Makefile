obj-m += producer.o
obj-m += consumer.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

insmod:
	insmod producer.ko
	insmod consumer.ko

rmmod:
	rmmod consumer
	rmmod producer
