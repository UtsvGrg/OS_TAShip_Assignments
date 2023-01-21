#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


int main(int num_args, char* cmd_store[]){
    int counter = 0;
    if(strcmp(cmd_store[counter],"./mkdir_exec")==0){
        counter++;
    }
    int check;
    if(cmd_store[counter]==NULL||strcmp(cmd_store[counter],"")==0){
        printf("mkdir: missing operand");
        exit(0);
    }

    if(cmd_store[counter+1]==NULL){
        check = mkdir(cmd_store[counter],0777);
        if(check==-1){
            printf("Error in creating directory");
        }
    }
    else if(strcmp(cmd_store[counter],"-v")==0){
        check = mkdir(cmd_store[counter+1],0777);
        if(!check){
            printf("mkdir: created directory '%s'",cmd_store[counter+1]);
        }
        if(check==-1){
            printf("Error in creating directory");
        }
    }
    else if(strcmp(cmd_store[counter],"-m777")==0){
        check = mkdir(cmd_store[counter+1],0777);
        if(check==-1){
            printf("Error in creating directory");
        }
    }
    else{
        printf("mkdir: missing operand");
    }
}