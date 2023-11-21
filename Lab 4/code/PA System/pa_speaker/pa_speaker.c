#include <stdio.h>
#include <zmq.h>
#include "zhelpers.h"

int main(){
    char line[100];
    char dpt_name[100];
    printf("What is the department of this building? (DEEC, DEI, ...)");
    fgets(line, 100, stdin);
    sscanf(line, "%s", &dpt_name);
    printf("We will broadcast all messages from the president of IST and %s\n", dpt_name);


    void *context = zmq_ctx_new ();
    // Connect to the server using ZMQ_SUB
    void *subscriber = zmq_socket (context, ZMQ_SUB);
    zmq_connect (subscriber, "tcp://localhost:5556");
    
    // subscribe to topics
    zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE,"odd", 3);
     
    char message[100], *dpt, *string, *recv_msg;


    while(1){

        // receive messages
        recv_msg = s_recv(subscriber);
        assert(recv_msg != NULL);
        strcpy(message, recv_msg);
        sscanf (message, "%s %s", dpt, string);

        printf("message from  %s - %s", dpt, string);
        free(string);
        
    }
    zmq_close (subscriber);
    zmq_ctx_destroy (context);
    return 0;
}



//  Weather update client
//  Connects SUB socket to tcp://localhost:5556
//  Collects weather updates and finds avg temp in zipcode

// #include "zhelpers.h" 

// int main (int argc, char *argv [])
// {
//     void *context = zmq_ctx_new ();
//     void *subscriber = zmq_socket (context, ZMQ_SUB);
//     zmq_connect (subscriber, "tcp://localhost:5556");
//     zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE,"odd", 3);
//     while(1) {
//         char *type = s_recv (subscriber);

//         char *string = s_recv (subscriber);
//         printf("recevd message - %s\n", string);
//         free(string);
//         free(type);
//     }

//     zmq_close (subscriber);
//     zmq_ctx_destroy (context);
//     return 0;
// }