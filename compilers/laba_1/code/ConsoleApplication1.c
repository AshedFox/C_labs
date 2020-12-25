#include <stdio.h>
#include <string.h>
#include <conio.h>

#define numOfStates 4
#define charType 3

const int transitions[numOfStates][charType] = { {0,0,0}, {0,2,0}, {0,3,2}, {0,2,0}};
const int states[numOfStates] = { 0,0,1,0};

int processSymbol(char symbol) {
	if ((symbol >= 32 && symbol < 127) && symbol != 39) {
		return 2;
	}
	else if (symbol == 39) {
		return 1;
	}
	else {
		return 0;
	}
}

int main() {
	char line[100];
	gets(line);
	int state = 1;
	int result;
	for (int i = 0; i < strlen(line); i++) {
		state = transitions[state][processSymbol(line[i])];
	}
	result = states[state-1];
	if (!result) {
		printf("Incorrect line\n");
	}
	else {
		printf("Line is correct\n");
	}
	return 0;
}
