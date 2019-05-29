//
// Created by franc on 25/05/2019.
//

#ifndef SYSTEM_CALL_REQUEST_H
#define SYSTEM_CALL_REQUEST_H
struct request {
    char user[50];
    char service[10];
    pid_t pid;
}
#endif //SYSTEM_CALL_REQUEST_H
