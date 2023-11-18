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
	printf("fifo just opened\n");

    //TODO_5

    // TODO_6

    

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
            break;
        case RIGHT:
            printf("%d Going Right   ", n);
           break;
        case DOWN:
            printf("%d Going Down   ", n);
            break;
        case UP:
            printf("%d Going Up    ", n);
            break;
        }
        //TODO_9
        //TODO_10
    }

 
	return 0;
}