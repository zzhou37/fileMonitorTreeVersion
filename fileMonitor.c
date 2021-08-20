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

void storeDir(fileTree* ft, char *dir, int depth, char* path) {
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
            addFileNode(ft, 0, "null", path);
            /* Recurse at a new indent level */
            storeDir(ft, entry->d_name,depth+4, path);
            removeFileName(path, entry->d_name);
        }
        else {
            //printf("%*s%s:",depth,"",entry->d_name); //if not a dir //****print the file name****
            //printf("%s", MDFile(entry->d_name)); //MD5
            //print file path
            strcat(path, "/"); strcat(path, entry->d_name);
            printf("localPath:%s\n", path);
            //add(al, newFileInfo(entry->d_name, MDFile(entry->d_name), path));
            addFileNode(ft, 1, MDFile(entry->d_name), path);
            removeFileName(path, entry->d_name);
            printf("\n");
        }
    }
    chdir("..");
    closedir(dp);
}

void updateDir(fileTree* ft, char *dir, int depth, char* path) {
    //printf("begin: %s\n", path);
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
            strcat(path, "/"); strcat(path, entry->d_name);
            updateFile(ft, 0, "null", path);
            /* Recurse at a new indent level */
            updateDir(ft, entry->d_name,depth+4, path);
            removeFileName(path, entry->d_name);
        }
        else {
            strcat(path, "/"); strcat(path, entry->d_name);
            char* MD5 = MDFile(entry->d_name);
            if(MD5 != NULL) updateFile(ft, 1, MD5, path);
            else updateFile(ft, 1, "null", path);
            removeFileName(path, entry->d_name);
        }
    }
    chdir("..");
    closedir(dp);
    //printf("end: %s\n", path);
}

void updateDirTest(fileTree* ft, char *dir, int depth, char* path) {
    //printf("begin: %s\n", path);
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
            strcat(path, "/"); strcat(path, entry->d_name);
            updateFile(ft, 0, "null", path);
            /* Recurse at a new indent level */
            updateDirTest(ft, entry->d_name,depth+4, path);
            removeFileName(path, entry->d_name);
        }
        else {
            strcat(path, "/"); strcat(path, entry->d_name);
            char* MD5 = MDFile(entry->d_name);
            if(MD5 != NULL) updateFile(ft, 1, MD5, path);
            else updateFile(ft, 1, "null", path);
            removeFileName(path, entry->d_name);
        }
    }
    chdir("..");
    closedir(dp);
    //printf("end: %s\n", path);
}

int main() {
    char path[PATH_MAX + 1] = "./dir";
    char fullPath[PATH_MAX + 1];
    if(getcwd(fullPath, sizeof (fullPath)) != NULL){
        strcat(fullPath, &path[1]);
        printf("Current working dir: %s\n", fullPath);
    }
    else{
        return 1;
    }
    printf("Directory scan of /dir:\n");
    //printdir("./dir",0, path);
    fileTree* ft = newFileTree();
    storeDir(ft, "./dir",0, path);
    //while loop
    while(1){
        sleep(1);
        printf("looking...\n\n");
        clearAllExist(ft->head);
        updateDir(ft, fullPath,0, path);
        deleteAllFileNotExist(ft, ft->head);
        //printFileTree(ft->head, 0);
        if(ft->currUpdate != NULL) printf("%s\n", ft->currUpdate);
        clearContent(ft);
    }
    return 0;
}
