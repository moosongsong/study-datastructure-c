// 어제 프로젝트의 마지막 소스 파일을 복사해 오세요 :D
#define _CRT_SECURE_NO_WARNINGS
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

	// 아래의 코드는 얕은 복사입니다.
	//node->key = key;
	//node->value = value;

	// 깊은 복사 코드로 변경합니다.
	char* k = malloc(strlen(key) + 1);
	if (k == NULL) {
		perror("createNode");
		free(node);
		return NULL;
	}

	char* v = malloc(strlen(value) + 1);
	if (v == NULL) {
		perror("createNode");
		free(node);
		free(k);
		return NULL;
	}
		
	strcpy(k, key);
	strcpy(v, value);
	node->key = k;
	node->value = v;
	return node;
}

int hashmapPut(Hashmap* map, const char* key, const char* value, const char** oldValue) {
	if (map == NULL || key == NULL || value == NULL || oldValue == NULL) {
		fprintf(stderr, "hashmapPut: argument is null\n");
		return -1;
	}

	int index = strlen(key) % map->bucketSize;
	Node** ptr = &(map->buckets[index]);
	while (1) {
		Node* cur = *ptr;
		if (cur == NULL) {
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
		if (strcmp(cur->key, key) == 0) {
			*oldValue = cur->value;

			char* v = malloc(strlen(value) + 1);
			if (v == NULL) {
				perror("hashmapPut");
				return -1;
			}
			strcpy(v, value);
			cur->value = v;
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

// 만약 코드가 아래와 같이 작성할 경우, 얕은 복사가 일어나므로
// 함수 호출이 끝나면 해당 포인터는 댕글링 포인터가 됩니다.
// 이를 해결하기 위해 깊은 복사를 수행합니다.
//void foo(Hashmap *map) {
//	char buf[32];
//	printf("input key: ");
//	scanf("%s", buf);
//
//	hashmapPut(map, buf, ...);
//}

int main() {
	char* names[5] = { "daniel", "susan", "andrew", "monica", "daniel" };
	char* ages[5] = { "10", "20", "30", "40", "50" };

	Hashmap* map = hashmapCreate(10);
	hashmapDisplay(map);
	for (int i = 0; i < 5; i++) {
		char* oldValue = NULL;
		hashmapPut(map, names[i], ages[i], &oldValue);
		if (oldValue != NULL) {
			// 사용 후, 반드시 파괴해야 합니다.
			printf("밸류 %s가 삭제되었습니다.", oldValue);
			free(oldValue);
			getchar();
		}
		hashmapDisplay(map);
	}

	hashmapDestroy(map);
}