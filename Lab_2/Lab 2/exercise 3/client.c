#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){

	int fd;
	char str[100];

	while((fd = open("/tmp/fifo_server", O_WRONLY))== -1){
	  if(mkfifo("/tmp/fifo_server", 0666)!=0){
			printf("problem creating the fifo\n");
			exit(-1);
	  }else{
		  printf("fifo created\n");
	  }
	}
	printf("fifo just opened for writing\n");


	while(1){
        
		printf("Choose function:");
		if(fgets(str, 100, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		
		if(write(fd, str, sizeof(str)) == -1) {
			exit(EXIT_FAILURE);
		}

	}
}




