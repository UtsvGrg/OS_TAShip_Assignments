#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#define LENGTH 4  
#define BUFFER_SIZE 1024

char buffer[BUFFER_SIZE];

int main(){
    char* str_arr[50];
    char temp[LENGTH+1];
    int f1, f2, idx;
    struct timespec a_start, a_stop;
	if(clock_gettime(CLOCK_REALTIME, &a_start) == -1){ // error checking 
		exit(1);
	}

    if (mkfifo("fifo_p1", 0777) < 0) {
        perror("Error creating FIFO1");
        exit(1);
    }

    for(int outerLoop=0; outerLoop<10; outerLoop++){

        f1 = open("fifo_p1", O_WRONLY);
        if (f1 < 0) {
            perror("Error opening FIFO for writing");
            exit(1);
        }
        
        for(int innerLoop = 0; innerLoop < 5; innerLoop++){
            for (int i = 0; i < LENGTH; i++) {
                temp[i] = rand() % 26 + 'A';  
            }
            temp[LENGTH] = '\0';  
            // str_arr[outerLoop] = temp;

            idx = outerLoop*5 + innerLoop;
            write (f1, &idx, sizeof(int));

            if (write(f1, temp, LENGTH+1) < 0) {
                perror("Error writing to FIFO");
                exit(1);
            }
        }

        close(f1);

        f2 = open("fifo_p2", O_RDONLY);
        if (f2 < 0) {
            perror("Error opening FIFO for reading");
            exit(1);
        }

        int bytes_read = read(f2,&idx,sizeof(int));
        if (bytes_read < 0) {
            perror("Error reading from FIFO");
            exit(1);
        }

        printf("Highest ID: %d\n",idx);

        close(f2);
    }
	if(clock_gettime(CLOCK_REALTIME, &a_stop) == -1){ // error checking 
		exit(1);
	}
	double total_time = (a_stop.tv_sec - a_start.tv_sec) + (a_stop.tv_nsec - a_start.tv_nsec)/1e9;
    printf("Time taken to communicate: %f",total_time);
    return 0;
}
