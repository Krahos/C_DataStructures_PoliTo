#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

int main(void) {
	int arr[10], i, *item;
	Stack stack = newStack(NULL, NULL);

	for (i = 0; i < 10; i++) {
		arr[i] = i;
	}

	if (stackEmpty(stack)) {
		printf("empty\n");
	}

	for (i = 0; i < 10; i++) {
		if (stackPush(stack, &arr[i])) {
			printf("push err\n");
			return -1;
		}
	}

	printf("count %d\n", stackCount(stack));

	if ((item = stackTopView(stack)) != NULL) {
		printf("top %d\n", *item);
	}

	while ((item = stackPop(stack)) != NULL) {
		printf("pop %d\n", *item);
	}

	stackDestructor(stack);

	return 0;
}