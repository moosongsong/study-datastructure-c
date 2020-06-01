
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


//int listGet(int index, int* outData) {
//	if (outData == NULL) {
//		fprintf(stderr, "listGet: argument is null\n");
//		return -1;
//	}
//
//	if (index < 0 || index >= count) {
//		fprintf(stderr, "listGet: out of index\n");
//		return -1;
//	}
//
//	Node* node = head->next;
//	for (int i = 0; i < index; i++)
//		node = node->next;
//
//	*outData = node->data;
//	return 0;
//}


// 이전의 함수는 처음부터 순차 탐색을 수행하므로 노드의 개수가 많아지면
// 성능이 떨어진다는 단점이 있습니다. 이를 해결하기 위해 탐색의 범위를
// 반으로 줄이도록 합니다.
int listGet(int index, int* outData) {
	if (outData == NULL) {
		fprintf(stderr, "listGet: argument is null\n");
		return -1;
	}

	if (index < 0 || index >= count) {
		fprintf(stderr, "listGet: out of index\n");
		return -1;
	}

	// 0100 = 4
	// 0100 >> 1 -> 0010 = 2

	Node* node;
	//if (index < (count / 2)) {
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
int main() {
	listIntialize();

	for (int i = 0; i < 5; i++)
		listAdd(i + 1);

	for (int i = 0; i < listCount(); i++) {
		int data;
		listGet(i, &data);
		printf("%d\n", data);
	}

	return 0;
}