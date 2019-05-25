#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sem.h>
#include "request_response.h"
#include "errExit.h"

char * FIFOSERVER ="/tmp/FIFOSERVER";
char * FIFOSCLIENT ="/tmp/FIFOCLIENT";

struct myRequest {
    char[] user;
    char[] service;
}
void helloWorld(){
    printf("Hi, I'm ClientReq program!\n");
    printf("Ecco i servizi di sistema:\n -stampa\n -salva\n -invia\n");
}
int main (int argc, char *argv[]) {

    struct myRequest request;

    helloWorld();

    printf(" Per favore inserisci il tuo nome:\n");
    scanf("%s", request.user);
    printf("Per favore inserisci il nome del servizio che vuoi utilizzare:\n");
    scanf("%s",request.service);
    printf("codice identificativo: %s \n", );



    // SEMAFORO 1
    int semid= semget(IPC_PRIVATE, 1, S_IWUSR | S_IRUSR);
    if(semid == -1)
        errExit("semget failed");
    //if possible enter and decrease
    semOp(semid, 0, -1);

    printf("<Client> making FIFO...\n");
    // make a FIFO with the following permissions:
    // user:  read, write

    if (mkfifo(FIFOCLIENT, S_IRUSR | S_IWUSR) == -1)
        errExit("mkfifo failed");



    // Step-2: The client opens the server's FIFO to send a Request

    int sd = open(FIFOSERVER, O_WRONLY);
    if (sd == -1)
        errExit("open failed");

    // Step-3: The client sends a Request through the server's FIFO

    if (write(FIFOSERVER, &request,
    sizeof(struct myRequest)) != sizeof(struct myRequest))
        errExit("write failed");

    // Step-4: The client opens its FIFO to get a Response
    int cd = open(FIFOCLIENT, O_RDONLY);
    if (cd == -1)
        errExit("open failed");

    // Step-5: The client reads a Response from the server
    struct myResponse response;
    if (read(FIFOCLIENT, &response,
             sizeof(struct myResponse)) != sizeof(struct myResponse))
        errExit("read failed");

    // Step-6: The client prints the result on terminal
    printf("<Client> The server sent the result: %d\n", response.result); //CHIAVE

    // Step-7: The client closes its FIFO
    if (close(FIFOSERVER) != 0 || close(FIFOCLIENT) != 0)
        errExit("close failed");

    // Step-8: The client removes its FIFO from the file system
    if (unlink(FIFOCLIENT) != 0)
        errExit("unlink failed");

    semOp(semid, 0, 1);


    printf("chiave rilasciata del server: %s \n", key);



    return 0;
}
