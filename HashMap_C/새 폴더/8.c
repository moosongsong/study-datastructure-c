
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

int main() {
	int arr[8] = { 4, 2, 1, 3, 6, 5, 7, 8 };
	for (int i = 0; i < 8; i++)
		bstInsert(arr[i]);
}