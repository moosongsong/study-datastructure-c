#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	void* key;
	void* value;
	int hash;
	struct Node* next;
} Node;

typedef int(*HashFn)(void* key);
typedef int(*EqualsFn)(void* key1, void* key2);
typedef struct Hashmap {
	Node** buckets;
	size_t bucketSize;
	size_t count;
	HashFn hash;
	EqualsFn equlas;
} Hashmap;

#define DEFALUT_BUCKET_SIZE		(16)
Hashmap* hashmapCreate(HashFn hash, EqualsFn equals) {
	if (hash == NULL || equals == NULL) {
		fprintf(stderr, "hashmapCreate: argument is null\n");
		return NULL;
	}

	Hashmap* map = calloc(1, sizeof(Hashmap));
	if (map == NULL) {
		perror("hashmapCreate");
		return NULL;
	}

	Node** buckets = calloc(DEFALUT_BUCKET_SIZE, sizeof(Node*));
	if (buckets == NULL) {
		perror("hashmapCreate");
		free(map);
		return NULL;
	}

	map->buckets = buckets;
	map->bucketSize = DEFALUT_BUCKET_SIZE;
	map->hash = hash;
	map->equlas = equals;

	return map;
}

void hashmapDestroy(Hashmap* map) {
	if (map == NULL)
		return;
	free(map->buckets);
	free(map);
}

static int hashKey(Hashmap* map, void* key) {
	int h = map->hash(key);
	h += ~(h << 9);
	h ^= (((unsigned int)h) >> 14);
	h += (h << 4);
	h ^= (((unsigned int)h) >> 10);
	return h;
}

static size_t calculateIndex(size_t bucketSize, int hash) {
	return ((size_t)hash) & (bucketSize - 1);
}

static Node* createNode(void* key, int hash, void* value) {
	Node* node = calloc(1, sizeof(Node));
	if (node == NULL) {
		perror("createNode");
		return NULL;
	}
	node->key = key;
	node->value = value;
	node->hash = hash;
	return node;
}

static int equalsKey(void* key1, int hash1, void* key2, int hash2, EqualsFn equals) {
	if (key1 == NULL || key2 == NULL || equals == NULL)
		return 0;

	if (key1 == key2)	// 주소 값이 같다면 같은 키
		return 1;
	if (hash1 != hash2)	// 주소가 같지 않으면 해시 값으로 비교
		return 0;
	return equals(key1, key2);
}

void* hashmapPut(Hashmap* map, void* key, void* value) {
	if (map == NULL || key == NULL || value == NULL) {
		fprintf(stderr, "hashmapPut: argument is null\n");
		return NULL;
	}

	int hash = hashKey(map, key);
	size_t index = calculateIndex(map->bucketSize, hash);

	Node** ptr = &(map->buckets[index]);
	while (1) {
		Node* cur = *ptr;
		if (cur == NULL) {	// 키에 대한 데이터가 존재하지 않는 경우
			Node* node = createNode(key, hash, value);
			if (node == NULL) {
				fprintf(stderr, "hashmapPut: createNode error\n");
				return NULL;
			}

			*ptr = node;
			map->count++;
			return NULL;
		}

		if (equalsKey(cur->key, cur->hash, key, hash, map->equlas) == 1) { // 키가 같은 경우
			void* oldValue = cur->value;
			cur->value = value;
			return oldValue;
		}
		ptr = &(cur->next);
	}
}

void hashmapDisplay(const Hashmap* map, const char* (*toString)(void*)) {
	if (map == NULL || toString == NULL)
		return;
	system("cls");	// system("clear");

	size_t bucketSize = map->bucketSize;
	for (size_t i = 0; i < bucketSize; i++) {
		printf("bucket[%2d]", i);

		for (Node* p = map->buckets[i]; p != NULL; p = p->next)
			printf("->[%s]", toString(p->value));
		printf("\n");
	}
	getchar();
}

void* hashmapGet(const Hashmap* map, void* key) {
	if (map == NULL || key == NULL) {
		fprintf(stderr, "hashmapGet: argument is null\n");
		return NULL;
	}

	int hash = hashKey(map, key);
	size_t index = calculateIndex(map->bucketSize, hash);
	Node* cur = map->buckets[index];	// Node* cur = head->next;
	while (cur != NULL) {
		if (equalsKey(cur->key, cur->hash, key, hash, map->equlas) == 1) {
			return cur->value;
		}
		cur = cur->next;
	}
	return NULL;
}

void* hashmapRemove(Hashmap* map, const void* key) {
	if (map == NULL || key == NULL) {
		fprintf(stderr, "hashmapRemove: argument is null\n");
		return NULL;
	}

	int hash = hashKey(map, key);
	size_t index = calculateIndex(map->bucketSize, hash);

	Node** ptr = &(map->buckets[index]);
	while (1) {
		Node* cur = *ptr;
		if (cur == NULL)
			return NULL;

		if (equalsKey(cur->key, cur->hash, key, hash, map->equlas) == 1) {
			void* value = cur->value;
			*ptr = cur->next;
			free(cur);
			--map->count;
			return value;
		}
		ptr = &(cur->next);
	}
}

// 위 코드는 라이브러리 설계자가 제공하는 코드입니다.
// ----------------------------------------------------------------------------------
// 아래의 코드는 사용자가 구현하는 코드입니다.

typedef struct {
	char name[32];
	int age;
} Person;

int myHash(void* key) {
	return strlen((const char*)key);
}

int myEquals(void* key1, void* key2) {
	if (key1 == NULL || key2 == NULL)
		return 0;
	return strcmp((const char*)key1, (const char*)key2) == 0;
}

const char* myToString(void* p) {
	static char buf[1024];
	Person* person = p;
	sprintf(buf, "%s(%d)", person->name, person->age);
	return buf;
}

int main() {
	Person people[4] = {
		{"daniel", 20}, {"susan", 30}, {"petty", 40}, {"eddy", 50}
	};
	Hashmap* map = hashmapCreate(myHash, myEquals);
	for (int i = 0; i < 4; i++)
		hashmapPut(map, people[i].name, &people[i]);
	hashmapDisplay(map, myToString);

	for (int i = 0; i < 4; i++) {
		// 아래의 hashmapRevmove 함수를 구현해 보세요 :D
		Person* p =	hashmapRemove(map, people[i].name);
		hashmapDisplay(map, myToString);
	}

	hashmapDestroy(map);
	return 0;
}