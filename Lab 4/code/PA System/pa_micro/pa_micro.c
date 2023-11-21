#include <stdio.h>
#include <zmq.h>
#include "zhelpers.h"

int main(){
    char line[100];
    char dpt_name[100];
    printf("What is your department? (DEEC, DEI, ...)");
    fgets(line, 100, stdin);
    sscanf(line, "%s", &dpt_name);
    printf("Hello your Honor, the President of %s\n", dpt_name);

    void *context = zmq_ctx_new ();
    assert(context != NULL);

    // Connect to the server using ZMQ_REQ
    void *requester = zmq_socket (context, ZMQ_REQ);
    assert(requester != NULL);
    int rc = zmq_connect (requester, "ipc:///tmp/s1");
    assert(rc == 0);
     
    char message[100];
    size_t send;

    while(1){

        printf("Please write the message to the students and staff on your buildings! ");
        fgets(message, 100, stdin);


        //send message to server
        send = s_send(requester, message);
        assert(send != -1);

        printf("Forwarding this message to all: %s", message);
        
    }
}




//  Hello World client
// #include <zmq.h> 
// #include <string.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <assert.h>

// int main (void)
// {
//     printf ("Connecting to hello world server…\n");
//     void *context = zmq_ctx_new ();
//     assert(context != NULL);
//     void *requester = zmq_socket (context, ZMQ_REQ);
//     assert(requester != NULL);
//     int rc = zmq_connect (requester, "ipc:///tmp/s1");
//     assert(rc == 0);

//     size_t send, recv;

//     while(1) {
//         int n;
//         char buffer [10];

//         printf("type an integer ");
//         scanf("%d", &n);
//         printf ("Sending number %d...\n", n);
//         send = zmq_send (requester, &n, sizeof(n), 0);
//         assert(send != -1);
//         recv = zmq_recv (requester, &n, sizeof(n), 0);
//         assert(recv != -1);
//         printf ("Received number %d\n", n);
//     }
//     zmq_close (requester);
//     zmq_ctx_destroy (context);
//     return 0;
// }
