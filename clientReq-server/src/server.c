#include <stdlib.h>
#include <stdio.h>
#include <sys/sem.h>
#include "semaphore.h"
#include "errExit.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>


// definition of the union semun


char * FIFOSERVER ="/tmp/FIFOSERVER";
char * FIFOSCLIENT ="/tmp/FIFOCLIENT";

int main (int argc, char *argv[]) {

    struct  myRequest request;
    printf("Hi, I'm Server program!\n");
    printf("<Server> Making FIFO...\n");
    // make a FIFO with the following permissions:
    // user:   READ, write
    if (mkfifo(FIFOSERVER,  S_IWUSR | S_IRUSR) == -1)
        errExit("mkfifo failed");

    //SEMAPHORE to manage the request of clientREQ
    int semid =semget(IPC_PRIVATE,1, IPC_CREAT | S_IWUSR | S_IRUSR);
    if(semid == -1)
        errExit("semget failed");

    // inizialize sem=1
    union semun arg;
    arg.val=1;
    if(semctl(semid, /*ignored*/ , SETVAL, arg)== -1)
        errExit("semctl failed");

    // Wait for clients in read-only mode. The open blocks the calling process
    // until another process opens the same FIFO in write-only mode
    printf("<Server> waiting for a client...\n");
    int fd = open(FIFOSERVER, O_RDONLY);
    if (fd == -1)
        errExit("open failed");


    printf("<Server> waiting for a req...\n");
    // Reading  FIFO.
    int bR = read(fd, &request, sizeof(struct myRequest));

    // Checking  FIFO's data
    if (bR == -1)
        printf("<Server> it looks like the FIFO is broken");


    // Close the FIFO
    if (close(serverFIFO) != 0)
        errExit("close failed");

    printf("<Server> removing FIFO...\n");
    // Remove the FIFO
    if (unlink(path2ServerFIFO) != 0)
        errExit("unlink failed");
}
    return 0;
}
