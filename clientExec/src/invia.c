#include <stdlib.h>
#include <stdio.h>
#include "message.h"
#include "errExit.h"
#include <sys/msg.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
    printf("Hi, I'm Invia program!\n");

    // check command line input arguments
    if (argc < 2) {
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
    int msgid=msgget(msgKey, IPC_CREAT| S_IWUSR);
    if (msgid == -1)
        errExit("msgget failed");

    srand(time(NULL));
    struct message msg;
    msg.mtype=rand()%100 +1;
    msg.num_elements = argc - 2;

    msg.elements= (char*)malloc (sizeof(char*)*msg.num_elements);
    for(int i=0; i<msg.num_elements; i++){
        msg.elements[i]=(char *)malloc(sizeof(char)*strlen(*(argv+i+2));
        strcpy(msg.elements[i], argv[i+2]);
    }
    size_t messageSize= sizeof(struct message) - sizeof(long);
    if(msgsnd(msgid, &msg, messageSize, IPC_NOWAIT)==-1){
        if(errno== EAGAIN)
            printf("Message que piena");
        else
            errExit("invio mex fallito");

    }
    printf("Messaggio inviato!");
    return 0;
}
