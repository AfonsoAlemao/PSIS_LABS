// TODO_1 
// declaration the struct corresponding to the exchanged messages

typedef enum direction_t {UP, DOWN, LEFT, RIGHT} direction_t;

typedef struct connection {
    int ch; // character selected by the user
} connection;


typedef struct movement {
    int ch; // character selected by the user
    direction_t diretion;
} movement;


// TODO_2
//declaration of the FIFO location

#define FIFO_NAME "/tmp/fifo_server"