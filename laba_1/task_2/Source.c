#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	unsigned int MyArray[5][5];

	unsigned int MinPos, min, temp;

	srand(time(NULL));
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			MyArray[i][j] = rand()%100;
		}
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			printf("%d", MyArray[i][j]);
			printf("%s", "\t");
		}
		printf("%s", "\n");
	}

	for (int i = 0; i < 5; i++) {
		min = MyArray[0][i];
		MinPos = 0;
		for (int j = 1; j < 5; j++) {
			if (MyArray[j][i] < min) {
				MinPos = j;
				min = MyArray[j][i];
			}
		}
		temp = MyArray[4-i][i];
		MyArray[4-i][i] = min;
		MyArray[MinPos][i] = temp;
	}

	printf("%s", "\n");

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			printf("%d", MyArray[i][j]);
			printf("%s", "\t");
		}
		printf("%s", "\n");
	}

	return 0;
}
