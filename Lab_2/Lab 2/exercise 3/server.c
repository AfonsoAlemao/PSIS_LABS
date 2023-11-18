#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "funcs.h"
#include <dlfcn.h>
#include <string.h>

int main(){

	int fd;

	while((fd = open("/tmp/fifo_server", O_RDONLY))== -1){
	  if(mkfifo("/tmp/fifo_server", 0666)!=0){
			printf("problem creating the fifo\n");
			exit(-1);
	  }else{
		  printf("fifo created\n");
	  }
	}
	printf("fifo just opened\n");
	int n;
	char str[100];
	int result = 0;
    
    int (*func)();

    char library_name[100];
	void *handle;
	
    strcpy(library_name, "./funcs.so");
    handle = dlopen(library_name, RTLD_LAZY);

    while(1){
        
		n = read(fd, str, 100);

		if(n<=0){
			perror("read ");
			exit(-1);
		}

		str[strlen(str) - 1] = '\0';

		// printf("%s", str);
		// printf(" %ld \n", strlen(str));

        if((func = dlsym(handle, str)) == NULL) {
			printf("try again!\n");
		} else {
			// printf("%d\n", func());
			result = func();
			printf("%d\n", result);
		}		
        
	}

	printf("fifo aberto\n");

	dlclose(handle);
    close(fd);
}
