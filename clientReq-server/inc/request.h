//
// Created by franc on 25/05/2019.
//

#ifndef SYSTEM_CALL_REQUEST_H
#define SYSTEM_CALL_REQUEST_H
struct Request {
    char userID[100];
    char service[10];
    pid_t pid; //pid_t getpid(void);
};
#endif //SYSTEM_CALL_REQUEST_H
