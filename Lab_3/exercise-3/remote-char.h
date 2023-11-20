// TODO_1 
// declaration the struct corresponding to the exchanged messages

typedef enum direction_t {UP, DOWN, LEFT, RIGHT} direction_t;

typedef struct message_type {
    int ch; // character selected by the user
    int msg_type; //0 for connection, 1 otherwise
    direction_t diretion;
} message_type;

// TODO_2
//declaration of the FIFO location

#define FIFO_NAME "/tmp/fifo_server"

typedef struct character_information {
    int pos_x; 
    int pos_y; 
    char ch;
} character_information;