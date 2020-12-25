#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int totalAmount;


struct TreeNode {
	char value;
	struct TreeNode* left;
	struct TreeNode* right;
};

struct TreeNode* addNode(struct TreeNode* node, char* values, int length) {
	int curPriority = 9, k = 0;
	int brackets = 0;
	int isAnyOperation = 0;
	for (int i = 0; i <= length; i++) {
		switch (values[i])
		{
		case '+':
		case '-': {
			if (curPriority >= 1 && brackets == 0) {
				curPriority = 1;
				k = i;
				isAnyOperation = 1;
			}
			break;
		}
		case '*':
		case '/': {
			if (curPriority >= 2 && brackets == 0) {
				curPriority = 2;
				k = i;
				isAnyOperation = 1;
			}
			break;
		}
		case '^': {
			if (curPriority >= 3 && brackets == 0) {
				curPriority = 3;
				k = i;
				isAnyOperation = 1;
			}
			break;
		}
		case '(':
			brackets++;
			break;
		case ')':
			brackets--;
			break;
		}
	}

	if (isAnyOperation == 0 && length > 2) {
		char* buff = (char*)malloc(length - 2);
		strncpy(buff, values + 1, length - 2);
		values = (char*)malloc(length - 2);
		values = buff;
		length -= 2;
		node = addNode(node, values, length);
	}
	else {
		node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
		if (node != NULL)
			node->value = values[k];
		if (length > 1) {
			node->right = addNode(node->right, values, k - 1);
			node->left = addNode(node->left, values + k + 1, length - k - 1);
		}
		else {
			node->right = NULL;
			node->left = NULL;
		}
	}
	return node;
}

struct TreeNode* initTree(struct TreeNode* head, char* values, int numOfElements) {
	int i = 0;
	head = addNode(head, values, numOfElements-1);
	return head;
}

void showTree(struct TreeNode* curNode, int curLevel) {
	if (curNode != NULL) {
		showTree(curNode->right, curLevel + 4);
		for (int i = 0; i < curLevel; i++)
			printf(" ");
		printf("|%c\n", curNode->value);
		showTree(curNode->left, curLevel + 4);
	}
}

void ShowInPrefixForm(struct TreeNode* curNode) {
	if (curNode != NULL) {
		printf("%c", curNode->value);
		if (curNode->right != NULL) {
			ShowInPrefixForm(curNode->right);
		}
		if (curNode->left != NULL) {
			ShowInPrefixForm(curNode->left);
		}
	}
}

int main()
{
	srand((int)time(NULL));
	struct TreeNode* treeHead = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	treeHead = NULL;

	char expression[] = "s*l/(x-f*t*p+w)";

	treeHead = initTree(treeHead, expression, sizeof(expression));

	showTree(treeHead, 0);

	printf("\nInfix form: %s\n\n", expression);

	printf("Prefix form: ");
	ShowInPrefixForm(treeHead);
	printf("\n");

	free(treeHead);
	return 0;
}
