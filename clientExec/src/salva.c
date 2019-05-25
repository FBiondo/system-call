#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "errExit.h"
#define SIZE_ARG(x) sizeof(char)*strlen(x)
int main (int argc, char *argv[]) {
    printf("Hi, I'm Salva program!\n");
    if(argc<2) {
        printf("File su cui si va a salvare: %s \n", argv[i]);
        return 1;
    }
    // only write only one user
    int fd=open(argv[1], O_WRONLY | O_CREAT| O_APPEND, S_IRWXU);
    if(fd==-1)
        errExit("Open Failed");
    char man='\n';
    for(int i=2; i<argc; i++){
        int bW= write(fd,argv[i], SIZE_ARG(argv[i]));
        if(bW != SIZE_ARG(argv[i]))
            errExit("Write failed");
        else
            if(write(fd,&man, sizeof(man)!= sizeof(man)))
                errExit("write failed");
    }
    if(close(fd)==-1)
        errExit("close failed");
    return 0;
}
