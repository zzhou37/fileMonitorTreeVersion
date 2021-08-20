makefile:
fileMonitor: fileMonitor.c file.c md5mit.c
	gcc -o fileMonitor fileMonitor.c file.c md5mit.c
all: fileMonitor.c file.c md5mit.c
	gcc -o fileMonitor fileMonitor.c file.c md5mit.c
file: file.c file.h md5mit.c md5mit.h
	gcc -o file file.c md5mit.c
clean: 
	rm fileMonitor file 