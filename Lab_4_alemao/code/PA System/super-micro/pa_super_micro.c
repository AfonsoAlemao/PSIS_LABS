#include <stdio.h>
#include <zmq.h>
#include "zhelpers.h"

int main(){
    printf("Hello your Honor, the president of IST!");
    
    void *context = zmq_ctx_new ();
    assert(context != NULL);
    
    // Connect to the server using ZMQ_REQ
    
    void *requester = zmq_socket (context, ZMQ_REQ);
    assert(requester != NULL);
    int rc = zmq_connect (requester, "ipc:///tmp/s1");
    assert(rc == 0);

    size_t send;
    
    char message[100], *recv;
    
    while(1){

        printf("Please write the message to your students and staff! ");
        fgets(message, 100, stdin);

        //send message to server
        
        printf("Forwarding this message to all: %s", message);
        send = s_send (requester, message);
        assert(send != -1);

        recv = s_recv(requester);
        assert(recv != NULL);
        printf("\n%s\n", recv);
        fflush(stdout);

    }

    zmq_close (requester);
    zmq_ctx_destroy (context);
    return 0;
}