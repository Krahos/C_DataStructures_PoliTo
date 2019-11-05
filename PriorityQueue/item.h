#ifndef ITEM_H
#define ITEM_H
typedef struct item *Item;

Item newItem(int value);
int isLower(Item itemA, Item itemB);
void printItem(Item item);

#endif