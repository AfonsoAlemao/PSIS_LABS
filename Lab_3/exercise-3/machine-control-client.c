#include "remote-char.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

int main()
{	
    int fd_server;
    char ch_user;

    //TODO_4
    // create and open the FIFO for writing
    while((fd_server = open(FIFO_NAME, O_WRONLY))== -1){
	  if(mkfifo("/tmp/fifo_server", 0666)!=0){
			printf("problem creating the server fifo\n");
			exit(-1);
	  }else{
		  printf("fifo server created\n");
	  }
	}
	printf("fifo server just opened for writing\n");

    //TODO_5
    // read the character from the user
    printf("Choose your character:");
    ch_user = getchar();

    // TODO_6
    // send connection message
    message_type connection;

    connection.ch = ch_user;
    connection.msg_type = 0;

    if(write(fd_server, &connection, sizeof(message_type)) == -1) {
        exit(EXIT_FAILURE);
    }

    

    int sleep_delay;
    direction_t direction;
    int n = 0;
    while (1)
    {
        sleep_delay = random()%700000;
        usleep(sleep_delay);
        direction = random()%4;
        n++;
        switch (direction)
        {
        case LEFT:
            printf("%d Going Left   ", n);
            connection.diretion = 2;
            break;
        case RIGHT:
            printf("%d Going Right   ", n);
            connection.diretion = 3;
           break;
        case DOWN:
            printf("%d Going Down   ", n);
            connection.diretion = 1;
            break;
        case UP:
            printf("%d Going Up    ", n);
            connection.diretion = 0;
            break;
        }
        //TODO_9
        connection.msg_type = 1;
        //TODO_10
        if(write(fd_server, &connection, sizeof(message_type)) == -1) {
            exit(EXIT_FAILURE);
        }
    }

 
	return 0;
}