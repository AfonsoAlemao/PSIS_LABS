#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include "data_struct.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){

	int fd_server, fd_client, n, result;
	char str[100];

	message_type res;

	while((fd_server = open("/tmp/fifo_server", O_WRONLY))== -1){
	  if(mkfifo("/tmp/fifo_server", 0666)!=0){
			printf("problem creating the server fifo\n");
			exit(-1);
	  }else{
		  printf("fifo server created\n");
	  }
	}
	printf("fifo server just opened for writing\n");

	while((fd_client = open("/tmp/fifo_client", O_RDONLY))== -1){
	  if(mkfifo("/tmp/fifo_client", 0666)!=0){
			printf("problem creating the fifo client\n");
			exit(-1);
	  }else{
		  printf("fifo client created\n");
	  }
	}
	
	int argument;
	char func_name[100];


	while(1){
        
		printf("Choose function and an argument:");
		if(fgets(str, 100, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}

		if (sscanf(str, "%99s %d", func_name, &argument) == 1) {
			argument = -1;
			res.funct_type = 0;
		} else {
			res.funct_type = 1;
		}

		res.arg = argument;
		strcpy(res.f_name, func_name);

		// printf("%d\n", res.arg);
		
		if(write(fd_server, &res, sizeof(message_type)) == -1) {
			exit(EXIT_FAILURE);
		}

		n = read(fd_client, &result, sizeof(int));

		if(n<=0){
			perror("read ");
			exit(-1);
		}

		printf("\n result : %d \n", result);

	}

	close(fd_server);
	close(fd_client);
}




