#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

typedef struct pq *PQ;

PQ newPQ(PQ, int max, int(*isLower)(void*, void*), void(*printItem)(void*));
int isEmptyPQ(PQ this);
int insertPQ(PQ this, void *item);
void *viewTopPQ(PQ this);
void *getTopPQ(PQ this);

#endif