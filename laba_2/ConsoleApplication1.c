#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void FillMatrix(float matr[5][5]) {
	for (int i = 0; i <= sizeof(&matr); i++) {
		for (int j = 0; j <= sizeof(&matr); j++) {
			matr[i][j] = (float)(rand()%100) / (rand()%10+1);
		}
	}
}

void ShowMatrix(const float matr[5][5]) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			printf("%.2f", matr[i][j]);
			printf("\t");
		}
		printf("\n\n");
	}
}

void FindLowestFirst(const float matr[5][5]) {
	int k = 1;
	float LowestElement=matr[1][1];
	for (int i = 0; i <= 1; i++) {
		for (int j = k; j <= 4 - k; j++) {
			if (matr[i][j] < LowestElement) {
				LowestElement = matr[i][j];
			}
		}
		k++;
	}
	k = 1;
	for (int i = 4; i >= 3; i--) {
		for (int j = k; j <= 4 - k; j++) {
			if (matr[i][j] < LowestElement) {
				LowestElement = matr[i][j];
			}
		}
		k++;
	}
	printf("First task: %.2f\n", LowestElement);
}

void FindLowestSecond(const float matr[5][5]) {
	int k = 1;
	float LowestElement = matr[1][0];
	for (int i = 1; i < 3; i++) {
		for (int j = 0; j < k; j++) {
			if (matr[i][j] < LowestElement) {
				LowestElement = matr[i][j];
			}
		}
		k++;
	}
	k = 1;
	for (int i = 3; i > 2; i--) {
		for (int j = 0; j < k; j++) {
			if (matr[i][j] < LowestElement) {
				LowestElement = matr[i][j];
			}
		}
		k++;
	}
	printf("Secind task: %.2f\n", LowestElement);
}

int main()
{
	srand(time(NULL));
	float MyMatrix[5][5];

	FillMatrix(MyMatrix);
	ShowMatrix(MyMatrix);
	FindLowestFirst(MyMatrix);
	FindLowestSecond(MyMatrix);

	return 0;
}
