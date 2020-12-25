#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STACK_SIZE 32

struct Stack {
	int* element;
	int top;
};

void ShowStack(struct Stack *stack) {
	for (int i = 0; i < stack->top; i++) {
		printf("%d ", stack->element[i]);
	}
	printf("\n");
}

void Push(struct Stack *stack, int newElem) {
	if (stack->top < STACK_SIZE) {
		stack->element[stack->top++] = newElem;
	}
	else
		printf("Stack overflow");
}

void Pop(struct Stack *stack, int *dest) {
	if (stack->top - 1 >= 0) {
		dest = stack->element[stack->top];
		--stack->top;
	}
}

void ChoosePos(struct Stack* sourceStack, struct Stack* destStack) {
	int buff;
	for (int i = 0; i < sourceStack->top; i++) {
		if (sourceStack->element[i] > 0) {
			Push(destStack, sourceStack->element[i]);
		}
	}
}

void ChooseNeg(struct Stack* sourceStack, struct Stack* destStack) {
	int buff;
	for (int i = 0; i < sourceStack->top; i++) {
		if (sourceStack->element[i] < 0) { 
			Push(destStack, sourceStack->element[i]);
		}
	}
}

void InitializeStack(struct Stack* stack) {
	stack->element = malloc(STACK_SIZE * sizeof(&stack->element));
	stack->top = 0;
}


int main()
{
	srand(time(NULL));
	struct Stack mainStack;

	InitializeStack(&mainStack);
	for (int i = 0; i < STACK_SIZE; i++) {
		Push(&mainStack, rand() % 50 - 25);
	}
	printf("Basic stack: \n");
	ShowStack(&mainStack);
	struct Stack posStack, negStack;
	InitializeStack(&posStack);
	InitializeStack(&negStack);
	printf("Stack with positive: \n");
	ChoosePos(&mainStack, &posStack);
	ShowStack(&posStack);
	printf("Stack with negative: \n");
	ChooseNeg(&mainStack, &negStack);
	ShowStack(&negStack);

	return 0;
}
