
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
	int data;
	struct Node* next;
} Node;
Node* head;

// 이전 자료구조는 삽입 알고리즘이 이원화되어 있다는 단점이 있습니다.
// 이를 해결 하기 위해 더미 헤드를 삽입합니다.

int listAdd(int data) {
	Node* node = calloc(1, sizeof(Node));
	if (node == NULL) {
		perror("listAdd");
		return -1;
	}
	node->data = data;

	//if (head == NULL) {
	//	head = node;
	//	return 0;
	//}

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

int main() {
	// 더미 헤드를 추가합니다.
	head = calloc(1, sizeof(Node)); //head = malloc(sizeof(Node));
									//head->next = NULL;


	listDisplay();
	for (int i = 0; i < 5; i++) {
		listAdd(i + 1);
		listDisplay();
	}
	return 0;
}