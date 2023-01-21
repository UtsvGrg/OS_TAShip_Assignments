#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h> 
#include <stdlib.h>

int main(int num_args, char* yo[]){
    int counter = 0;
    if(strcmp(yo[counter],"./date_exec")==0){
        counter++;
    }
    time_t now;
    struct tm *ftime;
    char arr[512];
    localtime(&now); 
    now = time(NULL);
    if(now==-1){
        printf("error: time() function failed");
    }
    if(yo[counter]==NULL||strcmp(yo[counter],"e")==0||strcmp(yo[counter],"")==0){
        ftime = localtime(&now);
        strftime(arr, sizeof(arr), "%a %b %d %T %Z %Y", ftime);
        printf("%s",arr);
    }
    else if(strcmp(yo[counter],"-R")==0){
        ftime = localtime(&now);
        strftime(arr, sizeof(arr), "%a %b %d %T %Y +0530", ftime);
        printf("%s",arr);   
    }
    else if(strcmp(yo[counter],"-u")==0){
        ftime = gmtime(&now);
        strftime(arr, sizeof(arr), "%a %b %d %T UTC %Y", ftime);
        printf("%s",arr);   
    }
    else{
        printf("Invalid command");
    }
}