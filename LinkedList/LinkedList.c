#include <stdlib.h>
#include "LinkedList.h"

typedef struct node *link;

struct node {
	void *item;
	link next;
};

struct List {
	link head;
	link tail;
	link probe;
	int count;

	void(*itemVisit)(void*);
	void(*deleteItem)(void*);
};

link newNode(void*, link);
void deleteNode(List, link, int);

int listInsert(List this, void *item) {

	if (this->tail == NULL) {
		this->tail = newNode(item, NULL);
		if (this->tail == NULL) {
			return 1;
		}
		this->head = this->tail;
		this->probe = this->head;
		this->count++;
	}
	else {
		this->tail->next = newNode(item, NULL);
		if (this->tail->next == NULL) {
			return 1;
		}

		this->tail = this->tail->next;

		this->count++;
	}

	return 0;
}

void *listGet(List this) {
	link local = this->head;
	void *lItem = local->item;

	this->head = this->head->next;
	deleteNode(this, local, ITEM_ND);
	this->count--;
	return lItem;
}

void *listNext(List this) {
	void *local = NULL;

	if (this->probe == NULL) {
		return NULL;
	}

	local = this->probe->item;
	this->probe = this->probe->next;
	return local;
}

int listEmpty(List this) {
	return this->count == 0;
}

int listCount(List this) {
	return this->count;
}

void listResetSearch(List this) {
	this->probe = this->head;
}

void listVisit(List this) {
	link local = this->head;

	while (local != NULL) {
		this->itemVisit(local->item);
		local = local->next;
	}
}

link newNode(void *item, link next) {
	link this = malloc(sizeof (*this));
	if (this == NULL) {
		return NULL;
	}

	this->item = item;

	this->next = next;

	return this;
}

List newList(
	void(*itemVisit)(void*),
	void(*deleteItem)(void*)
	) {

	List this = malloc(sizeof(*this));
	if (this == NULL) {
		return NULL;
	}

	this->head = NULL;
	this->tail = this->head;
	this->probe = this->head;
	this->count = 0;
	this->itemVisit = itemVisit;
	this->deleteItem = deleteItem;

	return this;
}

void deleteNode(List list, link this, int itemFlag) {
	if (itemFlag) {
		list->deleteItem(this->item);
	}

	free (this);
}

void deleteList(List this, int itemFlag) {
	link local = NULL;
	while (this->head != NULL) {
		local = this->head->next;
		deleteNode(this, this->head, itemFlag);
		this->head = local;
	}
}