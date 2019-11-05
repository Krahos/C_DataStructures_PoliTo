#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

void itemDelete(void*);

int main(void) {
	int i, arr [10], *check;
	Queue queue = NULL;

	if ((queue = newQueue(itemDelete)) == NULL) {
		printf("init error\n");
		system("PAUSE");
		return -1;
	}

	printf("empty %d\n", queueEmpty(queue));

	for (i = 0; i < 10; i++) {
		arr[i] = i;
		if (queuePut(queue, &arr[i]) == -1) {
			printf("allocation error\n");
			system("PAUSE");
			return -1;
		}
	}

	printf("count %d\n", queueCount(queue));

	for (i = 0; i < 10; i++) {
		check = queueGet(queue);
		printf("get %d \n", *check);
	}

	queueDestructor(queue);

	system("PAUSE");
	return 0;
}

void itemDelete(void* blabla) {
	
}