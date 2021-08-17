makefile:
fileMonitor: fileMonitor.c file.c md5mit.c
	gcc -o fileMonitor fileMonitor.c file.c md5mit.c
all: fileMonitor.c file.c md5mit.c
	gcc -o fileMonitor fileMonitor.c file.c md5mit.c
clean: 
	rm fileMonitor file 