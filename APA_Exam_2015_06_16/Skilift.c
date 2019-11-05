#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Skilift.h"

struct skilift {
	char *skiliftId;
	int timeInterval;
};

Skilift newSkilift (char* skiliftId, int timeInterval) {
	Skilift lSkilift = malloc (sizeof (*lSkilift));
	if (lSkilift == NULL) {
		return NULL;
	}

	lSkilift->skiliftId = malloc (sizeof (skiliftId));
	if (lSkilift->skiliftId == NULL) {
		return NULL;
	}

	strcpy (lSkilift->skiliftId, skiliftId);
	lSkilift->timeInterval = timeInterval;

	return lSkilift;
}

int skiliftGetTime (Skilift this) {
	return this->timeInterval;
}

char *skiliftGetId (Skilift this) {
	return this->skiliftId;
}