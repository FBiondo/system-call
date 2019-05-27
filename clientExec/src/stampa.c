#include <stdlib.h>
#include <stdio.h>
#include "errExit.h"
#include <sys/msg.h>
#include <string.h>
#include <error.h>
#include <fcntl.h>
int main (int argc, char *argv[]) {
    printf("Hi, I'm Stampa program!\n");
    for(int i=1; i<argc; i++){
        printf("%s ", argv[i]);
    }
    printf("\n");
    return 0;
}
