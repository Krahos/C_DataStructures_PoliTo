#include <stdlib.h>
#include "Queue.h"

#define ITEM_D 1
#define ITEM_ND 0

typedef struct node *link;

link newNode(void*, link);
void nodeDestructor(Queue, link, int);

struct node {
	void *item;
	link next;
};

struct queue {
	link head, tail;
	int count;

	void(*itemDelete) (void*);
};

int queuePut(Queue this, void *item) {

	if (this->head == NULL) {
		if ((this->tail = newNode(item, NULL)) == NULL) {
			return -1;
		}

		(this->count)++;
		this->head = this->tail;
		return 0;
	}

	if ((this->tail->next = newNode(item, NULL)) == NULL) {
		return -1;
	}

	(this->count)++;
	this->tail = this->tail->next;

	return 0;
}

void *queueGet(Queue this) {
	void *item = this->head->item;
	link local = this->head->next;

	nodeDestructor(this, this->head, ITEM_D);
	(this->count)++;
	this->head = local;

	return item;
}

int queueCount(Queue this) {
	return this->count;
}

int queueEmpty(Queue this) {
	return this->count == 0;
}

link newNode(void* item, link next) {
	link local = NULL;
	
	local = malloc(sizeof(*local));
	if (local == NULL) {
		return NULL;
	}

	local->item = item;
	local->next = next;
	return local;
}

Queue newQueue(
	void(*itemDelete)(void*)) {

	Queue local = malloc(sizeof(*local));

	local->tail = NULL;
	local->head = local->tail;
	local->count = 0;

	local->itemDelete = itemDelete;

	return local;
}

void nodeDestructor(Queue queue, link this, int itemFlag) {
	if (itemFlag) {
		queue->itemDelete(this->item);
	}

	free(this);
}

void queueDestructor(Queue this) {
	link local = this->head;

	while (local != NULL) {
		nodeDestructor(this, local, ITEM_D);
	}
}