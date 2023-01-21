#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

int forks[] = {1,1,1,1,1};
sem_t sem_arr[5], sem_bowl1, sem_bowl2;

void think_func(int num){
    printf("Philosopher %d is thinking\n",num);
}

void eat_func(int num){
    int valueBowl1, valueBowl2;
    while(1){
        sem_getvalue(&sem_bowl1,&valueBowl1);
        if(valueBowl1>0){
            sem_wait(&sem_bowl1);
            printf("Philosopher %d is eating in bowl 1\n",num);
            sleep(1);
            printf("Philosopher %d has finished eating in bowl 1\n",num);
            sem_post(&sem_bowl1);
            return;
        }
        sem_getvalue(&sem_bowl2,&valueBowl2);
        if(valueBowl2>0){
            sem_wait(&sem_bowl2);
            printf("Philosopher %d is eating in bowl 2\n",num);
            sleep(1);
            printf("Philosopher %d has finished eating in bowl 2\n",num);
            sem_post(&sem_bowl2);
            return;
        }
    }
}

void get_forks(int num){
    int temp1 = num;
    int temp2 = (num+1)%5;
    sem_wait(&sem_arr[temp1]);
	sem_wait(&sem_arr[temp2]);
    printf("Philosopher %d has got forks %d & %d\n",num,temp1,temp2);
}

void place_forks(int num){
    int temp1 = num;
    int temp2 = (num+1)%5;
    printf("Philosopher %d has placed forks %d & %d\n",num,temp1,temp2);
	sem_post(&sem_arr[temp2]);
    sem_post(&sem_arr[temp1]);
}

void* req_operations(void *arg){
    int temp = *((int*)arg);
    think_func(temp);
    get_forks(temp);
    eat_func(temp);
    place_forks(temp);
    return NULL;
}

int main(){
    
    pthread_t thread[5];
    int i, thread_arg[5];

    for(i=0;i<5;i++){
		sem_init(&sem_arr[i],0,1);
    }
    sem_init(&sem_bowl1,0,1);
    sem_init(&sem_bowl2,0,1);

    for (i=0; i<5; i++){
        thread_arg[i] = i;
        pthread_create(&thread[i],NULL,req_operations,(void*)&thread_arg[i]);
    }
    for (i=0; i<5; i++){
        pthread_join(thread[i],NULL);
    }

}
