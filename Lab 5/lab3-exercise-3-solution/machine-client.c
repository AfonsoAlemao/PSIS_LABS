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

    //TODO_4
    // create and open the FIFO for writing

    int fd;
    while((fd = open(FIFO_NAME, O_WRONLY))== -1){
	  if(mkfifo(FIFO_NAME, 0666)!=0){
			printf("problem creating the fifo\n");
			exit(-1);
	  }else{
		  printf("fifo created\n");
	  }
	}
	printf("fifo just opened\n");

    //TODO_5
    // read the character from the user
    char ch;
    do{
        printf("what is your symbol(a..z)?: ");
        ch = getchar();
        ch = tolower(ch);  
    }while(!isalpha(ch));

    // TODO_6
    // send connection message
    remote_char_t m;
    m.msg_type = 0;
    m.ch = ch;
    write(fd, &m, sizeof(remote_char_t));
    
    

    int sleep_delay;
    direction_t direction;
    int n = 0;
    while (1)
    {
        n++;
        sleep_delay = random()%700000;
        usleep(sleep_delay);
        direction = random()%4;
        switch (direction)
        {
        case LEFT:
           printf("%d Going Left   \n", n);
            break;
        case RIGHT:
            printf("%d Going Right   \n", n);
           break;
        case DOWN:
            printf("%d Going Down   \n", n);
            break;
        case UP:
            printf("%d Going Up    \n", n);
            break;
        }

        //TODO_9
        // prepare the movement message
        m.direction = direction;
        m.msg_type = 1;

        //TODO_10
        //send the movement message
        write(fd, &m, sizeof(m));
    }

 
	return 0;
}