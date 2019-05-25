#include <stdlib.h>
#include <stdio.h>
#include "message.h"
#include "errExit.h"
#include <sys/msg.h>
#include <string.h>
#include <error.h>
#include <fcntl.h>

char * salva = "salva";
char* stampa = "stampa";
char *invia = "invia";

int main (int argc, char *argv[]) {
    printf("Hi, I'm ClientExec program!\n");
    return 0;
}
