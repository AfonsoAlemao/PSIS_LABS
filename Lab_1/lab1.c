#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char line[100];
    int n;
    printf("What is your student number");

    if(fgets(line, 100, stdin) == NULL) {
        exit(EXIT_FAILURE);
    }
    
    if (sscanf(line, "%d", &n) != 1){
        printf("invalid Number\n");
        exit(-1);
    }
    srandom(n);
    // every time we run the program it runs with the same seed, meaning the random number will not change, remaining the same
    printf("your own random %ld\n", random());   
    exit(0);
}