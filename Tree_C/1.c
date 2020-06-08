
#include <stdlib.h>
#include <stdio.h>
// 이진 검색 트리(BST)
typedef struct Node {
	int data;
	struct Node* left;
	struct Node* right;
} Node;
Node* root;

int bstInsert(int data) {
	Node* node = calloc(1, sizeof(Node));
	if (node == NULL) {
		perror("bstInsert");
		return -1;
	}
	node->data = data;
	if (root == NULL) {	// 트리가 비어 있는 경우
		root = node;
		return 0;
	}
	Node* parent = NULL;
	Node* cur = root;
	while (cur != NULL) {
		parent = cur;
		if (data < cur->data)
			cur = cur->left;
		else if (data > cur->data)
			cur = cur->right;
		else {
			free(node);
			return -1;
		}
	}
	if (data < parent->data) parent->left = node;
	else parent->right = node;
	return 0;
}

static void fillArray(int(*arr)[10], int* row, int* col, Node* node) {
	if (node == NULL)
		return;
	++(*row);
	fillArray(arr, row, col, node->left);
	arr[*row][(*col)++] = node->data;
	fillArray(arr, row, col, node->right);
	--(*row);
}

void bstDisplay() {
	int arr[10][10] = { 0, };
	int row = -1, col = 0;

	system("cls");
	fillArray(arr, &row, &col, root);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (arr[i][j])
				printf("(%2d)", arr[i][j]);
			else
				printf("%4c", ' ');
		}
		printf("\n");
	}
	getchar();
}

int main() {
	int arr[8] = { 4, 2, 1, 3, 6, 5, 7, 8 };

	bstDisplay();
	for (int i = 0; i < 8; i++) {
		bstInsert(arr[i]);
		bstDisplay();
	}
	return 0;
}