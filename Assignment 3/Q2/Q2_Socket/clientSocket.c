#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "socket"
#define LENGTH 4
char temp[LENGTH + 1];


int main(){
    int sockfd, num_bytes, idx;
    struct sockaddr_un addr;
    // ssize_t num_bytes;

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    if (connect(sockfd,(struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    for(int outerLoop=0; outerLoop<10; outerLoop++){
        for(int innerLoop = 0; innerLoop < 5; innerLoop++){
            for (int i = 0; i < LENGTH; i++) {
                temp[i] = rand() % 26 + 'A';  
            }
            temp[LENGTH] = '\0';  

            idx = outerLoop*5 + innerLoop;
            if (write(sockfd, &idx, sizeof(int)) == -1) {
                perror("Error in writing to the server");
                exit(EXIT_FAILURE);
            }
            if (write(sockfd, temp, LENGTH+1) == -1) {
                perror("Error in writing to the server");
                exit(EXIT_FAILURE);
            }
        }
        num_bytes = read(sockfd, &idx, sizeof(int));
        if (num_bytes == -1) {
            perror("Error in reading from the server");
            exit(EXIT_FAILURE);
        }
        printf("Highest ID: %d\n",idx);
    }

    close(sockfd);
    return 0;
}

