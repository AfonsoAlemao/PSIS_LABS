#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include "data_struct.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "funcs.h"
#include <dlfcn.h>
#include <string.h>

int main(){

	int fd_server, fd_client;

	message_type req;

	while((fd_server = open("/tmp/fifo_server", O_RDONLY))== -1){
	  if(mkfifo("/tmp/fifo_server", 0666)!=0){
			printf("problem creating the server fifo\n");
			exit(-1);
	  }else{
		  printf("fifo server created\n");
	  }
	}
	
	while((fd_client = open("/tmp/fifo_client", O_WRONLY))== -1){
	  if(mkfifo("/tmp/fifo_client", 0666)!=0){
			printf("problem creating the client fifo\n");
			exit(-1);
	  }else{
		  printf("fifo client created\n");
	  }
	}

	printf("fifo just opened\n");
	int n;
	int result = 0;
    
    int (*func)();

    char library_name[100];
	void *handle;
	
    strcpy(library_name, "./funcs.so");
    handle = dlopen(library_name, RTLD_LAZY);

    while(1){
        
		n = read(fd_server, &req, sizeof(message_type));

		if(n<=0){
			perror("read ");
			exit(-1);
		}

		printf("%d", req.arg);

		if(req.funct_type == 0) {
			
			// (req.f_name)[strlen(req.f_name) - 1] = '\0';

			// printf("%s", str);
			// printf(" %ld \n", strlen(str));
			// printf("%s \n", req.f_name);
			if((func = dlsym(handle, req.f_name)) == NULL) {
				printf("try again!\n");
				result = -1;
			} else {
				// printf("%d\n", func());
				result = func();
				printf("%d\n", result);
			}

			if(write(fd_client, &result, sizeof(result)) == -1) {
				exit(EXIT_FAILURE);
			}		
		} else if (req.funct_type == 1) {

			// (req.f_name)[strlen(req.f_name) - 1] = '\0';

			// printf("%s", str);
			// printf(" %ld \n", strlen(str));

			if((func = dlsym(handle, req.f_name)) == NULL) {
				printf("try again!\n");
				result = -1;
			} else {
				// printf("%d\n", func());
				result = func(req.arg);
				printf("%d\n", result);
			}

			if(write(fd_client, &result, sizeof(result)) == -1) {
				exit(EXIT_FAILURE);
			}	
		}

		
        
	}

	printf("fifo aberto\n");

	dlclose(handle);
    close(fd_server);
}
