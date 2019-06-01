#ifndef SYSTEM_CALL_CONSTANTS_H
#define SYSTEM_CALL_CONSTANTS_H

#define MAX_CLIENT 1000
#define SEMAPHORE_KEY 11
#define SHARED_MEM_KEY 21
#define SHARED_NUM_KEY 22
#define MAX_LEN 9

char * services[]= {"stampa", "salva","invia"};
int numService = sizeof(services)/sizeof(char *);

#endif //SYSTEM_CALL_CONSTANTS_H