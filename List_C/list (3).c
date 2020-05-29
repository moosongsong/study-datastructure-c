
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
	int data;
	struct Node* next;
} Node;
Node* head;

int listAdd(int data) {
	Node* node = calloc(1, sizeof(Node));
	if (node == NULL) {
		perror("listAdd");
		return -1;
	}
	node->data = data;

	Node* cur = head;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = node;
	return 0;
}

void listDisplay() {
	system("cls");
	printf("[head]");
	for (Node* node = head->next; node != NULL; node = node->next)
		printf("->[%2d]", node->data);
	getchar();
}

// 이전 자료구조의 문제는 자료구조의 초기화를 사용자가 해야 한다는 단점이 있습니다.
// 이를 해결하기 위해 자료구조를 초기화하는 함수를 제공하도록 합니다.
int listInitialize() {
	head = calloc(1, sizeof(Node));
	if (head == NULL) {
		perror("listInitialize");
		return -1;
	}
	return 0;
}

int main() {
	//head = calloc(1, sizeof(Node));
	listInitialize();

	listDisplay();
	for (int i = 0; i < 5; i++) {
		listAdd(i + 1);
		listDisplay();
	}
	return 0;
}