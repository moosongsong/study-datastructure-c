
#include <stdio.h>
#include <stdlib.h>

typedef void(*FreeFunction)(const void*);

typedef struct Node {
	void* data;	// int data;
	struct Node* next;
	struct Node* prev;
} Node;

typedef struct List {
	Node* head;
	Node* tail;
	FreeFunction freeFn;
	int count;
} List;

static Node* toNode(const List *list, int index) {
	if (index < 0 || index >= list->count)
		return NULL;

	Node* node;
	if (index < (list->count >> 1)) {
		node = list->head->next;
		for (int i = 0; i < index; i++)
			node = node->next;
	}
	else {
		node = list->tail->prev;
		for (int i = list->count - 1; i > index; i--)
			node = node->prev;
	}
	return node;
}

List* listIntialize(FreeFunction fn) {
	Node *head = malloc(sizeof(Node));
	if (head == NULL) {
		perror("listInitialize");
		return NULL;
	}

	Node *tail = malloc(sizeof(Node));
	if (tail == NULL) {
		perror("listIntialize");
		free(head);
		return NULL;
	}

	head->next = tail;
	head->prev = head;
	tail->prev = head;
	tail->next = tail;

	List* list = malloc(sizeof(List));
	if (list == NULL) {
		perror("listInitalize");
		free(head);
		free(tail);
		return NULL;
	}

	list->head = head;
	list->tail = tail;
	list->count = 0;
	list->freeFn = fn;
	return list;
}

void listFinalize(List* list) {
	if (list == NULL) {
		fprintf(stderr, "listFinalize: argument is null\n");
		return;
	}

	// 리스트가 비어 있지 않다면
	// 1. 노드 안에 저장된 자원을 해제(freeFn이 널이 아닌 경우)
	// 2. 노드 삭제
	// 3. 더미 헤드와 더미 테일 삭제
	// 4. 리스트 정보 구조체(컨텍스트) 삭제
}

int listInsert(List *list, int index, void* data) {
	if (list == NULL) {
		fprintf(stderr, "listInsert: argument is null\n");
		return -1;
	}

	if (index < 0 || index >= list->count) {
		fprintf(stderr, "listInsert: out of index\n");
		return -1;
	}

	Node* new = malloc(sizeof(Node));
	if (new == NULL) {
		perror("listInsert");
		return -1;
	}
	new->data = data;

	Node* next = toNode(list, index);
	Node* prev = next->prev;

	new->prev = prev;
	new->next = next;
	prev->next = new;
	next->prev = new;

	++list->count;
	return 0;
}

//int listDisplay(const List *list) {
//	if (list == NULL) {
//		fprintf(stderr, "listDisplay: argument is null\n");
//		return -1;
//	}
//	Node* head = list->head;
//	Node* tail = list->tail;
//
//	system("cls");
//	printf("[head]");
//	for (Node* cur = head->next; cur != tail; cur = cur->next)
//		printf("<->[%2d]", cur->data);
//	printf("<->[tail]");
//	getchar();
//	return 0;
//}
//
//int listDisplayBackwardly(const List *list) {
//	if (list == NULL) {
//		fprintf(stderr, "listDisplayBackwardly: argument is null\n");
//		return -1;
//	}
//	Node* head = list->head;
//	Node* tail = list->tail;
//
//	system("cls");
//	printf("[tail]");
//	for (Node* cur = tail->prev; cur != head; cur = cur->prev)
//		printf("<->[%2d]", cur->data);
//	printf("<->[head]");
//	getchar();
//	return 0;
//}

int listAdd(List *list, void* data) {
	if (list == NULL) {
		fprintf(stderr, "listAdd: argument is null\n");
		return -1;
	}

	Node* node = malloc(sizeof(Node));
	if (node == NULL) {
		perror("listAdd");
		return -1;
	}
	node->data = data;
	Node* tail = list->tail;

	node->next = tail;
	node->prev = tail->prev;

	tail->prev->next = node;
	tail->prev = node;
	++list->count;
	return 0;
}


int listAddHead(List *list, void* data) {
	if (list == NULL) {
		fprintf(stderr, "listAddHead: argument is null\n");
		return -1;
	}

	Node* node = malloc(sizeof(Node));
	if (node == NULL) {
		perror("listAddHead");
		return -1;
	}
	node->data = data;
	Node* head = list->head;

	node->next = head->next;
	node->prev = head;

	head->next->prev = node;
	head->next = node;
	++list->count;

	return 0;
}

int listCount(const List *list) {
	if (list == NULL) {
		fprintf(stderr, "listCount: argument is null\n");
		return -1;
	}
	return list->count;
}

void* listGet(const List *list, int index) {
	if (list == NULL) {
		fprintf(stderr, "listGet: argument is null\n");
		return NULL;
	}

	if (index < 0 || index >= list->count) {
		fprintf(stderr, "listGet: out of index\n");
		return NULL;
	}
	return toNode(list, index)->data;
}

void* listRemoveTail(List* list) {
	if (list == NULL) {
		fprintf(stderr, "listRemoveTail: arguement is null\n");
		return NULL;
	}

	if (list->count == 0) {
		fprintf(stderr, "listRemoveTail: list is empty\n");
		return NULL;
	}

	Node* tail = list->tail;

	Node* target = tail->prev;
	tail->prev = target->prev;
	target->prev->next = tail;

	void* outData = target->data;
	free(target);
	--list->count;
	return outData;
}

void* listRemoveHead(List* list) {
	if (list == NULL ) {
		fprintf(stderr, "listRemoveHead: arguement is null\n");
		return NULL;
	}

	if (list->count == 0) {
		fprintf(stderr, "listRemoveHead: list is empty\n");
		return NULL;
	}

	Node* head = list->head;

	Node* target = head->next;
	head->next = target->next;
	target->next->prev = head;

	void *outData = target->data;
	free(target);
	--list->count;
	return outData;
}

void* listRemove(List *list, int index) {
	if (list == NULL) {
		fprintf(stderr, "listRemove: argument is null\n");
		return NULL;
	}

	if (list->count == 0) {
		fprintf(stderr, "listRemove: list is empty\n");
		return NULL;
	}

	if (index < 0 || index >= list->count) {
		fprintf(stderr, "listRemove: out of index\n");
		return NULL;
	}
	Node* target = toNode(list, index);

	Node* prev = target->prev;
	Node* next = target->next;

	prev->next = next;
	next->prev = prev;

	void *outData = target->data;
	free(target);
	--list->count;
	return outData;
}

int main() {
	List *list = listIntialize();

	listDisplay(list);
	for (int i = 0; i < 5; i++)
		listAddHead(list, i + 1);
	listDisplay(list);

	int count = listCount(list);
	for (int i = 0; i < count; i++) {
		int data;
		// listRemoveTail(list, &data);
		// listRemoveHead(list, &data);
		listRemove(list, 0, &data);
		listDisplay(list);
	}



	return 0;
}