
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
	//-------------------------------

	//-------------------------------
	free(map->buckets);
	free(map);
}
// 위 코드는 라이브러리 설계자가 제공하는 코드입니다.
// ----------------------------------------------------------------------------------
// 아래의 코드는 사용자가 구현하는 코드입니다.

// 동명이인은 없다고 가정합니다.
// Key: Name, Value: Person
typedef struct {
	char name[32];
	int age;
} Person;

// 인자로 전달된 키를 해시 값으로 변환하는 함수
int myHash(void* key) {
	return strlen((const char*)key);
}

// 충돌된 키에 대하여 비교를 수행하는 함수
int myEquals(void* key1, void* key2) {
	if (key1 == NULL || key2 == NULL)
		return 0;
	return strcmp((const char*)key1, (const char*)key2) == 0;
}

int main() {
	Hashmap* map = hashmapCreate(myHash, myEquals);
	hashmapDestroy(map);
	return 0;
}