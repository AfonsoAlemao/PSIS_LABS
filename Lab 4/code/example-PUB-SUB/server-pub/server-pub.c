#include "zhelpers.h"
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

int main (void)
{
    void *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_PUB);
    int rc = zmq_bind (publisher, "tcp://*:5556");
    assert(rc == 0);
    while (1) {
        char message[100];
        int n = rand();
        if (n%2 == 0){
            s_sendmore(publisher, "even");
        }else{
            s_sendmore(publisher, "odd");
        }
        sprintf(message, "%d\n", n);
        printf(message);
        s_send (publisher, message);
        sleep(1);
    }
    zmq_close (publisher);
    zmq_ctx_shutdown (context);
    return 0;
}
