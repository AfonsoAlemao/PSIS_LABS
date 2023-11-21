#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include "zhelpers.h"

int main (void){

    void *context = zmq_ctx_new ();
    assert(context != NULL);

    // Bind a ZMQ_REP socket
    void *responder = zmq_socket (context, ZMQ_REP);
    assert(responder != NULL);
    int rc_rep = zmq_bind (responder, "ipc:///tmp/s1");
    assert (rc_rep == 0);

    // Bind a ZMQ_PUB socket

    void *publisher = zmq_socket (context, ZMQ_PUB);
    assert(publisher != NULL);
    int rc_pub = zmq_bind (publisher, "tcp://*:5556");
    assert(rc_pub == 0);
 
    char *recv_message, *dpt, *s, *auxiliar_msg;
    int n_words = 0, i = 0;
    char *department_names[10];
    
    for(int j = 0; j < 10; j++) {
        department_names[j] = (char**) calloc (100, sizeof(char)); 
    }
    
    while (1) {

        recv_message = (char*) calloc (100, sizeof(char));
        dpt = (char*) calloc (100, sizeof(char));
        s = (char*) calloc (100, sizeof(char));

        // receive messages from the microphones
        recv_message = s_recv(responder);
        assert(recv_message != NULL);
        
        n_words = 0;
        for(i = 0; i < strlen(recv_message); i++) {
            if(recv_message[i] == ' ') {
                n_words++;
            }
        }

        if(n_words == 1) {

            for (int kk = 0; kk < 10; kk++) {
                strcpy(auxiliar_msg, department_names[i]);
                strcpy(auxiliar_msg, ' ');
                strcpy(auxiliar_msg, recv_message);

                sscanf (recv_message, "%s %s", dpt, s);
                printf("department %s message %s", dpt, s);  
                // publish message to speakers
                s_sendmore(publisher, dpt);
                s_send (publisher, s);
            }
        } else if(n_words == 2) {
            sscanf (recv_message, "%s %s", dpt, s);
            printf("department %s message %s", dpt, s);  
            // publish message to speakers
            s_sendmore(publisher, dpt);
            s_send (publisher, s);
        } 

        free(recv_message);
        free(dpt);
        free(s);

    }

    zmq_close (responder);
    zmq_close (publisher);
    zmq_ctx_shutdown (context);
    return 0;
}


// #include <zmq.h>
// #include <string.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <assert.h>

// int main (void)
// {
//     //  Socket to talk to clients
//     void *context = zmq_ctx_new ();
//     assert(context != NULL);
//     void *responder = zmq_socket (context, ZMQ_REP);
//     assert(responder != NULL);
//     int rc = zmq_bind (responder, "ipc:///tmp/s1");
//     assert (rc == 0);

//     size_t send, recv;
//     while (1) {
//         int n;
//         recv = zmq_recv (responder, &n, sizeof(n), 0);
//         assert(recv != -1);
//         printf ("Received %d\n", n);
//         n = n*2;
//         sleep(5);
//         printf ("Sending Reply %d\n", n);
//         send = zmq_send (responder, &n, sizeof(n), 0);
//         assert(send != -1);
//     }
//     return 0;
// }






// #include "zhelpers.h"
// #include <stdlib.h>
// #include <assert.h>
// #include <unistd.h>
 
// int main (void)
// {
//     void *context = zmq_ctx_new ();
//     void *publisher = zmq_socket (context, ZMQ_PUB);
//     int rc = zmq_bind (publisher, "tcp://*:5556");
//     assert(rc == 0);
//     while (1) {
//         char message[100];
//         int n = rand();
//         if (n%2 == 0){
//             s_sendmore(publisher, "even");
//         }else{
//             s_sendmore(publisher, "odd");
//         }
//         sprintf(message, "%d\n", n);
//         printf(message);
//         s_send (publisher, message);
//         sleep(1);
//     }
//     zmq_close (publisher);
//     zmq_ctx_shutdown (context);
//     return 0;
// }
