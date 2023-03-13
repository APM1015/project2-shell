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


int main(int argc, char *argv[]){
    char _line[1000] = "a line of text\n";
    char * line = strdup(_line);
    char ** array = parse(line," \n");

    if (array==NULL)
        exit(1);

    int i = 0;
    while (array[i]!=NULL)
        printf("%s\n",array[i++]);

    free(array);
    free(line);
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

    printf("-pwd: prints out the current working directory\n");
    printf("-cd: takes a directory and copies it to another directory\n");
    printf("-wait: wait for all background processes to finish\n");
    printf("help: print the manuel\n");
    printf("-exit: exits the shell\n");
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

    char input;
    while(( input = readdir(source)) != NULL){
        snprintf(sour, sizeof(sour), "%s/%s", sour, input->d_name);
        snprintf(dest, sizeof(dest), "%s/%s", dest, input->d_name);
    }
    closedir(source);




    int ret1 = 1;
    int ret2 = 1;
    ret1 = checkDir(*f1);//checking if the destination file is a file or directory
    ret2 = checkDir(*f2);

    return 0;

}
int checkDir(const char *filename) { //using stat to check if file or directory
    struct stat path;
    stat(filename, &path);
    return S_ISREG(path.st_mode);
}
