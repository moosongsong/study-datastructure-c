// 어제 프로젝트의 마지막 소스 파일을 복사해 오세요 :D
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

// 이전 자료구조는 데이터 삽입에 대한 코드가 이원화되어 있다는 단점이 있습니다.
// 이를 해결해 보세요 :D
static Node* createNode(const char* key, const char* value) {
	if (key == NULL || value == NULL) {
		fprintf(stderr, "createNode: argument is null\n");
		return NULL;
	}

	Node* node = calloc(1, sizeof(Node));
	if (node == NULL) {
		perror("createNode");
		return NULL;
	}

	node->key = key;
	node->value = value;
	return node;
}

int hashmapPut(Hashmap* map, const char* key, const char* value, const char** oldValue) {
	if (map == NULL || key == NULL || value == NULL || oldValue == NULL) {
		fprintf(stderr, "hashmapPut: argument is null\n");
		return -1;
	}

	int index = strlen(key) % map->bucketSize;
	// Node* cur = map->buckets[index];
	Node** ptr = &(map->buckets[index]);
	while (1) {
		Node* cur = *ptr;
		if (cur == NULL) {	// 버킷이 비어 있는 경우
			Node* node = createNode(key, value);
			if (node == NULL) {
				fprintf(stderr, "hashmapCreate: createNode error\n");
				return -1;
			}

			*oldValue = NULL;
			*ptr = node;
			map->count++;
			return 0;
		}
		// 버킷이 비어 있지 않은 경우
		if (strcmp(cur->key, key) == 0) {	// 동일한 키가 존재하는 경우
			*oldValue = cur->value;
			cur->value = value;
			return 0;
		}
		ptr = &(cur->next);
	}
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