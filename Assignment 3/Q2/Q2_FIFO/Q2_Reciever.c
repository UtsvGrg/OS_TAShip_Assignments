#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define LENGTH 4  
#define BUFFER_SIZE 5

char buffer[BUFFER_SIZE];

int main(){
    int f1, f2, req;

    if (mkfifo("fifo_p2", 0777) < 0) {
        perror("Error creating FIFO2");
        exit(1);
    }

    for(int outerLoop=0; outerLoop<10; outerLoop++){
        
        f1 = open("fifo_p1", O_RDONLY);
        if (f1 < 0) {
            perror("Error opening FIFO for reading");
            exit(1);
        }

        for(int innerLoop=0; innerLoop<5; innerLoop++){

            read (f1, &req, sizeof(int));
            printf("%d ",req);

            int bytes_read = read(f1, buffer, BUFFER_SIZE);
            if (bytes_read < 0) {
                perror("Error reading from FIFO");
                exit(1);
            }

            printf("%s\n",buffer);
            
        }

        close(f1);

        f2 = open("fifo_p2", O_WRONLY);
        if (f2 < 0) {
            perror("Error opening FIFO for writing");
            exit(1);
        }

        if (write(f1,&req,sizeof(int)) < 0) {
            perror("Error writing to FIFO");
            exit(1);
        }

        close(f2);
    }

    return 0;
}
