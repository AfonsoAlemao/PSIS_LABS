//  Weather update client
//  Connects SUB socket to tcp://localhost:5556
//  Collects weather updates and finds avg temp in zipcode

#include "zhelpers.h"

int main (int argc, char *argv [])
{
    void *context = zmq_ctx_new ();
    void *subscriber = zmq_socket (context, ZMQ_SUB);
    zmq_connect (subscriber, "tcp://localhost:5556");
    zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE,"odd", 3);
    while(1) {
        char *type = s_recv (subscriber);

        char *string = s_recv (subscriber);
        printf("recevd message - %s\n", string);
        free(string);
        free(type);
    }

    zmq_close (subscriber);
    zmq_ctx_destroy (context);
    return 0;
}