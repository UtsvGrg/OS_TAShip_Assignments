#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>

#define SOCKET_PATH "socket"
#define LENGTH 4
char temp[LENGTH + 1];

int main(){

	struct timespec a_start, a_stop;
	if(clock_gettime(CLOCK_REALTIME, &a_start) == -1){ // error checking 
		exit(1);
	}
    int sockfd, clientfd, num_bytes;
    socklen_t address_len = sizeof(struct sockaddr_un);
    struct sockaddr_un addr, client_addr;
    // ssize_t num_bytes;

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Unsuccessful socket creation");
        exit(EXIT_FAILURE);
    }
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    if (bind(sockfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1) {
        perror("Error in socket binding");
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 2) == -1) {
        perror("Error to listen for connections");
        exit(EXIT_FAILURE);
    }

    clientfd = accept(sockfd, (struct sockaddr *) &client_addr, &address_len);
    if (clientfd == -1) {
        perror("Error in accepting connection");
        exit(EXIT_FAILURE);
    }

    for(int outerLoop=0; outerLoop<10; outerLoop++){

        int id;
        for(int innerLoop=0; innerLoop<5; innerLoop++){

            num_bytes = read(clientfd, &id, sizeof(int));
            if (num_bytes == -1) {
                perror("Error in reading from client");
                exit(EXIT_FAILURE);
            }
            printf("%d ",id);

            num_bytes = read(clientfd, temp, LENGTH+1);
            if (num_bytes == -1) {
                perror("Error in reading from client");
                exit(EXIT_FAILURE);
            }
            printf("Received message: %s\n", temp);            
        }

        if (write(clientfd,&id,sizeof(int)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

    }
    close(clientfd);
    close(sockfd);
    if(clock_gettime(CLOCK_REALTIME, &a_stop) == -1){ // error checking 
		exit(1);
	}
	double total_time = (a_stop.tv_sec - a_start.tv_sec) + (a_stop.tv_nsec - a_start.tv_nsec)/1e9;
    printf("Time taken to communicate: %f",total_time);
    return 0;
}
