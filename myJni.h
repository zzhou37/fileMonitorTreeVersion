#include <jni.h>
#include <stdlib.h>
#include "file.h"

//call Java function. provide class name, file name and argument
char* callJava(char* className, char* methodName, char* arg);
