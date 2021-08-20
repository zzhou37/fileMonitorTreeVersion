makefile:
fileMonitor: fileMonitor.c file.c md5mit.c myJni.c
	gcc -fPIC -I /Library/Java/JavaVirtualMachines/jdk-16.0.2.jdk/Contents/Home/include -I /Library/Java/JavaVirtualMachines/jdk-16.0.2.jdk/Contents/Home/include/darwin -L /Library/Java/JavaVirtualMachines/jdk-16.0.2.jdk/Contents/Home/lib/server -o fileMonitor myJni.c fileMonitor.c file.c md5mit.c -ljvm
	#gcc -o fileMonitor fileMonitor.c file.c md5mit.c
all: fileMonitor.c file.c md5mit.c
	gcc -o fileMonitor fileMonitor.c file.c md5mit.c
myJni: 
	gcc -fPIC -I /Library/Java/JavaVirtualMachines/jdk-16.0.2.jdk/Contents/Home/include -I /Library/Java/JavaVirtualMachines/jdk-16.0.2.jdk/Contents/Home/include/darwin -L /Library/Java/JavaVirtualMachines/jdk-16.0.2.jdk/Contents/Home/lib/server myJni.c -ljvm
run:
	LD_LIBRARY_PATH=/Library/Java/JavaVirtualMachines/jdk-16.0.2.jdk/Contents/Home/lib/server ./fileMonitor 
clean: 
	rm fileMonitor file 