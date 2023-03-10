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

int exit(){
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

int pwd(){

}
int cd(){

}
