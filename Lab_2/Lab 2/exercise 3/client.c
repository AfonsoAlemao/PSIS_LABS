#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){

	int fd_server, fd_client, n, result;
	char str[100];

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


	while(1){
        
		printf("Choose function:");
		if(fgets(str, 100, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		
		if(write(fd_server, str, sizeof(str)) == -1) {
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




