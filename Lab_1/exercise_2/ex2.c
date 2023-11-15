#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500

int main(int argc, char * argv[]){

    char *result_str;

    result_str = (char *)calloc(MAX, sizeof(char));

    char *adress;
    char *start;

    start = result_str;

    for (int i = 1; i < argc; i++) {

        for (adress = argv[i]; *(adress) != '\0'; adress++) {
            *result_str++ = *adress;
        }
    }
    *result_str = '\0';

    printf("result_str:  %s\n", start);   
    exit(0);
}