##!/bin/bash
#for I in {0..500}; do
#	echo "Do you want to bind USB device (Y/N)?"
#	read ans
#	if [ "$ans" -eq 'Y'] 
#		echo "1-1" > /sys/bus/usb/drivers/usb/bind
#	fi
#	echo "Do you want to unbind USB device (Y/N)?"
#	read ans
#	if ["$ans" -eq
#		echo "1-1" > /sys/bus/usb/drivers/usb/unbind
#	fi
#done
if [ $# -eq 1 ]; then
	for i in `seq 1 5`;
	do
		echo "The $i round:"

		echo -n "$1" > /sys/bus/usb/drivers/usb/unbind
		tree /sys/bus/usb/drivers/usb
		echo "Device unbinded."

		echo -n "$1" > /sys/bus/usb/drivers/usb/bind
		tree /sys/bus/usb/drivers/usb
		echo "Device binded."
	done    
else
	echo Usage: bash $0 BusID
fi
