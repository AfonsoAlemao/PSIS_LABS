#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

int main (void)
{
    //  Socket to talk to clients
    void *context = zmq_ctx_new ();
    assert(context != NULL);
    void *responder = zmq_socket (context, ZMQ_REP);
    assert(responder != NULL);
    int rc = zmq_bind (responder, "ipc:///tmp/s1");
    assert (rc == 0);

    size_t send, recv;
    while (1) {
        int n;
        recv = zmq_recv (responder, &n, sizeof(n), 0);
        assert(recv != -1);
        printf ("Received %d\n", n);
        n = n*2;
        sleep(5);
        printf ("Sending Reply %d\n", n);
        send = zmq_send (responder, &n, sizeof(n), 0);
        assert(send != -1);
    }
    return 0;
}
