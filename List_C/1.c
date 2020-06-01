
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


int main() {
	listIntialize();
	return 0;
}