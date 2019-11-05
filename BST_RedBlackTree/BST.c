#include <stdlib.h>
#include "BST.h"

#define RED 1
#define BLACK 0

typedef struct node *link;
struct node {
	void *item;
	void *key;
	int count;
	int colour;

	link right;
	link left;
};

struct BST {
	link root;
	link nil;
	int count;

	void(*delItem) (void*);
	void(*visitItem) (void*);
	void(*delKey) (void*);
	int(*keyEq) (void*, void*);
	int (*keyLess) (void*, void*);
};

link newNode(void *item, void *key, link left, link right, int colour) {
	link this = NULL;

	if ((this = malloc(sizeof(*this))) == NULL) {
		return NULL;
	}

	this->item = item;
	this->key = key;
	this->left = left;
	this->right = right;
	this->colour = colour;

	return this;
}

void destroyNode(BST bst, link this, int itemflag, int keyflag) {
	if (itemflag) {
		bst->delItem(this->item);
	}

	if (keyflag) {
		bst->delKey(this->key);
	}

	free(this);
}

BST newBST(
	void(*delItem) (void*),
	void(*visitItem) (void*),
	void(*delKey) (void*),
	int(*keyEq) (void*, void*),
	int (*keyLess) (void*, void*)
	) {
	BST this = NULL;

	if ((this = malloc(sizeof(*this))) == NULL) {
		return NULL;
	}

	this->root = (this->nil = newNode (NULL, NULL, NULL, NULL, BLACK));
	this->count = 0;
	this->delItem = delItem;
	this->visitItem = visitItem;
	this->delKey = delKey;
	this->keyEq = keyEq;
	this->keyLess = keyLess;

	return this;
}

int emptyBST(BST this) {
	return this->count == 0;
}

int countBST(BST this) {
	return this->count;
}

link rotR(link this) {
	link x = this->left;
	this->left = x->right;
	x->right = this;
	return x;
}

link rotL(link this) {
	link x = this->right;
	this->right = x->left;
	x->left = this;
	return x; 
}

link insertR(BST bst, link this, void *item, void *key, int sw) {
	link nil = bst->nil;
	link local = NULL;
		if (this == nil) {
			if ((local = newNode (item, key, nil, nil, RED)) == NULL) {
				exit(-1);
			} else {
				return local;
			}
		}

		if ((this->left->colour == RED) && (this->right->colour == RED)) {
			this->colour = RED;
			this->left->colour = BLACK;
			this->right->colour = BLACK;
		}

		if (bst->keyLess (key, this->key)) {
			if ((this->left = insertR (bst, this->left, item, key, 0)) == NULL) {
				exit(-1);
			}

			if ((this->colour == RED) && (this->left->colour == RED) && sw) {
				this = rotR (this);
			}

			if ((this->left->colour == RED) && (this->left->left->colour == RED)) {
				this = rotR (this);
				this->colour = BLACK;
				this->right->colour = RED;
			}
		} else {
			if ((this->right = insertR (bst, this->right, item, key, 1)) == NULL) {
				exit (-1);
			}

			if ((this->colour == RED) && (this->right->colour == RED) && !sw) {
				this = rotL (this);
			}

			if ((this->right->colour == RED) && (this->right->right->colour == RED)) {
				this = rotL (this);
				this->colour = BLACK;
				this->left->colour = RED;
			}
		}

		return this;
}

int insertBST(BST this, void *item, void *key) {
	this->root = insertR (this, this->root, item, key, 0);

	++(this->count);
	this->root->colour = BLACK;
	return 0;
}

int balanceCheckR (link nil, link this) {
	int left = 0, right = 0;

	if (this == nil) {
		return 0;
	}

	left = balanceCheckR (nil, this->left);
	right = balanceCheckR (nil, this->right);

	if (left > right) {
		return ++left;
	} else {
		return ++right;
	}
}

int  balanceCheckBST (BST this) {
	int left = 0, right = 0;

	left = balanceCheckR (this->nil, this->root->left);
	right = balanceCheckR (this->nil, this->root->right);
	return  left - right;
}

void *searchR(BST bst, link this, void *key) {
	if (this == bst->nil) {
		return NULL;
	}

	if (bst->keyEq(this->key, key)) {
		return this->item;
	}

	if (bst->keyLess(this->key, key)) {
		return searchR(bst, this->left, key);
	}
	else return searchR(bst, this->right, key);
}

void *searchBST(BST this, void *key) {
	return searchR(this, this->root, key);
}

void preorderR(BST bst, link this) {
	if (this == bst->nil) {
		return;
	}

	bst->visitItem(this->item);
	preorderR(bst, this->left);
	preorderR(bst, this->right);
}

void preorderBST(BST this) {
	preorderR(this, this->root);
}

void inorderR(BST bst, link this) {
	if (this == bst->nil) {
		return;
	}

	inorderR(bst, this->left);
	bst->visitItem(this->item);
	inorderR(bst, this->right);
}

void inorderBST(BST this) {
	inorderR(this, this->root);
}

void postorderR(BST bst, link this) {
	if (this == bst->nil) {
		return;
	}

	postorderR(bst, this->left);
	postorderR(bst, this->right);
	bst->visitItem(this->item);
}

void postorderBST(BST this) {
	postorderR(this, this->root);
}

void toArrayR(void **array, link this, int count) {
	if (this == NULL) {
		return;
	}

	toArrayR(array, this->left, count);
	array[count++] = this->item;
	toArrayR(array, this->right, count);
}

void **toArrayBST(BST this) {
	void **array;

	array = malloc(this->count * sizeof(*array));
	if (array == NULL) {
		return NULL;
	}

	toArrayR(array, this->root, 0);

	return array;
}

void destroyR(BST bst, link this, int itemflag, int keyflag) {
	if (this == NULL) {
		return;
	}

	destroyR(bst, this->left, itemflag, keyflag);
	destroyR(bst, this->right, itemflag, keyflag);

	destroyNode(bst, this, itemflag, keyflag);
}

void destroyBST(BST this, int itemflag, int keyflag) {
	destroyR(this, this->root, itemflag, keyflag);
	free(this);
}
