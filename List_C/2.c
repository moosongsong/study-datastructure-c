
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node* next;
	struct Node* prev;
} Node;

Node* head;
Node* tail;

int listIntialize() {
	head = malloc(sizeof(Node));
	if (head == NULL) {
		perror("listInitialize");
		return -1;
	}

	tail = malloc(sizeof(Node));
	if (tail == NULL) {
		perror("listIntialize");
		free(head);
		return -1;
	}

	head->next = tail;
	head->prev = head;

	tail->prev = head;
	tail->next = tail;
	return 0;
}

int listAdd(int data) {
	Node* node = malloc(sizeof(Node));
	if (node == NULL) {
		perror("listAdd");
		return -1;
	}
	node->data = data;

	node->next = tail;
	node->prev = tail->prev;

	tail->prev->next = node;
	tail->prev = node;

	return 0;
}

void listDisplay() {
	system("cls");
	printf("[head]");
	for (Node* cur = head->next; cur != tail; cur = cur->next)
		printf("<->[%2d]", cur->data);
	printf("<->[tail]");
	getchar();
}

void listDisplayBackwardly() {
	system("cls");
	printf("[tail]");
	for (Node* cur = tail->prev; cur != head; cur = cur->prev)
		printf("<->[%2d]", cur->data);
	printf("<->[head]");
	getchar();
}

int main() {
	listIntialize();

	listDisplay();
	for (int i = 0; i < 5; i++) {
		listAdd(i + 1);
		listDisplay();
	}

	listDisplayBackwardly();

	return 0;
}