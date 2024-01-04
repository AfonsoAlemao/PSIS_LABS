#include "../remote-char.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

#include <zmq.h>
#include "zhelpers.h"

int main(){	 


    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    int rc = zmq_connect (requester, "tcp://localhost:55555");
    if (rc!=0){
        printf("error connecting REQ socket");
        exit(-1);
    }
	printf("socket connected\n");


    char ch;
    do{
        printf("what is your symbol(a..z)?: ");
        ch = getchar();
        ch = tolower(ch);  
    }while(!isalpha(ch));


    int msg_type = 0;
    zmq_send(requester, &msg_type, sizeof(msg_type), ZMQ_SNDMORE);

    // TODO 7 - create and fill a message of type  client_connection_req 
    //           and send the packed message to the server 
    remote_char_t m; 
    m.ch = ch;
    zmq_send (requester, &m, sizeof(remote_char_t), 0);
    // TODO 7

    char * str = s_recv(requester);
    free(str);   
    

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

        int msg_type = 1;
        zmq_send(requester, &msg_type, sizeof(msg_type), ZMQ_SNDMORE);

        // TODO 10 - create and fill a message of type  movement_req  
        //           and send the packed message to the server
        m.direction = direction;
        m.msg_type = 1;
        zmq_send (requester, &m, sizeof(remote_char_t), 0);
        // TODO 10

        char * str = s_recv(requester);
        free(str);   
   }

 
	return 0;
}