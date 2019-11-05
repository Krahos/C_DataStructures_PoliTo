#ifndef SKILIFT_H
#define SKILIFT_h

typedef struct skilift *Skilift;

Skilift newSkilift (char*, int);
int skiliftGetTime (Skilift);
char *skiliftGetId (Skilift);

#endif