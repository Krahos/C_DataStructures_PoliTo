#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Skilift.h"
#include "User.h"
#include "BST.h"

#define MAX_ID 20
#define APPROVED 1
#define NOT_APPROVED 0

void delKey (long*);
int keyEq (long*, long*);
int keyLess (long*, long*);
int search (Skilift*, int, char*);
int authorize (BST, long, char*, int, int, Skilift*);
int readFile (char*, Skilift**);
void printInfo (BST, long, Skilift*, int, char*);

int main (int argc, char *argv []) {
	char skiliftId [MAX_ID];
	int skiliftsN = -1, cardId = -1, time = -1, flag = 0;
	Skilift *skilifts = NULL;
	BST users = NULL;

	if (argc != 2) {
		return -1;
	}

	users = newBST (deleteUser,
		printUser,
		delKey,
		keyEq,
		keyLess);
	if (users == NULL) {
		return -2;
	}

	skiliftsN = readFile (argv [1], &skilifts);
	if (skiliftsN == -1) {
		return -3;
	}

	printf ("Insert skiliftId cardId and time.\n");
	while (fscanf (stdin, "%s %ld %d", skiliftId, &cardId, &time) == 3) {
		flag = authorize (users, cardId, skiliftId, time, skiliftsN, skilifts);
		if (flag == NOT_APPROVED) {
			printf ("Not approved!\n");
		} else if (flag == APPROVED) {
			printf ("Approved!\n");
		} else {
			printf ("Error!\n");
		}
	}

	do {
		printf ("Insert skiliftId and cardId if you wish to print info about a user.\n");
		printInfo (users, cardId, skilifts, skiliftsN, skiliftId);
	} while (fscanf (stdin, "%s %ld", skiliftId, &cardId, &time) == 2);

	getchar ();
	return 0;
}

int authorize (BST users, long cardId, char *skiliftId, int time, int skiliftsN, Skilift *skilifts) {
	int skiliftN = -1, usertime = -1;
	long *key = NULL;
	User lUser = NULL;
	Skilift skilift = NULL;

	lUser = searchBST (users, &cardId);
	if (lUser == NULL) {
		key = malloc (sizeof (*key));
		if (key == NULL) {
			return -1;
		}
		*key = cardId;
		lUser = newUser (cardId, skiliftsN);
		if (lUser == NULL) {
			return -1;
		}

		insertBST (users, lUser, key);
	}

	if ((skiliftN = search (skilifts, skiliftsN, skiliftId)) == -1) {
		return -1;
	}

	usertime = userGetLastTime (lUser, skiliftN);

	if (usertime == -1) {
		userSetTime (lUser, time, skiliftN);
		userInc (lUser, skiliftN);
		return APPROVED;
	}

	if ((usertime + skiliftGetTime (skilifts [skiliftN])) < time) {
		return APPROVED;
	} else {
		userSetTime (lUser, time, skiliftN);
		userInc (lUser, skiliftN);
		return NOT_APPROVED;
	}
}

int readFile (char * fname, Skilift **iskilifts) {
	int i, timeI = -1, count = 0;
	char skiliftId [MAX_ID];
	FILE *fp = NULL;
	Skilift *skilifts = *iskilifts;

	fp = fopen (fname, "r");
	if (fp == NULL) {
		return -1;
	}

	while (fscanf (fp, "%s %d", skiliftId, &timeI) != EOF) {
		++count;
	}

	skilifts = malloc (count * sizeof (*skilifts));
	if (skilifts == NULL) {
		return -1;
	}

	rewind (fp);

	for (i = 0; i < count; ++i) {
		if (fscanf (fp, "%s %d", skiliftId, &timeI) != 2) {
			return -1;
		}

		skilifts [i] = newSkilift (skiliftId, timeI);
		if (skilifts [i] == NULL) {
			return -1;
		}
	}

	fclose (fp);

	*iskilifts = skilifts;
	return count;
}

void printInfo (BST users, long cardId, Skilift *skilifts, int skiliftsN, char *skiliftId) {
	int skiliftIndex = -1;
	User lUser = NULL;

	lUser = searchBST (users, &cardId);
	if (lUser == NULL) {
		printf ("User not found!\n");
		return;
	}

	skiliftIndex = search (skilifts, skiliftsN, skiliftId);
	if (skiliftIndex == -1) {
		printf ("Skilift not found!\n");
		return;
	}

	userPrintInfo (lUser, skiliftIndex, skilifts);
}

int keyEq (long *key1, long *key2) {
	return *key1 == *key2;
}

int keyLess (long *key1, long *key2) {
	return *key1 < *key2;
}

void delKey (long *key) {
	free (key);
}

int search (Skilift* skilifts, int skiliftsN, char *skiliftId) {
	int i;
	for (i = 0; i < skiliftsN; ++i) {
		if (!strcmp (skiliftGetId (skilifts [i]), skiliftId)) {
			return i;
		}
	}
	return -1;
}