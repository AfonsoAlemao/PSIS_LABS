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
    // Connect to the server using ZMQ_REQ

    
    char message[100];
    while(1){

        printf("Please write the message to the students and staff on your buildings! ");
        fgets(message, 100, stdin);


        //send message to server

        printf("Forwarding this message to all: %s", message);
        
    }
}