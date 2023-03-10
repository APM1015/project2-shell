#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>

int cd(int argc, const char *source, const char *dest);
int checkDir(const char *filename);

int main(int argc, char *argv[]){

    return 0;
}
//when called exits shell
int ex(){
    printf("Exiting shell");
    exit(0);
}
//help command: Prints out pwd with letters for command
//with what each command does
int help(){

    printf("-pwd: prints out the current working directory\n");
    printf("-cd: takes a directory and copies it to another directory\n");
    printf("-exit: exits the shell");
}
//When called print the current working directory to standard output
int pwd(){
    char pwd[1024];
    if(getcwd(pwd, sizeof(pwd)) != NULL){
        printf("pwd: %s\n", pwd);
    }
    else{
        printf("Error retriving pwd");
        exit(EXIT_FAILURE);
    }

}
int cd(int argc, const char *f1, const char *f2){
    if (argc < 2) {//If less than two arguments entered error prompty because cannot run
        perror("Invalid number of arguments");
        exit(EXIT_FAILURE);
    }
    FILE *source, *dest; //creating pointer for arguments to be opened in

    source = fopen(f1, "r"); //opening first argument
    dest = fopen(f2, "w"); //opening second argument
    
    int ret1 = 1;
    int ret2 = 1;
    ret1 = checkDir(*f1);//checking if the destination file is a file or directory
    ret2 = checkDir(*f2);
    //if ret is 0-> directory: if 1->no directory
    if(ret1 == 0 && ret2 == 0) {//mult source files to directory
        
        
    }
    else{
        printf("Error: One of the files is not a directory\n");
        exit(EXIT_FAILURE);
    }
    return 0;

}
int checkDir(const char *filename) { //using stat to check if file or directory
    struct stat path;
    stat(filename, &path);
    return S_ISREG(path.st_mode);
}
