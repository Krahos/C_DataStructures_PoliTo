#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

#define N 10

void itemVisit(int*);
void deleteItem(int*);

int main(void) {
	int array[N], array1[N];
	int *item;
	int i;
	int check = 1;
	List list = NULL;

	if ((list = newList(itemVisit, deleteItem)) == NULL) {
		printf("allocation error\n");
		return 1;
	}

	for (i = 0; i < N; i++) {
		array[i] = i;
		check = listInsert(list, &array[i]);
		if (check) {
			printf("Insertion failed.\n");
			return 2;
		}
	}


	printf("Next:\n");
	for (i = 0; i < N; i++) {
		item = listNext(list);
		printf("%d\n", *item);
	}

	listResetSearch(list);
	printf("Next:\n");
	for (i = 0; i < N; i++) {
		item = listNext(list);
		printf("%d\n", *item);
	}

	item = listNext(list);
	if (item == NULL) {
		printf("Failure ok\n");;
	}

	printf("Visit:\n");
	listVisit(list);

	printf("Get:\n");
	for (i = 0; i < N; i++) {
		item = listGet(list);
		printf("%d\n", *item);
	}

	listCount(list);

	deleteList(list, ITEM_D);

	getchar();
	return 0;
}

void itemVisit(int *item) {
	printf("item %d\n", *item);
}

void deleteItem(int *item) {
	printf("delete executed.\n");
}