#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue *Queue;

Queue newQueue(
	void(*itemDelete)(void*));
int queuePut(Queue, void* item);
void *queueGet(Queue);
int queueCount(Queue);
int queueEmpty(Queue);
void queueDestructor(Queue);

#endif