#include "myJni.h"


char* callJava(char* className, char* methodName, char* arg){
    JavaVM         *vm; //java virtual machine pointer
    JNIEnv         *env; //java environment
    JavaVMInitArgs  vm_args; //arguments
    jint            res; //java integer
    jclass          cls; //java class
    jmethodID       mid; //java method ID
    jstring         jstr; //java String

    //set up java vm
    vm_args.version  = JNI_VERSION_1_8;
    vm_args.nOptions = 0;

    //creat java virtual machine
    res = JNI_CreateJavaVM(&vm, (void **)&env, &vm_args);
    if (res != JNI_OK) {
        printf("Failed to create Java VM\n");
        return NULL;
    }

    //call env function to find java class
    cls = (*env)->FindClass(env, className);
    if (cls == NULL) {
        printf("Failed to find Main class\n");
        return NULL;
    }

    //call env function to find java method
    mid = (*env)->GetStaticMethodID(env, cls, methodName, "(Ljava/lang/String;)Ljava/lang/String;");
    if (mid == NULL) {
        printf("Failed to find main function\n");
        return NULL;
    }

    //call env function to construct parameter
    jstr = (*env)->NewStringUTF(env, arg);

    //call method
    jstring retJString = (jstring)((*env)->CallStaticObjectMethod(env, cls, mid, jstr));

    jboolean jb;
    const char *ret = (* env)->GetStringUTFChars(env, retJString, &jb);

    char* retStr = calloc(strlen(ret) + 1, sizeof(char));
    strcpy(retStr, ret);

    (* env)->ReleaseStringUTFChars(env, retJString, ret);

    return retStr;
}

/*int main(){
    char* ret = callJava("HelloWorld", "testRetStr", "zzhou37");
    printf("%s\n", ret);
}*/




























