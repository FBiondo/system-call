#include <stdlib.h>
#include <stdio.h>
#include "message.h"
#include "errExit.h"
#include <sys/msg.h>
#include <string.h>
#include <error.h>
#include <fcntl.h>

int main (int argc, char *argv[]) {
    printf("Hi, I'm Invia program!\n");

    // check command line input arguments
    if (argc != 2) {
        printf("Usage: %s message_queue_key\n", argv[0]);
        exit(1);
    }
    // read the message queue key defined by user
    int msgKey= atoi(argv[1]);

    if(msgKey<=0){
        printf("msg failed pls put a msg grater than zero");
        exit(1);
    }
    // get the message queue identifier
    int msgid=msgget(msgKey,S_IRUSR | S_IWUSR);
    if (msgid == -1)
        errExit("msgget failed");

    struct message msg;
    msg.mtype=1;
    msg.num_elements = argc - 2;

    msg.elements= (char*)malloc (sizeof(char*)*msg.num_elements);
    for(int i=0; i<msg.num_elements; i++){
        msg.elements[i]=(char *)malloc(sizeof(char)*strlen(*(argv+i+2));
        strcpy(msg.elements[i], *(argv +i+2));
    }
    return 0;
}
