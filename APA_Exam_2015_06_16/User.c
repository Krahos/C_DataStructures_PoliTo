#include <stdio.h>
#include <stdlib.h>
#include "User.h"

struct user {
	long cardId;
	int *skiliftCount;
	int *skiliftLastTime;
};

User newUser (long cardId, int skiliftsN) {
	int i;
	User lUser = malloc (sizeof (*lUser));
	if (lUser == NULL) {
		return NULL;
	}

	lUser->cardId = cardId;
	lUser->skiliftCount = malloc (skiliftsN * sizeof (*(lUser->skiliftCount)));
	if (lUser->skiliftCount == NULL) {
		return NULL;
	}

	lUser->skiliftLastTime = malloc (skiliftsN * sizeof (*(lUser->skiliftCount)));
	if (lUser->skiliftLastTime == NULL) {
		return NULL;
	}

	for (i = 0; i < skiliftsN; ++i) {
		lUser->skiliftCount [i] = 0;
		lUser->skiliftLastTime [i] = -1;
	}

	return lUser;
}

void userSetTime (User this, int time, int skiliftN) {
	this->skiliftLastTime [skiliftN] = time;
}

int userGetTime (User this, int skiliftN) {
	return this->skiliftCount [skiliftN];
}

int userGetLastTime (User this, int skiliftN) {
	return this->skiliftLastTime [skiliftN];
}

void userPrintInfo (User this, int skiliftN, Skilift *skilifts) {

	printf ("User %ld ", this->cardId);
	printf ("Visited skilift %s %d times\n",
			skiliftGetId (skilifts [skiliftN]),
			this->skiliftCount [skiliftN]);
}

void userInc (User this, int skiliftN) {
	++(this->skiliftCount [skiliftN]);
}

void printUser (User this) {
	printf ("%ld\n", this->cardId);
}

void deleteUser (User this) {
	if (this == NULL) {
		return;
	}
	free (this->skiliftCount);
	free (this->skiliftLastTime);
	free (this);
}