#include <stdio.h>
#include <stdlib.h>
#include "item.h"

struct item {
	int value;
};

Item newItem(int value) {
	Item local;

	local = malloc(sizeof(*local));
	if (local == NULL) {
		return NULL;
	}

	local->value = value;
	return local;
}

int isLower(Item itemA, Item itemB) {
	return itemA->value < itemB->value;
}

void printItem(Item item) {
	if (item != NULL) {
		printf("%d ", item->value);
	}

	else printf("NULL ");
}