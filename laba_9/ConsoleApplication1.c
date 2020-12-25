#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int totalAmount;

struct TreeNode {
	int value;
	struct TreeNode* left;
	struct TreeNode* right;
};

struct TreeNode* addNode(struct TreeNode* node, int value) {
	if (node == NULL) {
		node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
		if (node != NULL) {
			node->value = value;
			node->left = NULL;
			node->right = NULL;
		}
	}
	else  if (node->value < value) {
		node->left = addNode(node->left, value);
	}
	else {
		node->right = addNode(node->right, value);
	}
	return(node);
}

struct TreeNode* initTree(struct TreeNode* head, int* values, int numOfElements) {
	for (int i = 0; i < numOfElements; i++) {
		head = addNode(head, values[i]);
	}
	return head;
}

void showTree(struct TreeNode* curNode, int curLevel) {
	if (curNode != NULL) {		
		showTree(curNode->right, curLevel+4);
		for (int i = 0; i < curLevel; i++)
			printf(" ");
		printf("|%d\n", curNode->value);
		showTree(curNode->left, curLevel+4);
	}
}

void countNodesWithTwoBranches(struct TreeNode* head) {
	if (head != NULL) {
		if (head->left != NULL) {
			countNodesWithTwoBranches(head->left);
		}
		if (head->right != NULL) {
			countNodesWithTwoBranches(head->right);
		}
		if (head->right != NULL && head->left != NULL) {
			totalAmount++;
			printf("%d; ", head->value);
		}
	}
}

int main()
{
	srand((int)time(NULL));
	struct TreeNode* treeHead = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	treeHead = NULL;

	int amountOfElements = 5;
	printf("Enter amount of elements in tree: ");
	scanf("%d", &amountOfElements);
	printf("\n\n");

	int *values = (int*)malloc(amountOfElements * sizeof(int));

	for (int i = 0; i < amountOfElements; i++) {
		if (values)
			values[i] = rand() % 100;
	}

	treeHead = initTree(treeHead, values, amountOfElements);

	showTree(treeHead, amountOfElements);

	printf("\n\nNodes with two branches: ");
	totalAmount = 0;
	countNodesWithTwoBranches(treeHead);
	printf("\nTotal amount of nodes with two brunches: %d\n", totalAmount);

	free(values);
	free(treeHead);
	return 0;
}
