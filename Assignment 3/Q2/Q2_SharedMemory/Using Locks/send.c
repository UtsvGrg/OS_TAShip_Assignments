#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

#define LENGTH 4
char temp[LENGTH+1];

int main(){
    const char *name = "y";
    const int SIZE = 4096;

    int shm_fd, idx, value=1;
    void *ptr;
    struct timespec a_start, a_stop;
	if(clock_gettime(CLOCK_REALTIME, &a_start) == -1){ // error checking 
		exit(1);
	}
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0777);
    ftruncate(shm_fd, SIZE);

    sem_t* sem = sem_open("/my_sem", O_CREAT, 0777, 0);
    if (sem == SEM_FAILED) {
        return 1;
    }

    sem_t* sem2 = sem_open("/my_sem2", O_CREAT, 0777, 0);
    if (sem2 == SEM_FAILED) {
        return 1;
    }


    for(int outerLoop=0; outerLoop<10; outerLoop++){

        // if (sem_wait(sem2) == -1){
        //     perror("sem_wait");
        // }
        shm_fd = shm_open(name,O_RDWR, 0777);
        ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
        if (ptr == MAP_FAILED) {
            perror("ommap");
            exit(1);
        }

        for(int innerLoop = 0; innerLoop < 5; innerLoop++){
            for (int i = 0; i < LENGTH; i++) {
                temp[i] = rand() % 26 + 'A';  
            }
            temp[LENGTH] = '\0';  
            idx = outerLoop*5 + innerLoop;
            sprintf(ptr, "%d ", idx);
            ptr += strlen(ptr);
            sprintf(ptr,"%s\n",temp);
            ptr += strlen(ptr);
        }
        close(shm_fd);

        if (sem_post(sem) == -1){
            perror("sem_wait");
        }

        if (sem_wait(sem2) == -1){
            perror("sem_wait");
        }
        // sleep(2);
        shm_fd = shm_open(name,O_RDWR, 0777);
        ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
        if (ptr == MAP_FAILED) {
            perror("ommap");
            exit(1);
        }
        printf("Highest ID: %s\n",(char*)ptr);
        close(shm_fd);
    }
    
    if (shm_unlink(name) == -1) {
        perror("Error removing shared memory object");
        return 1;
    }
    if (sem_unlink("/my_sem") == -1) {
        perror("Error removing sem1");
        return 1;
    }
    if (sem_unlink("/my_sem2") == -1) {
        perror("Error removing sem2");
        return 1;
    }
    if(clock_gettime(CLOCK_REALTIME, &a_stop) == -1){ // error checking 
		exit(1);
	}
	double total_time = (a_stop.tv_sec - a_start.tv_sec) + (a_stop.tv_nsec - a_start.tv_nsec)/1e9;
    printf("Total time taken to communicate: %f",total_time);
    return 0;
}
