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
int ex();
int help();
int pwd();
char **parse(char *line, char *delim);
int pip(int argc);
int out(int argc, const char *f1);
int in(int argc, const char *f1);


int main(int argc, char *argv[]){

    char line[1024];

    while(1){
        printf("echo>");
        fgets(line, 1024, stdin);
        line[strlen(line) - 1] = '\0';
        char **args = parse(line, " ");

        if(args == NULL){
            //nothing
        }
        else if(strcmp(args[0], "exit") == 0){
            ex();
        }
        else if(strcmp(args[0], "pwd") == 0){
            pwd();
        }
        else if(strcmp(args[0], "help") == 0){
            help();
        }
        else if(strcmp(args[0], "cd") == 0){
            cd(argc, argv[1], argv[2]);
        }
        else if(strcmp(args[0], ">") == 0){
            out(argc, argv[1]);
        }
        else if(strcmp(args[0], "<") == 0){
            in(argc, argv[1]);
        }
        else{

        }
    }

    return 0;
}

char ** parse(char *line, char *delim){

    char**array=malloc(sizeof(char*));
    *array=NULL;
    int n = 0;

    char*buf = strtok(line,delim);

    if (buf == NULL){
        free(array);
        array=NULL;
        return array;
    }

    while(buf!=NULL ){

        char**temp = realloc(array,(n+2)*sizeof(char*));

        if(temp==NULL){
            free(array);
            array=NULL;
            return array;
        }

        array=temp;
        temp[n++]=buf;
        temp[n]=NULL;

        buf = strtok(NULL,delim);

    }
    return array;
}

//when called exits shell
int ex(){
    printf("Exiting shell");
    exit(0);
}
//help command: Prints out pwd with letters for command
//with what each command does
int help(){
    printf("-----------------");
    printf("\nManuel for Shell\n");;
    printf("------------------\n");
    printf("\t-pwd: prints out the current working directory\n");
    printf("\t-cd: takes a directory and copies it to another directory\n");
    printf("\t-wait: wait for all background processes to finish\n");
    printf("\t-help: print the manuel\n");
    printf("\t-exit: exits the shell\n");
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
    char sour[1024];
    char dest[1024];

    if (argc < 3) {//If less than two arguments entered error prompty because cannot run
        perror("Invalid number of arguments");
        exit(EXIT_FAILURE);
    }
    FILE *source; //*dest; //creating pointer for arguments to be opened in

    source = opendir(f1); //opening first argument
    //dest = fopen(f2, "w"); //opening second argument

    char input[1024];

    //input = readdir(source);
    while(( input == readdir(source)) != NULL){
        snprintf(sour, sizeof(sour), "%s/%s", sour);
        snprintf(dest, sizeof(dest), "%s/%s", dest);
        //snprintf(sour, sizeof(sour), "%s/%s", sour, input->d_name);
        //snprintf(dest, sizeof(dest), "%s/%s", dest, input->d_name);
    }


    closedir(source);

    return 0;

}
int checkDir(const char *filename) { //using stat to check if file or directory
    struct stat path;
    stat(filename, &path);
    return S_ISREG(path.st_mode);
}
int out(int argc, const char *f1){

    FILE *output = fopen(f1, "w");
    dup2(output, STDOUT_FILENO);
    close(output);


}
int in(int argc, const char *f1){
    int *input = fopen(f1, O_RDONLY);
    dup2(input, STDIN_FILENO);
    close(input);
}
