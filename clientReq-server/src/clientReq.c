#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sem.h>

#include "request.h
#include "response.h"
#include "errExit.h"
#include "constants.h"

extern char * path2ServerFIFO ;
extern char * baseClientFIFO;
extern char* services[];


void helloWorld(){
    printf("Hi, I'm ClientReq program!\n");
    printf("Ecco i servizi di sistema:\n -stampa\n -salva\n -invia\n");
}
int main (int argc, char *argv[]) {

    struct request request;

    helloWorld();

    printf(" Per favore inserisci il tuo nome:\n");
    scanf("%s", request.user);
    printf("Per favore inserisci il nome del servizio che vuoi utilizzare:\n");
    scanf("%s",request.service);
    printf("codice identificativo: %s \n", );


    //create the client fifo using the base clientFIFO path and adding his pid
    char path2clientFIFO[50];
    pid_t myPid = getpid();
    request.pid = myPid;
    sprintf(path2clientFIFO, "%s%d", path2clientFIFO, myPid);

    printf("<Client> making FIFO...\n");
    // make a FIFO with the following permissions:
    // user:  read, write

    if (mkfifo(path2clientFIFO, S_IRUSR | S_IWUSR) == -1)
        errExit("mkfifo failed");



    // Step-2: The client opens the server's FIFO to send a Request

    int sd = open(serverFIFO, O_WRONLY);
    if (sd == -1)
        errExit("open failed");

    // Step-3: The client sends a Request through the server's FIFO

    if (write(sd, &request,sizeof(struct request))
            != sizeof(struct request))
        errExit("write failed");

    // Step-4: The client opens its FIFO to get a Response
    int cd = open(path2clientFIFO, O_RDONLY);
    if (cd == -1)
        errExit("open failed");

    // Step-5: The client reads a Response from the server
    struct response response;

    int bR = read(cd, &response, sizeof(struct response_t));
    if(bR == -1)
        errExit("read failed");
    else if(bR != sizeof(struct response_t))
        printf("Bad response\n");
    else { // Step-6: The client prints the result on terminal
        printf("\n");
        printf("Key:\t%ls\n", response.key);
        printf("UserId:\t%s\n", response.user);
    }


    // Step-7: The client closes its FIFO
    if (close(cd) == -1)
        errExit("close failed");

    // Step-8: The client removes its FIFO from the file system
    if (unlink(path2clientFIFO) != 0)
        errExit("unlink failed");

    return 0;
}
