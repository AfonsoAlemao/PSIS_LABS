#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500

int main(int argc, char * argv[]){

    char *result_str;

    result_str = (char *)malloc(MAX * sizeof(char));

    for (int i = 1; i < argc; i++) {
        if(i == 1) {
            strncpy(result_str, argv[i], strlen(argv[i]));
        } else {
            strncat(result_str, argv[i], strlen(argv[i]));
        }
    }

    printf("result_str:  %s\n", result_str);   
    exit(0);
}