#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct enrollee {
	char* surname;
	char* adress;
	float avgMark;
};

int main()
{
	srand(time(NULL));

	struct enrollee Enrollee[12] = { {"Stone", "st. abc 8, Minsk", 8.9f}, {"Alfy", "st. bcd 9, Grodno", 5.6f}, {"Cin", "st. cba 7, Lida", 7.8f},
									 {"Mall", "st. aaa 27, Minsk", 7.1f}, {"Avgustov", "st. ojk 9, Minsk", 7.0f}, {"Cherry", "st. bus 5, Brest", 6.4f},
									 {"Lemon", "st. bb 11, Vitebsk", 6.6f}, {"Han", "st. cba 7, Minsk", 5.9f}, {"Luter", "st. alo 18, Minsk", 8.7f},
									 {"Warhol", "st. nex 23, Minsk", 7.9f}, {"Pollo", "st. he 3, Vitebsk", 9.1f}, {"Huges", "st. nex 17, Minsk", 7.9f}};

	for (int i = 0; i < 12; i++) {
		printf("%15s%30s%7.2f\n", Enrollee[i].surname, Enrollee[i].adress, Enrollee[i].avgMark);
	}
	printf("\n");


	int numOfMinskEnrolle=0;
	for (int i = 0; i < 12; i++) {
		if ((strstr(Enrollee[i].adress, "Minsk")!=NULL) && (Enrollee[i].avgMark>=7.0f)) {
			numOfMinskEnrolle++;
		}
	}

	struct enrollee* OkEnrollee = malloc(numOfMinskEnrolle*sizeof(struct enrollee));
	int k=0;
	for (int i = 0; i < 12; i++) {
		if ((strstr(Enrollee[i].adress, "Minsk")!=NULL) && (Enrollee[i].avgMark>=7.0f)) {
			OkEnrollee[k].surname = Enrollee[i].surname;
			OkEnrollee[k].adress = Enrollee[i].adress;
			OkEnrollee[k].avgMark = Enrollee[i].avgMark;
			k++;
		}
	}

	printf("Num of enrollee from Minsk with mark not lower than 7: %d\n\n", numOfMinskEnrolle);

	for (int i = 0; i < numOfMinskEnrolle-1; i++) {
		for (int j = 0; j < numOfMinskEnrolle-i-1; j++) {
			if (strcmp(OkEnrollee[j].surname, OkEnrollee[j+1].surname) > 0) {
				char* temp1 = OkEnrollee[j+1].surname;
				OkEnrollee[j+1].surname = OkEnrollee[j].surname;
				OkEnrollee[j].surname = temp1;
				char* temp2 = OkEnrollee[j + 1].adress;
				OkEnrollee[j + 1].adress = OkEnrollee[j].adress;
				OkEnrollee[j].adress = temp2;
				float temp3 = OkEnrollee[j + 1].avgMark;
				OkEnrollee[j + 1].avgMark = OkEnrollee[j].avgMark;
				OkEnrollee[j].avgMark = temp3;
			}
		}
	}

	for (int i = 0; i < numOfMinskEnrolle; i++) {
		printf("%15s%30s%7.2f\n", OkEnrollee[i].surname, OkEnrollee[i].adress, OkEnrollee[i].avgMark);
	}

	return 0;
}
