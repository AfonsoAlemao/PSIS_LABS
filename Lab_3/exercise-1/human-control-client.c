#include <ncurses.h>
#include "remote-char.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  
 #include <ctype.h> 
 #include <stdlib.h>
 

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
    printf("Choose function and an argument:");
    if((ch_user = fget()) == NULL) {
        exit(EXIT_FAILURE);
    }

    // TODO_6
    // send connection message
    message_type connection;

    connection.ch = ch_user;
    


	initscr();			/* Start curses mode 		*/
	cbreak();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */

    
    int ch;

    m.msg_type = 1;
    int n = 0;
    do
    {
    	ch = getch();		
        n++;
        switch (ch)
        {
            case KEY_LEFT:
                mvprintw(0,0,"%d Left arrow is pressed", n);
                break;
            case KEY_RIGHT:
                mvprintw(0,0,"%d Right arrow is pressed", n);
                break;
            case KEY_DOWN:
                mvprintw(0,0,"%d Down arrow is pressed", n);
                break;
            case KEY_UP:
                mvprintw(0,0,"%d :Up arrow is pressed", n);
                break;
            default:
                ch = 'x';
                    break;
        }
        refresh();			/* Print it on to the real screen */
        //TODO_9
        // prepare the movement message

        //TODO_10
        //send the movement message
        
    }while(ch != 27);
    
    
  	endwin();			/* End curses mode		  */

	return 0;
}