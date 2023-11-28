#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include "zhelpers.h"

int main (void){

    void *context = zmq_ctx_new ();
    // Bind a ZMQ_REP socket


    // Bind a ZMQ_PUB socket



    while (1) {

        // receive messages from the microphones

        printf("department %s message %s", dpt, s); 

        // publish message to speakers

    }
    return 0;
}