#include <stdio.h>
#include <stdlib.h>
#include "BST.h"

#define N 100000

void visitItem(int*);
int keyEq (int*, int*);
int keyLess (int*, int*);
void delItem (void*);
void delKey (void*);

int main(void) {
	int i, arrA [N];
	BST bst;

	if ((bst = newBST(delItem, visitItem, delKey, keyEq, keyLess)) == NULL) {
		return  -1;
	}

	for (i = 0; i < N; i++) {
		arrA[i] = i;
		insertBST (bst, &arrA [i], &arrA [i]);
	}

	printf("preorder:\n");
	preorderBST(bst);
	putchar('\n');
	printf("inorder:\n");
	inorderBST(bst);
	putchar('\n');
	printf("postorder:\n");
	postorderBST(bst);
	putchar('\n');

	printf ("balance %d", balanceCheckBST (bst));

	getchar();
	return 0;
}

void visitItem(int *item) {
	printf("%d ", *item);
}

int keyEq(int *keyA, int *keyB) {
	return *keyA == *keyB;
}

int keyLess (int *keyA, int *keyB) {
	return *keyA < *keyB;
}

void delItem (void* item) {

}

void delKey (void* key) {

}
