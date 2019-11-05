#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define ITEM_D 1
#define ITEM_ND 0

typedef struct List *List;

List  newList(
	void(*itemVisit)(void*),
	void(*itemDelete)(void*)
	);
int   listInsert(List, void *item);
void  *listGet(List this);
void  *listNext(List);
int   listEmpty(List);
int   listCount(List);
void  listResetSearch(List);
void  listVisit(List);
void  deleteList(List, int itemDelete);

#endif