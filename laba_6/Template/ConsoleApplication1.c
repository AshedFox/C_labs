#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main()
{
	FILE* f1 = fopen("F1.txt", "w");
	FILE* f2 = fopen("F2.txt", "r");
	FILE* f3 = fopen("F3.txt", "w");

	float num;
	num = 19.0f / 2;
	char buff[100];
	while (!feof(f2)) {
		fscanf(f2,"%s\n", buff);
		int num = atoi(buff);
		if (num % 5 == 0) {
			fprintf(f1, "%s\n", buff);
		}
		if ((num < 0) && (num % 3 == 0)) {
			fprintf(f3, "%s\n", buff);
		}
	}
	fclose(f1);
	fclose(f2);
	fclose(f3);

	f1 = fopen("F_1.txt", "r");
	FILE* f = fopen("F.txt", "w");

	char surname[100], name[100], ageBuff[100];
	int students[100] = { 0 };
	int numOfStudents = 1;
	int avg = 0;

	while (!feof(f1)) {
		fscanf(f1, "%s%s%s\n", surname, name, ageBuff);
		avg += atoi(ageBuff);
		numOfStudents++;
	}

	f1 = fopen("F_1.txt", "r");
	avg /= numOfStudents;
	fprintf(f, "Average age: %d\n\n", avg);

	while (!feof(f1)) {
		fscanf(f1, "%s%s%s\n", surname, name, ageBuff);
		if (atoi(ageBuff) > avg) {
			fprintf(f, "%s %s %s\n", surname, name, ageBuff);			
		}
		
	}
	fclose(f);
	fclose(f1);

	return 0;
}
