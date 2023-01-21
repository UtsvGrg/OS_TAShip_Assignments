#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>


void* request_fork(void *arg){
    
    int* i = (int*)arg;
    int temp = *i;
    if(temp==4){

        printf("Philosopher %d is thinking.\n",temp);
        printf("Philosopher %d has picked fork %d and %d.\n",temp,temp,0);
        printf("Philosopher %d is eating in bowl 1\n",temp);
        printf("Philosopher %d has placed fork %d and %d.\n\n",temp,temp,0);

    }
    else {
        if(temp%2){
            printf("Philosopher %d is thinking.\n",temp);
            printf("Philosopher %d has picked fork %d and %d.\n",temp,temp,temp+1);
            printf("Philosopher %d is eating in bowl 2.\n",temp);
            printf("Philosopher %d has placed fork %d and %d.\n\n",temp,temp,temp+1);

        }
        else{
            printf("Philosopher %d is thinking.\n",temp);
            printf("Philosopher %d has picked fork %d and %d.\n",temp,temp,temp+1);
            printf("Philosopher %d is eating in bowl 1.\n",temp);
            printf("Philosopher %d has placed fork %d and %d.\n\n",temp,temp,temp+1);
        }
    }

    return NULL;
}

int main(){
    pthread_t thread;
    for (int i=0; i<5; i++){
        pthread_create(&thread,NULL,&request_fork,(void*)&i);
        pthread_join(thread,NULL);
    }
}