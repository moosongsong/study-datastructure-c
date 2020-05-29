
#include <stdlib.h>
#include <stdio.h>

// 노드 설계
typedef struct Node {
	int data;
	struct Node* next;
} Node;
Node* head;

// 데이터를 마지막에 추가하는 listAdd 함수를 구현해 보세요 :D
int listAdd(int data) {
	Node* node = calloc(1, sizeof(Node));	// malloc(sizeof(Node));
	if (node == NULL) {
		perror("listAdd");
		return -1;
	}
	node->data = data;
	// node->next = NULL;

	// 연결 리스트가 비어 있는 경우
	if (head == NULL) {
		head = node;
		return 0;
	}

	// 연결 리스트가 비어 있지 않은 경우
	Node* cur = head;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = node;
	return 0;
}

void listDisplay() {
	system("cls");	// clear("clear");
	printf("[head]");
	for (Node* node = head; node != NULL; node = node->next)
		printf("->[%2d]", node->data);
	getchar();
}

int main() {
	listDisplay();
	for (int i = 0; i < 5; i++) {
		listAdd(i + 1);
		listDisplay();
	}
	return 0;
}