#include <stdio.h>
#include <string.h>

char* cmd_st[1000];

void str_split(char* line){
    char * token = strtok(line, " ");
    int idx = 0;
    int temp;
    while(token != NULL) {
        cmd_st[idx] = token; // Stores split command in a global array
        temp = strlen(token) - 1;
        idx++;
        token = strtok(NULL, " ");
    }
}

int main(int num_args, char* stri[]){
    str_split(stri[0]);
    int idx = 0;
    int ret;
    if(strcmp(cmd_st[0],"HEHE")==0){
        idx = 1;
        char check;
        printf("rm: remove file ?");
        scanf("%c",&check);
        while(cmd_st[idx]!=NULL){
            if(check='y'){
                ret = remove(cmd_st[idx]);
                idx++;
                if(ret == 0) {
                    printf("File deleted successfully\n");
                } else {
                    printf("Error: unable to delete or locate the file\n");
                }
            }
            else{
                continue;
            }
        }
    }
    while(cmd_st[idx]!=NULL){
        ret = remove(cmd_st[idx]);
        if(strcmp(cmd_st[idx]," ")!=0 || strcmp(cmd_st[idx],"")!=0){
            idx++;
            if(ret == 0) {
                printf("File deleted successfully\n");
            } 
            else {
                printf("Error: unable to delete or locate the file\n");
            }
        }
    }
    return 0;
}