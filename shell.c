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
int cd(){

}
