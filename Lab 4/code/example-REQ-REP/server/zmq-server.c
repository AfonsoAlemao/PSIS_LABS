#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

int main (void)
{
    //  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "ipc:///tmp/s1");
    assert (rc == 0);
    while (1) {
        int n;
        zmq_recv (responder, &n, sizeof(n), 0);
        printf ("Received %d\n", n);
        n = n*2;
        sleep(5);
        printf ("Sending Reply %d\n", n);
        zmq_send (responder, &n, sizeof(n), 0);
    }
    return 0;
}
