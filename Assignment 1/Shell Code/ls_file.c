#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int num_args, char*cmd_store[num_args]){ 
    int counter = 0;
    if(strcmp(cmd_store[counter],"./ls_exec")==0){
        counter++;
    }
    char path[512];
    getcwd(path,512);
    struct dirent *head;
    DIR *dir = opendir(path);
    if(dir==NULL){
        perror(path); // error handled 1
        exit(1);
    }

    if(cmd_store[counter+1]==NULL){
        system("ls");
        return 0;
    }

    if (strcmp(cmd_store[counter+1], "-d")==0){
        printf(".");
        return 0;
    }

    if (strcmp(cmd_store[counter+1], "nospace")==0){
        while((head = readdir(dir))!=NULL){
            if(head->d_name[0]=='.'){
                continue;
            }
            else{
                printf("%s ", head->d_name);
            }
        }
    }

    while((head = readdir(dir))!=NULL){
       if(head->d_name[0]=='.'){
            if(strcmp(cmd_store[counter+1], "-a")==0){
                printf("%s ", head->d_name);
            }
            else if(strcmp(cmd_store[counter+1], "-A")==0 && (strcmp(head->d_name,".." )==0 || strcmp(head->d_name,".")==0)){
                continue;
            }
            else{
                continue;
            }
        }
        else{
            printf("%s ", head->d_name);
        }
    }
    return 0;
    if (strcmp(cmd_store[counter+1], "-d")!=0 || strcmp(cmd_store[counter+1], "-a")!=0){
        printf("error: invalid command"); // error handled 2
    }
    closedir(dir);

}
