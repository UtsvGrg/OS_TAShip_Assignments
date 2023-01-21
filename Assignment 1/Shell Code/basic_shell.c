#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <pthread.h>

char* cmd_store[15];
char home[200];

void* thread_handle(void* arg){
	system((char*)arg);
	return NULL;
}

void thread_func(char* cmd_store[]){
    char stri[1000];
    memset(stri, 0, sizeof(stri));
    int num = 0;
    pthread_t pth1;
	int rc;
    if(strcmp(cmd_store[0],"cat")==0){
        strcat(stri,"./cat_exec ");
        num = 1;
        while (cmd_store[num]!=NULL){
            strcat(stri,cmd_store[num]);
            strcat(stri," ");
            num++;
        }
        rc = pthread_create(&pth1, NULL, thread_handle, (void*)stri);
	    rc = pthread_join(pth1,NULL);
    }

    else if(strcmp(cmd_store[0],"date")==0){
        strcat(stri,"./date_exec ");
        num = 1;
        while (cmd_store[num]!=NULL){
            strcat(stri,cmd_store[num]);
            strcat(stri," ");
            num++;
        }
        rc = pthread_create(&pth1, NULL, thread_handle, (void*)stri);
	    rc = pthread_join(pth1,NULL);
    }

    else if(strcmp(cmd_store[0],"mkdir")==0){
        strcat(stri,"./mkdir_exec ");
        num = 1;
        while (cmd_store[num]!=NULL){
            strcat(stri,cmd_store[num]);
            strcat(stri," ");
            num++;
        }
        rc = pthread_create(&pth1, NULL, thread_handle, (void*)stri);
	    rc = pthread_join(pth1,NULL);
    }

    else if(strcmp(cmd_store[0],"ls")==0){
        strcat(stri,"./ls_exec ");
        num = 0;
        while (cmd_store[num]!=NULL){
            strcat(stri,cmd_store[num]);
            strcat(stri," ");
            num++;
        }
        rc = pthread_create(&pth1, NULL, thread_handle, (void*)stri);
	    rc = pthread_join(pth1,NULL);
    }
    else if(strcmp(cmd_store[0],"rm")==0){
        num = 0;
        while (cmd_store[num]!=NULL){
            strcat(stri,cmd_store[num]);
            strcat(stri," ");
            num++;
        }
        rc = pthread_create(&pth1, NULL, thread_handle, (void*)stri);
	    rc = pthread_join(pth1,NULL);
    }
}

void pwd_help(){
    printf("\npwd: pwd [-LP]\nPrint the name of the current working directory.\nOptions:\n   -L	print the value of $PWD if it names the current working directory\n");
    printf("Exit Status:\nReturns 0 unless an invalid option is given or the current directory\ncannot be read.\n");
}

void func_cd(char* cmd_store[]){
    if(cmd_store[1]==NULL){
        return;
    }
    if (strcmp(cmd_store[1],"-L")==0 || strcmp(cmd_store[1],"-P")==0){
        chdir(cmd_store[2])!=0;     
    }
    if (strcmp(cmd_store[1],"..")==0 || strcmp(cmd_store[1],".")==0){
        if(chdir(cmd_store[1])!=0){
            printf("cd: error to use the operation"); // error handled #1
        }         
    }
    else if(chdir(cmd_store[1])!=0){
        printf("cd: error to use the operation"); // error handled #2
    }
}

void func_cat(char* cmd_store[]){
    pid_t pid = fork();
    int status;
    if(pid<0){
        printf("Failed to fork child process");
        exit(1); 
    }
    else if(pid==0){
        char home_copy[200];
        strcpy(home_copy,home);
        strcat(home_copy,"/cat_exec");
        execl(home_copy,cmd_store[1],cmd_store[2],(char*)NULL);
    }
    int w = wait(&status);
    if(w==-1){
        printf("error: waitpid");
        return;
    }
}   

void func_date(char* cmd_store[]){
    pid_t pid = fork();
    int status;
    if(pid<0){
        printf("Failed to fork child process");
        exit(1); 
    }
    else if(pid==0){
        char home_copy[200];
        strcpy(home_copy,home);
        strcat(home_copy,"/date_exec");
        execl(home_copy,cmd_store[1],(char*)NULL);
    }
    int w = wait(&status);
    if(w==-1){
        printf("error: waitpid");
        return;
    }
}

void func_mkdir(char* cmd_store[]){
    pid_t pid = fork();
    int status;
    if(pid<0){
        printf("Failed to fork child process");
        exit(1); 
    }
    else if(pid==0){
        char home_copy[200];
        strcpy(home_copy,home);
        strcat(home_copy,"/mkdir_exec");
        execl(home_copy,cmd_store[1],cmd_store[2],(char*)NULL);
    }
    int w = wait(&status);
    if(w==-1){
        printf("error: waitpid");
        return;
    }
}

void func_rm(char* cmd_store[]){
    pid_t pid = fork();
    int status;
    if(pid<0){
        printf("Failed to fork child process");
        exit(1); 
    }
    else if(pid==0){
        char stri[1000];
        char home_copy[200];
        strcpy(home_copy,home);
        if(cmd_store[1]==NULL||strcmp(cmd_store[1],"")==0){ //not working
            strcat(home_copy,"/empty_exec");
            execl(home_copy,"yp",(char*)NULL);
        }
        else if(strcmp(cmd_store[1],"-i")==0){
            strcat(stri,"HEHE ");
            int num=2;
            while(cmd_store[num]!=NULL){
                strcat(stri,cmd_store[num]);
                strcat(stri," ");
                num++;
            }  
            strcat(home_copy,"/rm_exec");
            execl(home_copy,stri,(char*)NULL);
        }
        else if(strcmp(cmd_store[1],"-f")==0){
            int num=2;
            while(cmd_store[num]!=NULL){
                strcat(stri,cmd_store[num]);
                strcat(stri," ");
                num++;
            }  
            strcat(home_copy,"/rm_exec");
            execl(home_copy,stri,(char*)NULL);
        }
        else{
            int num=1;
            while(cmd_store[num]!=NULL){
                strcat(stri,cmd_store[num]);
                strcat(stri," ");
                num++;
            }  
            strcat(home_copy,"/rm_exec");
            execl(home_copy,stri,(char*)NULL);
        }
    }
    int w = wait(&status);
    if(w==-1){
        printf("error: wait");
        return;
    }
}

void func_ls(char* cmd_store[]){
    pid_t pid = fork();
    int status;
    if(pid<0){
        printf("Failed to fork child process");
        exit(1); 
    }
    else if(pid==0){
        if(cmd_store[1]==NULL){
            cmd_store[1] = "nospace";
        }
        char home_copy[200];
        strcpy(home_copy,home);
        strcat(home_copy,"/ls_exec");
        execl(home_copy,cmd_store[0],cmd_store[1],(char*)NULL); // this is for ls, ls -a, and ls -l
    }
    int w = wait(&status);
    if(w==-1){
        printf("error: waitpid");
        return;
    }
}


void func_echo(char* cmd_store[]){
    int idx;
    if(cmd_store[1]==NULL){//||strcmp(cmd_store[1],"")==0){
        ;
    }
    else{
        if(strcmp(cmd_store[1],"--help")==0){ // supports echo -e add assumption in the file
            printf("Usage: /bin/echo [SHORT-OPTION]... [STRING]...\nor:  /bin/echo LONG-OPTION\nEcho the STRING(s) to standard output.");
            printf("\n  --help     display this help and exit");
            printf("\n  *          display the files in the directory");     
        }
        else if (strcmp(cmd_store[1],"*")==0){  // supports echo *
            char* temp_store[15];
            temp_store[0] = "ls";
            temp_store[1] = "nospace";
            func_ls(temp_store);
        }
        else {
            idx = 1;
            while(cmd_store[idx]!=NULL){
                printf("%s ",cmd_store[idx]);
                idx++;
            }
        }
    }
}

void func_pwd(char* cmd_store[]){
    char path[512];
    char* ptr;
    if(cmd_store[1]==NULL||strcmp(cmd_store[1],"")==0){
        ptr = getcwd(path,512);
        if(ptr==NULL){
            perror("pwd");
            exit(1);
        }
        printf("%s",path);
    }
    else if(strcmp(cmd_store[1],"--help")==0){
        pwd_help();
    }
    else if(strcmp(cmd_store[1],"-L")==0){
        ptr = getcwd(path,512);
        if(ptr==NULL){
            perror("pwd");
            exit(1);
        }
        printf("%s",path);    
    }
    else if(strcmp(cmd_store[1],"-P")==0){
        getcwd(path,512);
        printf("%s",path);     
    }
    else{
        printf("Invalid Command\n");
        printf("Use pwd --help to know about pwd");
    }
}

void str_checker(char* cmd_store[]){


    if(strcmp(cmd_store[0],"cd")==0){
        func_cd(cmd_store);
    }
    else if(strcmp(cmd_store[0],"pwd")==0){
        func_pwd(cmd_store);
    }

    else if(strcmp(cmd_store[0],"echo")==0){
        func_echo(cmd_store);
    }

    else if(strcmp(cmd_store[0],"ls")==0){
        func_ls(cmd_store);
    }

    else if(strcmp(cmd_store[0],"cat")==0){
        func_cat(cmd_store);
    }

    else if(strcmp(cmd_store[0],"date")==0){
        func_date(cmd_store);
    }

    else if(strcmp(cmd_store[0],"rm")==0){
        func_rm(cmd_store);
    }

    else if(strcmp(cmd_store[0],"mkdir")==0){
        func_mkdir(cmd_store);
    }

    else if(strcmp(cmd_store[0],"exit")==0){
        exit(0);
    }

    else{
        printf("The command is not valid");
    }
}

void str_split(char* line){
    char * token = strtok(line, " ");
    int idx = 0;
    int temp;
    while(token != NULL){
        cmd_store[idx] = token; // Stores split command in a global array
        temp = strlen(token) - 1;
        idx++;
        token = strtok(NULL, " ");
    }
    cmd_store[idx-1][temp] = '\0';
    if(strcmp(cmd_store[idx-1],"&t")==0){
        cmd_store[idx-1] = NULL;
        thread_func(cmd_store);
    }
    else{
        str_checker(cmd_store);
    }
}

void input_cmd(){
    printf("\n>>>");
    char *line = NULL;
    size_t lenght = 0;
    int lineSize = 0;
    lineSize = getline(&line,&lenght,stdin);
    str_split(line);
    free(line);
    return;
}

int main(){
    printf("\n--------------------------------------------\n\n");
    printf("       Welcome To Utsav's Custom Shell        \n");
    printf("\n--------------------------------------------\n\n");
    getcwd(home,200);
    while(1){
        input_cmd();
    }
    return 0;
}

