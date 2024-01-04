#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
  
#include "../example.pb-c.h"

void *context;



int main (void)
{
    //  Socket to talk to clients
    context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:5555");
    assert (rc == 0);
    zmq_msg_t zmq_msg;
    zmq_msg_init (&zmq_msg);

 

    SimpleMessage * simple_msg;

 
    while (1) { 
        int msg_len = zmq_recvmsg (responder, &zmq_msg, 0); 
        printf ("Received %d bytes\n", msg_len);

        void * msg_data = zmq_msg_data (& zmq_msg);
        simple_msg = simple_message__unpack(NULL, msg_len, msg_data);

        printf("data received\n");

        printf("\tstring %s", simple_msg->str_value);

        printf("\toptional integer %d %d\n", simple_msg->has_int_number, 
                          simple_msg->int_number);

        printf("\tarray of %ld floats \n", simple_msg->n_float_array);
        for (int i = 0; i< simple_msg->n_float_array; i++){
            printf("\t\t%f\n", simple_msg->float_array[i]);
        }

        printf("\t%d %d\n", simple_msg->has_enum_value, 
                          simple_msg->enum_value);

        sleep (1);          //  Do some 'work'

        int n_response = strlen(simple_msg->str_value);
        zmq_send (responder,& n_response, sizeof(n_response), 0);
        zmq_msg_close(msg_data);
        free(simple_msg);
    }
    return 0;
}