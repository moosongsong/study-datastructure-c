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

	// 문자열의 길이를 해시 값으로 사용
	int index = strlen(key) % map->bucketSize;A
	Node* cur = map->buckets[index];

	// 해당 버킷이 비어 있는 경우(충돌이 발생하지 않은 경우)
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

	// 해당 버킷이 비어 있지 않은 경우(충돌이 발생한 경우)
	while (cur) {
		if (strcmp(cur->key, key) == 0) {	// 기존 키가 존재하는 경우
			*oldValue = cur->value;
			cur->value = value;
			return 0;
		}
		cur = cur->next;
	}

	// 키가 존재하지 않는 경우
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

int main() {
	char* names[5] = { "daniel", "susan", "andrew", "monica", "jessy" };
	char* ages[5] = { "10", "20", "30", "40", "50" };

	Hashmap* map = hashmapCreate(10);
	for (int i = 0; i < 5; i++) {
		char* oldValue = NULL;
		// 아래의 함수를 구현해 보세요 :D
		hashmapPut(map, names[i], ages[i], &oldValue);
	}

	hashmapDestroy(map);
}