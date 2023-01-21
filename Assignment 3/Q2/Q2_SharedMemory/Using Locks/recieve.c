#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>

#define LENGTH 4
char temp[LENGTH+1];

int main(){

    const char *name = "y";
    const int SIZE = 4096;

    int shm_fd, idx, value=1;
    void *ptr;

    sem_t* sem = sem_open("/my_sem", 0);
    if (sem == SEM_FAILED) {
    return 1;
    }

    sem_t* sem2 = sem_open("/my_sem2", 0);
    if (sem2 == SEM_FAILED) {
    return 1;
    }

    for(int outerLoop=0; outerLoop<10; outerLoop++){


        if (sem_wait(sem) == -1){
            perror("sem_wait");
        }

        shm_fd = shm_open(name,O_RDWR, 0777);
        ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
        if (ptr == MAP_FAILED) {
            perror("pmmap");
            exit(1);
        }
        printf("%s\n",(char*)ptr);
        close(shm_fd);

        shm_fd = shm_open(name,O_RDWR, 0777);
        ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
        if (ptr == MAP_FAILED) {
            perror("ommap");
            exit(1);
        }

        idx = outerLoop*5 + 4;
        sprintf(ptr, "%d ", idx);
        ptr += strlen(ptr);
        close(shm_fd);

        if (sem_post(sem2) == -1){
            perror("sem_wait");
        }
        // sleep(2);
    }
    return 0;
}
