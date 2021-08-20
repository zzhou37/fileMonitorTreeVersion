#include "file.h"
//#include "file.c"

void removeFileName(char* path, char* fileName){
    int i = strlen(path)-strlen(fileName)-1;
    //printf("i is: %d", i);
    while(path[i] != '\0'){
        path[i] = '\0';
        i++;
    }
}



void storedir(arrayList* al, char *dir, int depth, char* path) {
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if((dp = opendir(dir)) == NULL) {
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);
    while((entry = readdir(dp)) != NULL) { //read a file in the dir and return an entry 
        lstat(entry->d_name,&statbuf);     //read file name of the entry and store into the buffer
        if(S_ISDIR(statbuf.st_mode)) {     //if the file is a dir then print the dir name and recursive into the file
            /* Found a directory, but ignore . and .. */
            if(strcmp(".",entry->d_name) == 0 ||
                strcmp("..",entry->d_name) == 0)
                continue;
            //printf("%*s%s",depth,"",entry->d_name); //print the dir name of the
            //update the file path
            strcat(path, "/"); strcat(path, entry->d_name);
            //printf("localPath:%s\n", path);
            /* Recurse at a new indent level */
            storedir(al, entry->d_name,depth+4, path); 
            removeFileName(path, entry->d_name);
        }
        else {
            //printf("%*s%s:",depth,"",entry->d_name); //if not a dir //****print the file name****
            //printf("%s", MDFile(entry->d_name)); //MD5
            //print file path
            strcat(path, "/"); strcat(path, entry->d_name);
            printf("localPath:%s\n", path);
            addFileInfo(al, entry->d_name, MDFile(entry->d_name), path);
            removeFileName(path, entry->d_name);
            printf("\n");
        }
    }
    chdir("..");
    closedir(dp);
}

void updatedir(arrayList* al, char *dir, int depth, char* path) {
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if((dp = opendir(dir)) == NULL) {
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);
    while((entry = readdir(dp)) != NULL) { //read a file in the dir and return an entry 
        lstat(entry->d_name,&statbuf);     //read file name of the entry and store into the buffer
        if(S_ISDIR(statbuf.st_mode)) {     //if the file is a dir then print the dir name and recursive into the file
            /* Found a directory, but ignore . and .. */
            if(strcmp(".",entry->d_name) == 0 ||
                strcmp("..",entry->d_name) == 0)
                continue;
            //update the file path
            strcat(path, "/"); strcat(path, entry->d_name);
            /* Recurse at a new indent level */
            storedir(al, entry->d_name,depth+4, path); 
            removeFileName(path, entry->d_name);
        }
        else {
            //printf("%*s%s:",depth,"",entry->d_name); //if not a dir //****print the file name****
            //printf("%s", MDFile(entry->d_name)); //MD5
            //print file path
            strcat(path, "/"); strcat(path, entry->d_name);
            printf("localPath:%s\n", path);
            add(al, newFileInfo(entry->d_name, MDFile(entry->d_name), path));
            removeFileName(path, entry->d_name);
            printf("\n");
        }
    }
    chdir("..");
    closedir(dp);
}

void printdir(char *dir, int depth, char* path) {
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if((dp = opendir(dir)) == NULL) {
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);
    while((entry = readdir(dp)) != NULL) { //read a file in the dir and return an entry 
        lstat(entry->d_name,&statbuf);     //read file name of the entry and store into the buffer
        if(S_ISDIR(statbuf.st_mode)) {     //if the file is a dir then print the dir name and recursive into the file
            /* Found a directory, but ignore . and .. */
            if(strcmp(".",entry->d_name) == 0 ||
                strcmp("..",entry->d_name) == 0)
                continue;
            printf("%*s%s",depth,"",entry->d_name); //print the dir name of the
            //update the file path
            strcat(path, "/"); strcat(path, entry->d_name);
            printf("localPath:%s\n", path);
            /* Recurse at a new indent level */
            printdir(entry->d_name,depth+4, path); 
            removeFileName(path, entry->d_name);
        }
        else {
            printf("%*s%s:",depth,"",entry->d_name); //if not a dir //****print the file name****
            printf("%s", MDFile(entry->d_name)); //MD5
            //print file path
            strcat(path, "/"); strcat(path, entry->d_name);
            printf("localPath:%s\n", path);
            removeFileName(path, entry->d_name);
            printf("\n");
        }
    }
    chdir("..");
    closedir(dp);
}

int main() {
    MDFile("./dir/OutputExample.docx");
    char path[PATH_MAX + 1] = "./dir";
    printf("Directory scan of /dir:\n");
    //printdir("./dir",0, path);
    arrayList* al = newArrayList();
    storedir(al, "./dir",0, path);
    printf("scan finish. Display Result:\n");
    printArrayList(al);
    printf("done.\n");
    return 0;
}
