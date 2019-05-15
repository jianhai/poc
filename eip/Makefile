.PHONY: all clean

obj-m := eip.o


KERNEL := /lib/modules/`uname -r`/build/
all:
	make -C ${KERNEL} M=`pwd` modules
	gcc -o test main.c -lpthread

clean:
	make -C ${KERNEL} M=`pwd` clean
	rm -rf test
