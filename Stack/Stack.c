#include <stdlib.h>
#include "Stack.h"

typedef struct node *link;

link newNode(void*, link);
void nodeDestructor(Stack, link);

struct node {
	void *item;
	link next;
};

struct stack {
	link top;
	int count;
	void(*itemDelete) (void*);
};

int stackPush(Stack this, void* item) {
	link local = NULL;

	if ((local = newNode(item, this->top)) == NULL) {
		return -1;
	}

	this->top = local;
	(this->count)++;

	return 0;
}

void* stackPop(Stack this) {
	void *tmpItem = NULL;
	link tmpLink;

	if ((this->top) == NULL) {
		return NULL;
	}

	tmpItem = this->top->item;
	this->top->item = NULL;
	tmpLink = this->top;
	this->top = this->top->next;
	nodeDestructor(this, tmpLink);

	return tmpItem;
}

void* stackTopView(Stack this) {
	if ((this->top) == NULL) {
		return NULL;
	}

	return this->top->item;
}

int stackCount(Stack this) {
	return this->count;
}

int stackEmpty(Stack this) {
	if ((this->count) == 0) {
		return 1;
	}
	else return 0;
}

link newNode(void* item, link next) {
	link this = NULL;
		
	this = malloc(sizeof(*this));
	if (this == NULL) {
		return NULL;
	}

	(this->item) = item;
	(this->next) = next;

	return this;
}

Stack newStack(
	void (*itemvisit)(void*),
	void (*itemDelete)(void*)) {

	Stack this = malloc(sizeof(*this));
	if (this == NULL) {
		return NULL;
	}

	this->top = NULL;
	this->count = 0;
	this->itemDelete = itemDelete;
	this->itemVisit = itemvisit;

	return this;
}

void nodeDestructor(Stack stack, link this) {
	if ((this->item) != NULL) {
		stack->itemDelete(this->item);
	}

	free(this);
	return;
}

void stackDestructor(Stack this) {
	link tmpLink = this->top;

	while (tmpLink != NULL) {
		tmpLink = this->top->next;
		nodeDestructor(this, this->top);
	}

	free(this);
	return;
}