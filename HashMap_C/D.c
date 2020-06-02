#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	const char* key;
	const char* value;
	struct Node* next;
} Node;

typedef struct Hashmap {
	Node** buckets;
	size_t bucketSize;
	size_t count;
} Hashmap;

Hashmap* hashmapCreate(size_t bucketSize) {
	if (bucketSize == 0) {
		fprintf(stderr, "hashmapCreate: bucket size is zero\n");
		return NULL;
	}

	Node** buckets = calloc(bucketSize, sizeof(Node*));
	if (buckets == NULL) {
		perror("hashmapCreate");
		return NULL;
	}

	Hashmap* map = calloc(1, sizeof(Hashmap));
	if (map == NULL) {
		perror("hashmapCreate");
		free(buckets);
		return NULL;
	}

	map->buckets = buckets;
	map->bucketSize = bucketSize;
	return map;
}

void hashmapDestroy(Hashmap* map) {
	if (map == NULL)
		return;
	free(map->buckets);
	free(map);
}

int hashmapPut(Hashmap* map, const char* key, const char* value, const char** oldValue) {
	if (map == NULL || key == NULL || value == NULL || oldValue == NULL) {
		fprintf(stderr, "hashmapPut: argument is null\n");
		return -1;
	}

	int index = strlen(key) % map->bucketSize;
		Node* cur = map->buckets[index];

	if (cur == NULL) {
		Node* node = calloc(1, sizeof(Node));
		if (node == NULL) {
			perror("hashmapPut");
			return -1;
		}

		*oldValue = NULL;
		node->key = key;
		node->value = value;
		map->buckets[index] = node;
		map->count++;

		return 0;
	}

	while (cur) {
		if (strcmp(cur->key, key) == 0) {	// 기존 키가 존재하는 경우
			*oldValue = cur->value;
			cur->value = value;
			return 0;
		}
		cur = cur->next;
	}

	Node* node = calloc(1, sizeof(Node));
	if (node == NULL) {
		perror("hashmapPut");
		return -1;
	}
	*oldValue = NULL;
	node->key = key;
	node->value = value;

	node->next = map->buckets[index];
	map->buckets[index] = node;
	++map->count;
	return 0;
}

void hashmapDisplay(const Hashmap* map) {
	if (map == NULL)
		return;
	system("cls");

	size_t bucketSize = map->bucketSize;
	for (size_t i = 0; i < bucketSize; i++) {
		printf("bucket[%2lu]", i);

		for (Node* cur = map->buckets[i]; cur != NULL; cur = cur->next)
			printf("->[%s(%s)]", cur->key, cur->value);
		printf("\n");
	}
	getchar();
}

int main() {
	char* names[5] = { "daniel", "susan", "andrew", "monica", "jessy" };
	char* ages[5] = { "10", "20", "30", "40", "50" };

	Hashmap* map = hashmapCreate(10);
	hashmapDisplay(map);
	for (int i = 0; i < 5; i++) {
		char* oldValue = NULL;
		hashmapPut(map, names[i], ages[i], &oldValue);
		hashmapDisplay(map);
	}

	hashmapDestroy(map);
}