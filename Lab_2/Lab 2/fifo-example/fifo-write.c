#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(){


	int fd;
	char str[100];
	int n;
	while((fd = open("/tmp/fifo_teste", O_WRONLY))== -1){
	  if(mkfifo("/tmp/fifo_teste", 0666)!=0){
			printf("problem creating the fifo\n");
			exit(-1);
	  }else{
		  printf("fifo created\n");
	  }
	}
	printf("fifo just opened for writing\n");


	while(1){

		printf("write a string:");
		fgets(str, 100, stdin);
		write(fd, str, 100);

		printf("write a number:");
		fgets(str, 100, stdin);
		sscanf(str, "%d", &n);
		write(fd, &n, sizeof(n));

	}

}
