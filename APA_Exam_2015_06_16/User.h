#ifndef USER_H
#define USER_H
#include "Skilift.h"

typedef struct user *User;

User newUser (long, int skiliftsN);
void userSetTime (User, int time, int skiliftN);
int userGetTime (User, int skiliftN);
int userGetLastTime (User, int skiliftN);
void userInc (User, int skiliftN);
void userPrintInfo (User, int skiliftN, Skilift*);
void printUser (User);
void deleteUser (User);

#endif