//  Hello World client
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../example.pb-c.h"
#include<stdlib.h>
int main (void)
{
    printf ("Connecting to hello world server…\n");
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requester, "tcp://localhost:5555");


/*  struct  SimpleMessage {
        ProtobufCMessage base;
        char *user_string;
        protobuf_c_boolean has_integer_number;
        int32_t integer_number;
        size_t n_float_array;
        float *float_array;
        protobuf_c_boolean has_enumerate_value;
        SimpleMessage__EnumType enumerate_value;
    };
    */ 
   
    SimpleMessage msg = SIMPLE_MESSAGE__INIT;


    int request_nbr;
    for (request_nbr = 0; request_nbr != 10; request_nbr++) {
        int n;
        char buffer [100];
        printf("type the message: ");
        fgets(buffer, 100, stdin);
        msg.str_value = strdup(buffer);

        /* pack the integer_number*/
        msg.has_int_number = 0;

        msg.n_float_array = 4;
        msg.float_array = malloc(sizeof(float)*4);
        for (int i = 0; i< 4; i++)
            msg.float_array[i] = i;
        msg.has_enum_value = 1;
        msg.enum_value = ENUM_TYPE__ENUM_ONE;


        int msg_len = simple_message__get_packed_size(&msg);
        char * msg_buf = malloc(msg_len);
        simple_message__pack(&msg, msg_buf);

        printf ("Sending msg with  %d bytes\n", msg_len);
        zmq_send (requester, msg_buf, msg_len, 0);
        free(msg.str_value);
        free(msg.float_array);

        int receive_n;
        zmq_recv (requester, &receive_n, sizeof(receive_n), 0);
        printf ("Received World %d\n", receive_n);
    }
    zmq_close (requester);
    zmq_ctx_destroy (context);
    return 0;
}