
#include <ncurses.h>
#include "remote-char.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  
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
    int ch;
    int pos_x;
    int pos_y;
    int n;
    message_type req;



    direction_t  direction;

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

            ch = req.ch;
            pos_x = WINDOW_SIZE/2;
            pos_y = WINDOW_SIZE/2;

             /* creates a window and draws a border */
            WINDOW * my_win = newwin(WINDOW_SIZE, WINDOW_SIZE, 0, 0);
            box(my_win, 0 , 0);	
            wrefresh(my_win);
            
            /* draw mark on new position */
            wmove(my_win, pos_y, pos_x);
            waddch(my_win,ch| A_BOLD);
            wrefresh(my_win);

        }
        

        // TODO_11
        // process the movement message
        
        /* draw mark on new position */
        wmove(my_win, pos_x, pos_y);
        waddch(my_win,ch| A_BOLD);
        wrefresh(my_win);			
    }
  	endwin();			/* End curses mode		  */

	return 0;
}