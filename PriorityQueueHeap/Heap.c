#include <stdlib.h>
#include "Priority queue.h"

#define ITEM_D 1
#define ITEM_ND 2

typedef struct element *Element;

struct element{
	void *item;
	void *priority;
};

struct priorityQueue {
	Element *elements;
	int count, max;
	
	int(*less)(void*, void*);
	void(*itemDelete)(void*);
	void(*priorityDelete)(void*);
};

Element newElement(void*, void*);
void    fixUp(int(*)(void*, void*), Element*, int);
void    fixDown(int(*)(void*, void*), Element *, int, int);
void    exch(PriorityQueue, int, int);
void    elementDestructor(PriorityQueue, Element, int);

int pqInsert(PriorityQueue this, void *item, void *priority) {
	if (
		(this->elements[++(this->count)] =
		newElement(item, priority))
		== NULL) {
		return -1;
	}

	fixUp(this->less, this->count);
	return 0;
}

void *pqDelMax(PriorityQueue this) {
	void *local = NULL;
	exch(this, 1, this->count);
	fixDown(this, 1, (this->count) - 1);
	local = this->elements[this->count];
	elementDestructor(this, this->elements[(this->count)--], ITEM_ND);
	return local;
}

int pqEmpty(PriorityQueue this) {
	return this->count == 0;
}

int pqCount(PriorityQueue this) {
	return this->count;
}

void fixUp(int (*less)(void*, void*),
	Element *elements,
	int position) {

	while (
		position > 1 &&
		less(elements[position / 2], elements[position / 2])) {
		exch(elements, position / 2, position);
	}
}

void exch(Element *elements, int posA, int posB) {
	Element local;

	local = elements[posA];
	elements[posA] = elements[posB];
	elements[posB] = local;
}

Element newElement(void *item, void*priority) {
	Element this;

	this = malloc(sizeof(*this));
	if (this == NULL) {
		return NULL;
	}

	this->item = item;
	this->priority = priority;

	return this;
}

PriorityQueue newPQueue(
	int max,
	int(*less)(void*, void*),
	void(*itemDelete)(void*),
	void(*priorityDelete)(void*)) {
	PriorityQueue this = NULL;

	this = malloc(sizeof(*this));
	if (this == NULL) {
		return NULL;
	}

	(this->elements) = 
		malloc((++max) * sizeof(*(this->elements)));
	if (this->elements == NULL) {
		return NULL;
	}

	this->count = 0;
	this->max = max;
	this->less = less;
	this->itemDelete = itemDelete;
	this->priorityDelete = priorityDelete;

	return this;
}

void elementDestructor(PriorityQueue pq, Element this, int itemFlag) {
	if (itemFlag){ 
		pq->itemDelete(this->item);
	}

	pq->itemDelete(this->priority);
	free(this);
}

void pqDestructor(PriorityQueue pq) {
	int i = pq->count;

	while (i) {
		elementDestructor(pq, pq->elements[i], ITEM_D);
		i--;
	}

	free(pq);
}