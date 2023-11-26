#include <stdio.h>
#include <zmq.h>
#include "zhelpers.h"

int main(){
    char line[100];
    char dpt_name[100];
    printf("What is your department? (DEEC, DEI, ...)");
    fgets(line, 100, stdin);
    sscanf(line, "%s", dpt_name);
    printf("Hello your Honor, the President of %s\n", dpt_name);

    void *context = zmq_ctx_new ();
    assert(context != NULL);

    // Connect to the server using ZMQ_REQ
    void *requester = zmq_socket (context, ZMQ_REQ);
    assert(requester != NULL);
    int rc = zmq_connect (requester, "ipc:///tmp/s1");
    assert(rc == 0);
     
    char message[100], *recv;
    size_t send;

    while(1){

        printf("Please write the message to the students and staff on your buildings! ");
        fgets(message, 100, stdin);

        send = s_sendmore(requester, dpt_name);

        //send message to server
        send = s_send(requester, message);
        assert(send != -1);

        printf("Forwarding this message to all: %s", message);

        recv = s_recv(requester);
        assert(recv != NULL);
        printf("\n%s\n", recv);

    }
}
