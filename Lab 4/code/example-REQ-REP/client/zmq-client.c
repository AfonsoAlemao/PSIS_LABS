//  Hello World client
#include <zmq.h> 
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

int main (void)
{
    printf ("Connecting to hello world server…\n");
    void *context = zmq_ctx_new ();
    assert(context != NULL);
    void *requester = zmq_socket (context, ZMQ_REQ);
    assert(requester != NULL);
    int rc = zmq_connect (requester, "ipc:///tmp/s1");
    assert(rc == 0);

    size_t send, recv;

    while(1) {
        int n;
        char buffer [10];

        printf("type an integer ");
        scanf("%d", &n);
        printf ("Sending number %d...\n", n);
        send = zmq_send (requester, &n, sizeof(n), 0);
        assert(send != -1);
        //recv = zmq_recv (requester, &n, sizeof(n), 0);
        //assert(recv != -1);
        printf ("Received number %d\n", n);
    }
    zmq_close (requester);
    zmq_ctx_destroy (context);
    return 0;
}
