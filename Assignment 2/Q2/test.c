#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(){
	float matrix[4][3] = {{4.5,2.45,5.67},{1.2,7.89,23.5},{25.12,44.232,43.67},{32.12,54.43,76.23}};
	float matrix2[4][3];	
	long t = syscall(451,matrix,matrix2,4,3);
	for(int i=0; i<4; i++){
		for(int j=0; j<3; j++){
			printf("%f ",matrix2[i][j]);
		}
	printf("\n");		
	}
		return t;
}
