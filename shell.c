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
int ex();
int help();
int pwd();
char **parse(char *line, char *delim);
int pip(int argc);
int out(int argc, const char *f1);
int in(int argc, const char *f1);
int path();


int main(int argc, char *argv[]) {
    //char *argp[] = {"ls", "-l", NULL}; // Command to be executed
    //char *argw[] = {"wc", NULL};

    char shell[1024];
  // path();

    while (1) {
        printf("echo>");

        fgets(shell, 1024, stdin);
        shell[strlen(shell) - 1] = '\0';
        char **args = parse(shell, " ");

        char *path = getenv("PATH"); //getting path

        char *tokenPath = strtok(path, ":");
        while (tokenPath != NULL) {
            char cmd[1000];
            snprintf(cmd, 1000, "%s/%s", tokenPath, shell);
            if (access(cmd, X_OK) == 0) { //was not working so implemented the access() to validate
                pid_t pid = fork();
                if (pid < 0) { //invalid pid value
                    printf("error forking");
                    ex();
                } else if (pid == 0) { //child
                    if (strcmp(cmd, "wc") == 0) {//attempted to fix wc but not workinng
                        int name = open(cmd, O_RDONLY);
                        dup2(name, STDIN_FILENO);
                    }
                    printf("Executing command: %s\n", cmd);
                    char *args[] = {path, NULL}; //fixes problem of argv[0] being NULL
                    execvp(cmd, args);
                } else { //parent
                    int status;
                    waitpid(pid, &status, 0);//waiting for child to complete
                }
            }
            tokenPath = strtok(NULL, ":");
        }

        if (args == NULL) {
            //nothing
        } else if (strcmp(args[0], "exit") == 0) {
            ex();
        } else if (strcmp(args[0], "pwd") == 0) {
            pwd();
        } else if (strcmp(args[0], "help") == 0) {
            help();
        } else if (strcmp(args[0], "cd") == 0) {
            cd(argc, argv[1], argv[2]);
        } else if (strcmp(args[0], "|")) {
            pip(args);
        } else if (strcmp(args[0], ">") == 0) {
            out(argc, argv[1]);
        } else if (strcmp(args[0], "<") == 0) {
            in(argc, argv[1]);
        }


    }
    return 0;


}
int path(){
    char shell[1024];

    while (1) {
        printf("echo>");
        fgets(shell, 1024, stdin);
        shell[strlen(shell) - 1] = '\0';
        char **args = parse(shell, " ");

        char *path = getenv("PATH"); //getting path

        char *tokenPath = strtok(path, ":");
        while (tokenPath != NULL) {
            char cmd[1000];
            snprintf(cmd, 1000, "%s/%s", tokenPath, shell);
            if (access(cmd, X_OK) == 0) { //was not working so implemented the access() to validate
                pid_t pid = fork();
                if (pid < 0) { //invalid pid value
                    printf("error forking");
                    ex();
                } else if (pid == 0) { //child
                    if (strcmp(cmd, "wc") == 0) {//attempted to fix wc but not workinng
                        int name = open(cmd, O_RDONLY);
                        dup2(name, STDIN_FILENO);
                    }
                    printf("Executing command: %s\n", cmd);
                    char *args[] = {path, NULL}; //fixes problem of argv[0] being NULL
                    execvp(cmd, args);
                } else { //parent
                    int status;
                    waitpid(pid, &status, 0);//waiting for child to complete
                }
            }
            tokenPath = strtok(NULL, ":");
        }
    }
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

int out(int argc, const char *f1){

    FILE *output = fopen(f1, "w");//open file
    dup2(output, STDOUT_FILENO);
    close(output); //closing file


}
int in(int argc, const char *f1){
    int *input = fopen(f1, O_RDONLY);
    dup2(input, STDIN_FILENO);
    close(input);
}
int pip(int argc){ //what is nummber of pipes????
    int pipe_array[argc-1][2]; //create array to hold pipes
    pid_t pid[argc - 1];

    for(int i = 0; i < argc-1; i++){
        pipe(pipe_array[i]); //creating pipe for each child
    }

    for(int i = 0; i < argc-1; i++){
        pid[i] = fork(); //forking all child processes

        if(pid[i] < 0){
            printf("error");
            ex();
        }
        else if(pid[i] == 0){
            if(i == 0){ //finds first child process
                close(pipe_array[0][0]);
                dup2(pipe_array[0][1], STDOUT_FILENO); //only needs STDOUT as nothing before it
                close(pipe_array[0][1]);
            }
        }
        else if(i == argc-1){ //last child process
            close(pipe_array[argc-2][1]);//have to close second to last pipe
            dup2(pipe_array[argc-2][0], STDIN_FILENO);
            close(pipe_array[argc-2][0]);
        }
        else{//all other pipes that are not at ends
            close(pipe_array[i-1][1]);
            close(pipe_array[i][0]);

            dup2(pipe_array[i-1][0], STDIN_FILENO); //Since middle needs STDIN
            dup2(pipe_array[i][1], STDOUT_FILENO);  //and STDOUT

            close(pipe_array[i-1][0]);
            close(pipe_array[i][1]);

        }
    }



    /*
    int pipefd[argc];
    pid_t pid;

    if(pipe(pipefd) == -1){
        ex();
    }
    pid = fork();
    if(pid == -1){
        ex();
    }
    if(pid == 0){
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        char *const args[] = {"ls", "-l", NULL};
        execvp(args[0], args);

        ex();
    }
    else{
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        char *const args[] = {"wc", "-l", NULL};
        execvp(args[0], args);

        ex();
    }
     */
    return 0;
}

