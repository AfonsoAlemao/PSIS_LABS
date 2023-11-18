
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>


#define WINDOW_SIZE 15
typedef enum direction_t {UP, DOWN, LEFT, RIGHT} direction_t;

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
	initscr();		    	/* Start curses mode 		*/
	cbreak();				/* Line buffering disabled	*/
    keypad(stdscr, TRUE);   /* We get F1, F2 etc..		*/
	noecho();			    /* Don't echo() while we do getch */

    /* creates a window and draws a border */
    WINDOW * my_win = newwin(WINDOW_SIZE, WINDOW_SIZE, 0, 0);
    box(my_win, 0 , 0);	
	wrefresh(my_win);

    /* place the curso in the middle of the window */
    int pos_x = WINDOW_SIZE/2;
    int pos_y = WINDOW_SIZE/2;

    int sleep_delay;
    direction_t  direction;
    int n = 0;
    int ch = 'x';
    while (1)
    {
        sleep_delay = random()%700000;
        usleep(sleep_delay);

        /*deletes old place */
        wmove(my_win, pos_y, pos_x);
        waddch(my_win,' ');

        /* claculates new direction */
        direction = random_direction();

        /* claculates new mark position */
        new_position(&pos_x, &pos_y, direction);

        
        /* draw mark on new position */
        wmove(my_win, pos_y, pos_x);
        waddch(my_win,ch| A_BOLD);
    	wrefresh(my_win);			
    }
    
  	endwin();			/* End curses mode		  */

	return 0;
}