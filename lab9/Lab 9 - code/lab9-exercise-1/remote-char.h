
typedef enum direction_t {UP, DOWN, LEFT, RIGHT} direction_t;

typedef struct remote_char_t
{   
    int msg_type; /* 0 join   1 - move  2- subscribe*/
    char subscriber_name[100];
    char creditcard_number [100];
    char ch; 
    direction_t direction ; 
    /* data */
}remote_char_t;


typedef struct remote_display_m
{   
    char ch; 
    int x, y;
}remote_display_m;

typedef struct subscrition_ok_m
{   
    int random_secret;
}subscrition_ok_m;


#define FIFO_NAME "/tmp/fifo_snail"
