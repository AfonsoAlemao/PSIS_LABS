#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){


	int fd;

	while((fd = open("/tmp/fifo_teste", O_RDONLY))== -1){
	  if(mkfifo("/tmp/fifo_teste", 0666)!=0){
			printf("problem creating the fifo\n");
			exit(-1);
	  }else{
		  printf("fifo created\n");
	  }
	}
	printf("fifo just opened\n");
	int n;
	int i;
	char str[100];
	int count = 0;
	while(1){

		n = read(fd, str, 100);
		if(n<=0){
			perror("read ");
			exit(-1);
		}
		count ++;
		printf("Str %d %s (%d bytes)\n", count, str, n);

		n = read(fd, &i, 100);
		if(n<=0){
			perror("read ");
			exit(-1);
		}
		count ++;
		printf("Int %d %d (%d bytes)\n", count, i, n);

	}

	printf("fifo aberto\n");

}
