#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <time.h>

#define LENGTH 4
char temp[LENGTH+1];

int main(int argc, char *argv[]){

    const char *name = "mysharedmemory";
    const int SIZE = 4096;
    double total_time;

    int shm_fd, idx;
    void *ptr;
    struct timespec a_start, a_stop;
	if(clock_gettime(CLOCK_REALTIME, &a_start) == -1){ // error checking 
		exit(1);
	}

    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);

    for(int outerLoop=0; outerLoop<10; outerLoop++){
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
        sleep(2);

        shm_fd = shm_open(name,O_RDWR, 0777);
        ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
        if (ptr == MAP_FAILED) {
            perror("ommap");
            exit(1);
        }
        printf("Highest ID: %s\n",(char*)ptr);
        close(shm_fd);
    }
    if(clock_gettime(CLOCK_REALTIME, &a_stop) == -1){ // error checking 
		exit(1);
	}
	total_time = (a_stop.tv_sec - a_start.tv_sec) + (a_stop.tv_nsec - a_start.tv_nsec)/1e9;
    printf("Time Taken to execute the communicate: %f",total_time);
    return 0;
}
