#include <stdlib.h>
#include <stdio.h>
#include "message.h"
#include "errExit.h"
#include <sys/msg.h>
#include <string.h>
#include <error.h>
#include <fcntl.h>

extern char* services[];
extern int numService;

int main (int argc, char *argv[]) {
    printf("Hi, I'm ClientExec program!\n");
    if (argc < 3) {
        printf("Usage: %s user_identifier server_key ...\n", *argv);
        return 1;
    }
    unsigned long int serverKey = getKey(); //TODO
    if (serverKey == 0) {
        printf("Invalid server key.\nServer generates only hexadecimal keys greater then zero.\n");
        exit(1);
    }

    //get the id of the semaphore
    int semid = semget(SEMAPHORE_KEY, 1, S_IRUSR | S_IWUSR);
    if (semid == -1)
        errExit("semget failed");

    //get the id of the shared memory
    int shmid = shmget(SEMAPHORE_KEY, sizeof(struct Entry)*MAX_CLIENT, S_IRUSR | S_IWUSR);
    if (shmid == -1)
        errExit("shmget failed");

    //attach the shared memory segment
    struct Entry shm_entry * = (struct Entry shm_entry*) shmat(shmid, NULL, 0);
    if (shm_entry == (struct Entry *) NULL)
        errExit("shmat failed");

    //get the id of the shared memory which contains the number
    int shmNum = shmget(SHARED_NUM_KEY, sizeof(int), S_IRUSR | S_IWUSR);
    if (shmNum == -1)
        errExit("shmget failed");

    //attach the shared memory segment which contains the length
    int *num= (int *) shmat(shmNum, NULL, 0);
    if (num == (int *) NULL)
        errExit("shmat failed");

    //before searching into the server, tries to get the semaphore to access
    semOp(semid, 0, -1);
    //int entry=search();//TODO search for key
    semOp(semid, 0, 1);

    //switch over entry to know if we have found an entry or we have errors
    switch (entry) {
        case -1: {
            printf("code [%d]: user_identifier and server_key don't appear in the shm_entry.\n", entry);
            printf("\t1. You might have asked for an unsupported service.\n");
            printf("\t2. Your key has already been used.\n");
            printf("\t3. Your key has expired.\n");
            printf("\t4. You are trying to access before requesting a key.\n");
            exit(1);
        }
        case -2: {
            printf("code [%d]: invalid key for user_identifier.\n", entry);
            exit(1);
        }
        case -3: {
            printf("code [%d]: invalid user_identifier for key.\n", entry);
            exit(1);
        }
        case -4: {
            printf("code [%d]: there is no combination (user_identifier, key).\n", entry);
            exit(1);
        }
        default: {
            printf("\nSoon starting service: %s ... \n\n", service);
            //create the argument vector for the exec call
           //TODO create argVector
            }
        }
    }

    return 0;
}
