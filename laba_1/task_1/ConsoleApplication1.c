#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main()
{
	unsigned int MyArray[6][6];
	unsigned int max, min, MaxPos, MinPos, temp;

	srand(time(NULL));

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			MyArray[i][j] = rand()%100;
		}
	}

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			printf("%d", MyArray[i][j]);
			printf("%s", "\t");
		}
		printf("%s", "\n");
	}


	for (int i = 0; i < 6; i++) {
		max = MyArray[i][0];
		min = MyArray[i][0];
		MaxPos = 0; MinPos = 0;
		for (int j = 0; j < 6; j++) {
			if (max < MyArray[i][j]) {
				MaxPos = j;
				temp = max;
				max = MyArray[i][j];
				MyArray[i][j] = max;
			}
			if (min > MyArray[i][j]) {
				MinPos = j;
				temp = min;
				min = MyArray[i][j];
				MyArray[i][j] = min;
			}
		}
		MyArray[i][MinPos] = max;
		MyArray[i][MaxPos] = min;
	}

	printf("%s", "\n");

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			printf("%d", MyArray[i][j]);
			printf("%s", "\t");
		}
		printf("%s", "\n");
	}

	return 0;
}
