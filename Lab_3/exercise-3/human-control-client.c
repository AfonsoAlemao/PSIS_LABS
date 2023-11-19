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

	initscr();			/* Start curses mode 		*/
	cbreak();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */

    
    int ch;
    int arrow = 1; //1 when there is arrow/ 0 otherwise

    connection.msg_type = 1;
    int n = 0;
    do
    {
        arrow = 1;
    	ch = getch();		
        n++;
        switch (ch)
        {
            case KEY_LEFT:
                mvprintw(0,0,"%d Left arrow is pressed", n);
                connection.diretion = 2;
                break;
            case KEY_RIGHT:
                mvprintw(0,0,"%d Right arrow is pressed", n);
                connection.diretion = 3;
                break;
            case KEY_DOWN:
                mvprintw(0,0,"%d Down arrow is pressed", n);
                connection.diretion = 1;
                break;
            case KEY_UP:
                mvprintw(0,0,"%d :Up arrow is pressed", n);
                connection.diretion = 0;
                break;
            default:
                connection.msg_type = 0;
                arrow = 0;
                    break;
        }
        refresh();			/* Print it on to the real screen */
        //TODO_9
        // prepare the movement message
        if(arrow == 0) {
            continue;
        }

        connection.msg_type = 1;

        //TODO_10
        //send the movement message

        if(write(fd_server, &connection, sizeof(message_type)) == -1) {
            exit(EXIT_FAILURE);
        }

    }while(ch != 27);
    
    
  	endwin();			/* End curses mode		  */

	return 0;
}