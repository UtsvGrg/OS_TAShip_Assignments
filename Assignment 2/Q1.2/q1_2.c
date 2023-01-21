#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define power 1e9
pid_t pida,pidb,pidc;
struct timespec sa,fa,sb,fb,sc,fc;

int main(){
    clock_gettime(0,&sa);
    pida = fork();
    if(pida==0){
        sched_setscheduler(pida,SCHED_OTHER,NULL);
        execl("file1.sh","file1.sh",NULL,NULL,NULL);
    }
    else if(pida>0){
        clock_gettime(0,&sb);
        pidb = fork();
        if(pidb==0){
            sched_setscheduler(pidb,SCHED_FIFO,NULL);
            execl("file2.sh","file2.sh",NULL,NULL,NULL);
        }
        else if(pidb>0){
            clock_gettime(0,&sc);
            pidc = fork();
            if(pidc==0){
                sched_setscheduler(pidc,SCHED_RR,NULL);
                execl("file3.sh","file3.sh",NULL,NULL,NULL);
            }
            else if(pidc<0){
                perror("Error in Forking C");
            }
        }
        else if(pidb<0){
            perror("Error in Forking B");
        }
    }
    else if(pida<0){
        perror("Error in Forking A");
    }

    float time_store;
    pid_t piw = waitpid(-1,NULL,0);
    FILE *file_pointer;
    while(piw!=-1){
        if(piw==pida){
            clock_gettime(0,&fa);
            time_store = (fa.tv_sec - sa.tv_sec) + (fa.tv_nsec - sa.tv_nsec)/power;
            file_pointer = fopen("f1.txt",'a');
            fprintf(file_pointer,"SCHED_OTHER: %f\n",time_store);
        }
        if(piw==pidb){
            clock_gettime(0,&fb);
            time_store = (fb.tv_sec - sb.tv_sec) + (fb.tv_nsec - sb.tv_nsec)/power;
            file_pointer = fopen("f1.txt",'a');
            fprintf(file_pointer,"SCHED_FIFO: %f\n",time_store);
        }
        if(piw==pidc){
            clock_gettime(0,&fc);
            time_store = (fc.tv_sec - sc.tv_sec) + (fc.tv_nsec - sc.tv_nsec)/power;
            file_pointer = fopen("f1.txt",'a');
            fprintf(file_pointer,"SCHED_RR: %f\n",time_store);
        }
    }
    system("Python3 Graph2.py");
    return 0;
}
