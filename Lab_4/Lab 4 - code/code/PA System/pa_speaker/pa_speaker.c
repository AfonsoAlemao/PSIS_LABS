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
    
    // subscribe to topics

    
    char message[100];
    while(1){

        // receive messages
        printf("message from  %s - %s", dpt, string);
        free(string);
        
    }
}