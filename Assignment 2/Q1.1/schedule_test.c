#include <stdio.h>
#include <unistd.h> // MOVE TO DESKTOP
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sched.h>
#include<sys/wait.h>
#include <string.h>

#define ull unsigned long long int 
double total_time;
FILE *fptr;
int set_priority;

void* count_a(){
	struct timespec a_start, a_stop;
	if(clock_gettime(CLOCK_REALTIME, &a_start) == -1){ // error checking 
		exit(1);
	}
	for(ull i=1;i<4294967296;i++){;} //counting
	if(clock_gettime(CLOCK_REALTIME, &a_stop) == -1){ // error checking 
		exit(1);
	}
	total_time = (a_stop.tv_sec - a_start.tv_sec) + (a_stop.tv_nsec - a_start.tv_nsec)/1e9;
	fprintf(fptr,"o: %f %d\n", total_time, set_priority);
	return NULL;
}

void* count_b(){
	struct sched_param def;	
	struct timespec b_start, b_stop;
	def.sched_priority = set_priority;
	pthread_setschedparam(pthread_self(),1,&def);
	if(clock_gettime(CLOCK_REALTIME, &b_start) == -1){ // error checking 
		exit(1);
	}
	for(ull i=1;i<4294967296;i++){;} //counting
	if(clock_gettime(CLOCK_REALTIME, &b_stop) == -1){ // error checking 
		exit(1);
	}
	total_time = (b_stop.tv_sec - b_start.tv_sec) + (b_stop.tv_nsec - b_start.tv_nsec)/1e9;
	fprintf(fptr,"f: %f %d\n", total_time, set_priority);
	return NULL;
}

void* count_c(){
	struct sched_param def;
	struct timespec c_start, c_stop;
	def.sched_priority = set_priority;
	pthread_setschedparam(pthread_self(),2,&def);
	if(clock_gettime(CLOCK_REALTIME, &c_start) == -1){ // error checking 
		exit(1);
	}
	for(ull i=1;i<4294967296;i++){;} //counting
	if(clock_gettime(CLOCK_REALTIME, &c_stop) == -1){ // error checking 
		exit(1);
	}
	total_time = (c_stop.tv_sec - c_start.tv_sec) + (c_stop.tv_nsec - c_start.tv_nsec)/1e9;
	fprintf(fptr,"r: %f %d\n", total_time,set_priority);
	return NULL;
}

int main(){
	fptr = fopen("fileopen.txt","w");
	pthread_t pth_a,pth_b,pth_c;
	int ra, rb, rc;
	for(int i=0;i<10;i++){
		set_priority+=5;
		ra = pthread_create(&pth_a, NULL, count_a, NULL);
		rb = pthread_create(&pth_b, NULL, count_b, NULL);
		rc = pthread_create(&pth_c, NULL, count_c, NULL);
		ra = pthread_join(pth_a,NULL);
		rb = pthread_join(pth_b,NULL);
		rc = pthread_join(pth_c,NULL);
	}
	fclose(fptr);
	pid_t pid = fork();
    int status;
    if(pid<0){
        printf("Failed to fork child process");
        exit(1); 
    }
    else if(pid==0){
		system("./q1a.sh");
    }
	return 0;
}