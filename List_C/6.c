
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node* next;
	struct Node* prev;
} Node;

Node* head;
Node* tail;
int count;

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
	count = 0;
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
	++count;

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

int listAddHead(int data) {
	Node* node = malloc(sizeof(Node));
	if (node == NULL) {
		perror("listAddHead");
		return -1;
	}
	node->data = data;

	node->next = head->next;
	node->prev = head;

	head->next->prev = node;
	head->next = node;
	++count;

	return 0;
}

int listInsert(int index, int data) {
	if (index < 0 || index >= count) {
		fprintf(stderr, "listInsert: out of index\n");
		return -1;
	}

	Node* new = malloc(sizeof(Node));
	if (new == NULL) {
		perror("listInsert");
		return -1;
	}
	new->data = data;

	Node* next = head->next;
	for (int i = 0; i < index; i++)
		next = next->next;
	Node* prev = next->prev;

	new->prev = prev;
	new->next = next;
	prev->next = new;
	next->prev = new;

	++count;
	return 0;
}

int listCount() { return count; }

int listGet(int index, int* outData) {
	if (outData == NULL) {
		fprintf(stderr, "listGet: argument is null\n");
		return -1;
	}

	if (index < 0 || index >= count) {
		fprintf(stderr, "listGet: out of index\n");
		return -1;
	}

	Node* node;
	if (index < (count >> 1)) {
		node = head->next;
		for (int i = 0; i < index; i++)
			node = node->next;
	}
	else {
		node = tail->prev;
		for (int i = count - 1; i > index; i--)
			node = node->prev;
	}
	*outData = node->data;
	return 0;
}

// 아래의 함수를 구현해 보세요 
// 1. listRemoveTail
int listRemoveTail(int* outData) {
	if (count == 0) {
		fprintf(stderr, "listRemoveTail: list is empty\n");
		return -1;
	}

	if (outData == NULL) {
		fprintf(stderr, "listRemoveTail: argument is null\n");
		return -1;
	}

	Node* target = tail->prev;
	tail->prev = target->prev;
	target->prev->next = tail;

	*outData = target->data;
	free(target);
	--count;
	return 0;
}

// 2. listRemoveHead
int listRemoveHead(int* outData) {
	if (count == 0) {
		fprintf(stderr, "listRemoveHead: list is empty\n");
		return -1;
	}

	if (outData == NULL) {
		fprintf(stderr, "listRemoveHead: argument is null\n");
		return -1;
	}

	Node* target = head->next;
	head->next = target->next;
	target->next->prev = head;

	*outData = target->data;
	free(target);
	--count;
	return 0;
}
// 3. listRemove
int listRemove(int index, int* outData) {
	if (count == 0) {
		fprintf(stderr, "listRemove: list is empty\n");
		return -1;
	}

	if (index < 0 || index >= count) {
		fprintf(stderr, "listRemove: out of index\n");
		return -1;
	}

	if (outData == NULL) {
		fprintf(stderr, "listRemove: argument is null\n");
		return -1;
	}

	Node* target = head->next;
	for (int i = 0; i < index; i++)
		target = target->next;

	Node* prev = target->prev;
	Node* next = target->next;

	prev->next = next;
	next->prev = prev;

	*outData = target->data;
	free(target);
	--count;
	return 0;
}

int main() {
	listIntialize();

	for (int i = 0; i < 5; i++)
		listAdd(i + 1);
	listDisplay();	// 1 2 3 4 5

	int count = listCount();
	for (int i = 0; i < count; i++) {
		int data;
		// listRemoveTail(&data);
		// listRemoveHead(&data);
		listRemove(0, &data);
		listDisplay();
	}

	return 0;
}