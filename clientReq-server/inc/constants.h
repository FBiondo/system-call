//
// Created by franc on 29/05/2019.
//

#ifndef SYSTEM_CALL_CONSTANTS_H
#define SYSTEM_CALL_CONSTANTS_H
#include <stdlib.h>

#include "shared_memory.h"

/*

 */
#define MAX_CLIENTREQ 300


/*
 * define constant values for the keys of the shared memory segments and the semaphore
 */
#define SEMAPHOREDBKEY 2

#define SHAREDMEMDBKEY 1
#define SHAREDMEMLKEY 2

/*
 * defining constant values which will be used by the various programs
 */
char * path2ServerFIFO ="tmp/fifo_server";
char * baseClientFIFO = "tmp/fifo_client.";

char * services[]= {"stampa", "salva","invia"};
int numService = sizeof(services)/sizeof(char *);

#endif //KEYS_H
#endif //SYSTEM_CALL_CONSTANTS_H
