
#include <ncurses.h>
#include "remote-char.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  
#include <stdlib.h>

#define WINDOW_SIZE 15

direction_t random_direction(){
    return  random()%4;

}
void new_position(int* x, int *y, direction_t direction){
    switch (direction)
    {
    case UP:
        (*x) --;
        if(*x ==0)
            *x = 2;
        break;
    case DOWN:
        (*x) ++;
        if(*x ==WINDOW_SIZE-1)
            *x = WINDOW_SIZE-3;
        break;
    case LEFT:
        (*y) --;
        if(*y ==0)
            *y = 2;
        break;
    case RIGHT:
        (*y) ++;
        if(*y ==WINDOW_SIZE-1)
            *y = WINDOW_SIZE-3;
        break;
    default:
        break;
    }
}

int main()
{	
    int fd_server;

	// TODO_3
    // create and open the FIFO for reading

    while((fd_server = open(FIFO_NAME, O_RDONLY))== -1){
	  if(mkfifo("/tmp/fifo_server", 0666)!=0){
			printf("problem creating the server fifo\n");
			exit(-1);
	  }else{
		  printf("fifo server created\n");
	  }
	}


    // ncurses initialization
	initscr();		    	
	cbreak();				
    keypad(stdscr, TRUE);   
	noecho();			    


    /* creates a window and draws a border */
    WINDOW * my_win = newwin(WINDOW_SIZE, WINDOW_SIZE, 0, 0);
    box(my_win, 0 , 0);	
	wrefresh(my_win);

    /* information about the character */
    int n;
    message_type req;
    element_user elements[128];
    int n_clients = -1;
    int i = 0;

    while (1)
    {
        // TODO_7
        // receive message from the clients
        n = read(fd_server, &req, sizeof(message_type));

		if(n<=0){
			perror("read ");
			exit(-1);
		}

        //TODO_8
        // process connection messages
        if(req.msg_type == 0) {

            n_clients++;
            elements[n_clients].ch = req.ch;
            
            elements[n_clients].pos_x = WINDOW_SIZE/2;
            elements[n_clients].pos_y = WINDOW_SIZE/2;

            wmove(my_win,  elements[n_clients].pos_x, elements[n_clients].pos_y);
            waddch(my_win,' ');
            i = n_clients;

        } else if (req.msg_type == 1) { //movement type
            // TODO_11
            // process the movement message
            /*deletes old place */

            for(i = 0; i < n_clients; i++) {
                if(elements[i].ch == req.ch) {
                    break;
                }
            }

            wmove(my_win,  elements[i].pos_x, elements[i].pos_y);
            waddch(my_win,' ');

            /* claculates new mark position */
            new_position(&(elements[i].pos_x), &(elements[i].pos_y), req.diretion);
        }
        
        /* draw mark on new position */
        wmove(my_win, elements[i].pos_x, elements[i].pos_y);
        waddch(my_win, elements[i].ch| A_BOLD);
        wrefresh(my_win);			
    }
  	endwin();			/* End curses mode		  */

	return 0;
}