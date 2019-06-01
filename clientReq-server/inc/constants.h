//
// Created by franc on 29/05/2019.
//

#ifndef SYSTEM_CALL_CONSTANTS_H
#define SYSTEM_CALL_CONSTANTS_H
#include <stdlib.h>

#include "shared_memory.h"

#ifndef SYSCALL_CONSTANTS_H
#define SYSCALL_CONSTANTS_H

#define SEMAPHORE_KEY 11
#define SHARED_MEM_KEY 21
#define SHARED_NUM_KEY 22
#define TTL 300
#define MAX_CLIENT 1000

#define SEM_SHM 0
#define SEM_NUM 1

/*
 * defining constant values which will be used by the various programs
 */
char *pathFifoServer = "tmp/fifoServer";
char *baseFifoClient = "tmp/fifoClient.";

char * services[]= {"stampa", "salva","invia"};


#endif //SYSTEM_CALL_CONSTANTS_H
