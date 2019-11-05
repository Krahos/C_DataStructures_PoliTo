#include <stdio.h>
#include <stdlib.h>
#include "PQ.h"
#include "item.h"

#define N 101

int main(void) {
	int i;
	PQ pq = NULL;
	Item items [N];

	if ((pq = newPQ(pq, N, isLower, printItem)) == NULL) {
		printf("newPQ\n");
		return -1;
	}

	printf("first empty check %d\n", isEmptyPQ(pq));

	for (i = 0; i < N; i++) {
		items[i] = newItem(rand() % 50);
		if (items[i] == NULL) {
			printf("Item creation\n");
			return -2;
		}

		if (insertPQ(pq, items[i]) == -1) {
			printf("insert n %d \n ", i);
			return -3;
		}
	}

	printf("second empty check %d\n", isEmptyPQ(pq));

	for (i = 0; i < N; i++) {
		printItem(items[i]);
	}
	printf("\n");

	i = 0;
	while (!isEmptyPQ(pq)) {
		items[i] = getTopPQ(pq);
		i++;
	}

	for (i = 0; i < N; i++) {
		printItem(items[i]);
	}
	printf("\n");

	getchar();
}