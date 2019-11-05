#include <stdio.h>
#include <stdlib.h>
#include "PQ.h"

void fixUp(PQ, void **, int);
void fixDown(PQ, void **, int, int);
void exch(void **, int, int);

struct pq {
	int(*isLower) (void*, void*);
	void(*printItem) (void *);

	void **heap;
	int n;
	int max;
};

PQ newPQ(PQ this,
	int max,
	int(*isLower)(void*, void*),
	void(*printItem)(void*)
	) {

	this = malloc(sizeof(*this));
	if (this == NULL) {
		return NULL;
	}

	this->max = max;
	this->isLower = isLower;
	this->printItem = printItem;
	this->heap = malloc(max * sizeof(*(this->heap)));
	this->n = 0;

	return this;
}

int isEmptyPQ(PQ this) {
	return this->n == 0;
}

int insertPQ(PQ this, void *item) {
	this->n++;
	if (this->n > this->max) {
		return -1;
	}

	this->heap[this->n] = item;
	fixUp(this, this->heap, this->n);
	return 0;
}

void *getTopPQ(PQ this) {
	exch(this->heap, 1, this->n);
	fixDown(this, this->heap, 1, (this->n) - 1);
	return this->heap[this->n--];
}

void *viewTopPQ(PQ this) {
	return this->heap[1];
}

void fixUp(PQ this, void **arr, int currElement) {
	while (currElement > 1 && (this->isLower(arr[currElement / 2], arr[currElement]))) {
		exch(arr, currElement, currElement / 2);
		currElement = currElement / 2;
	}
}

void fixDown(PQ this, void **arr, int currElement, int max) {
	int j;
	while ((2 * currElement) <= max) {
		j = 2 * currElement;
		if (j < max && this->isLower(arr[j], arr[j + 1])){
			j++;
		}

		if (!this->isLower(arr[currElement], arr[j])) {
			break;
		}

		exch(arr, currElement, j);
		currElement = j;
	}
}

void exch(void ** array, int a, int b) {
	void *tmp = array [a];

	array [a] = array [b];
	array [b] = tmp;
}