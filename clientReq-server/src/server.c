#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include "errExit.h"
#include "request.h"
#include "respond.h"

#define MAX_SERVICE 1400000000
unsigned long int printkey =1;
unsigned long int savekey =MAX_SERVICE+1;
unsigned long int recievekey =(MAX_SERVICE*2)+1;
char *path2ServerFIFO ="/tmp/fifo_server";
char *baseClientFIFO = "/tmp/fifo_client.";


// the file descriptor entry for the FIFO
int serverFIFO, serverFIFO_extra;

char * services[]= {"stampa", "salva","invia"};

// the quit function closes the file descriptors for the FIFO,
// removes the FIFO from the file system, and terminates the process

void quit(int sig) {

    // Close the FIFO
    if (serverFIFO != 0 && close(serverFIFO) == -1)
        errExit("close failed");

    if (serverFIFO_extra != 0 && close(serverFIFO_extra) == -1)
        errExit("close failed");

    // Remove the FIFO
    if (unlink(path2ServerFIFO) != 0)
        errExit("unlink failed");

    // terminate the process
    _exit(0);
}
 void strlwr (char s[]) {
    int c = 0;

    while (s[c] != '\0') {
        if (s[c] >= 'A' && s[c] <= 'Z') {
                s[c] = s[c] + 32;
        }
        c++;
    }
}

unsigned long int getKey(struct Request *request){
        unsigned long int key;
        char myService[10];
        strcpy(myService, request->service );
        strlwr(myService);
        if(strcmp(services[0], &myService)==0){
            if(printkey == MAX_SERVICE) {
                printkey = 1;
            }
            return printkey++;
        } //STAMPA

        else if(strcmp(services[1], &myService)==0){
            if(recievekey == MAX_SERVICE*2) {
                printkey = MAX_SERVICE+1;
            }
            return  recievekey++;
        }
        else if(strcmp(services[2], &myService)==0){
            if(savekey == MAX_SERVICE*3) {
                printkey = MAX_SERVICE*2 + 1;
            }
            return savekey++;
        }
        else
            return 0;// TODO RETURN 0!! IN CLIENTreQ


        return key;
}

void sendResponse(struct Request *request) {

    // make the path of client's FIFO
    char path2ClientFIFO [100];
    sprintf(path2ClientFIFO, "%s%d", baseClientFIFO, request->pid);

    printf("<Server> opening FIFO %s...\n", path2ClientFIFO);
    // Open the client's FIFO in write-only mode
    int clientFIFO = open(path2ClientFIFO, O_WRONLY);
    if (clientFIFO == -1) {
        errExit("<Server> open failed");

    }

    // Prepare the response for the client
    struct Response response;
    response.key = getKey(&request);
    //TODO key in shared memory request->user, response.key , time_t current

    printf("<Server> sending a response\n");
    // Write the Response into the opened FIFO
    if (write(clientFIFO, &response, sizeof(struct Response))!= sizeof(struct Response)) {
        errExit("<Server> write failed");
    }

    // Close the FIFO
    if (close(clientFIFO) != 0)
        printf("<Server> close failed");
}


int main (int argc, char *argv[]) {
    //TODO fork for keyManager
    printf("Server program");

    sigset_t mySet;
    // initialize mySet to contain all signals
    sigfillset(&mySet);
    // remove SIGTERM from mySet
    sigdelset(&mySet, SIGTERM);
    // blocking all signals but SIGINT
    sigprocmask(SIG_SETMASK, &mySet, NULL);

    // set the function sigHandler as handler for the signal SIGINT
    if (signal(SIGTERM, quit) == SIG_ERR)
        errExit("change signal handler failed");

    printf("<Server> Making FIFO...\n");
    // make a FIFO with the following permissions:
    // user:  read, write
    // group: write
    // other: no permission
    if (mkfifo(path2ServerFIFO, S_IRUSR | S_IWUSR | S_IWGRP) == -1)
        errExit("mkfifo failed");

    printf("<Server> FIFO %s created!\n", path2ServerFIFO);

    // set a signal handler for SIGALRM and SIGINT signals
    if (signal(SIGALRM, quit) == SIG_ERR ||
        signal(SIGINT, quit) == SIG_ERR)
    { errExit("change signal handlers failed"); }

    // setting a 30 seconds alarm
    alarm(30);

    // Wait for client in read-only mode. The open blocks the calling process
    // until another process opens the same FIFO in write-only mode
    printf("<Server> waiting for a client...\n");
    serverFIFO = open(path2ServerFIFO, O_RDONLY);
    if (serverFIFO == -1)
        errExit("open read-only failed");

    // Open an extra descriptor, so that the server does not see end-of-file
    // even if all clients closed the write end of the FIFO
    serverFIFO_extra = open(path2ServerFIFO, O_WRONLY);
    if (serverFIFO_extra == -1)
        errExit("open write-only failed");

    struct Request request;
    int bR = -1;
    do {
        printf("<Server> waiting for a Request...\n");
        // Read a request from the FIFO
        bR = read(serverFIFO, &request, sizeof(struct Request));


        // Check the number of bytes read from the FIFO
        if (bR == -1) {
            printf("<Server> it looks like the FIFO is broken\n");
        }
        else if (bR != sizeof(struct Request) || bR == 0)
            printf("<Server> it looks like I did not receive a valid request\n");
        else
            sendResponse(&request);


    } while (bR != -1);

    // the FIFO is broken, run quit() to remove the FIFO and
    // terminate the process.
    quit(0);

    return 0;
}
