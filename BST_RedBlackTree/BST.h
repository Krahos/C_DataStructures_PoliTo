#ifndef BINARYSEARCHTREE
#define BINARYSEARCHTREE

#define DELITEM 1
#define NDELITEM 0
#define DELKEY 1
#define NDELKEY 0

typedef struct BST *BST;


BST  newBST(
	 void(*delItem) (void*),
	 void(*visitItem) (void*),
	 void(*delKey) (void*),
	 int(*keyEq) (void*, void*),
	 int (*keyLess) (void *, void*)
	 );
int  emptyBST(BST);
int  countBST(BST);
int  insertBST(BST, void *item, void *key);
int  balanceCheckBST (BST);
void *searchBST(BST, void *key);
void **toArrayBST(BST this);
void preorderBST(BST);
void inorderBST(BST);
void postorderBST(BST);
void destroyBST(BST, int itemflag, int keyflag);

#endif