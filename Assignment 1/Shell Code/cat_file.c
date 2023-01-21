#include <stdio.h>
#include <string.h>

int main(int num_args, char* cmd_store[]){ 
    int counter = 0;
    if(strcmp(cmd_store[counter],"./cat_exec")==0){
        counter++;
    }
    FILE* file_ptr;
    char line[2048];
    int line_c = 1;
    if(cmd_store[counter+1]==NULL){
        file_ptr = fopen(cmd_store[counter],"r");
            if(file_ptr==NULL){
                printf("error: could not open file");
            }
        while(fgets(line, 2048, file_ptr)!=NULL){
            printf("%s",line);
        }
        fclose(file_ptr);
    }

    else if(strcmp(cmd_store[counter],"-E")==0){
        file_ptr = fopen(cmd_store[counter+1],"r");
            if(file_ptr==NULL){
                printf("error: could not open file");
            }
        while(fgets(line, 2048, file_ptr)!=NULL){
            line[strlen(line)-1] = '$';
            printf("%s\n",line);
        }
        fclose(file_ptr);
    }

    else if(strcmp(cmd_store[counter],"-n")==0){
        file_ptr = fopen(cmd_store[counter+1],"r");
            if(file_ptr==NULL){
                printf("error: could not open file");
            }
        while(fgets(line, 2048, file_ptr)!=NULL){
            printf("%d %s",line_c++,line);
        }
        fclose(file_ptr);
    }
    else{
        printf("Invalid Command");
    }
}