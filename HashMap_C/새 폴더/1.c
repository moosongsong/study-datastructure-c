
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	void* key;
	void* value;
	int hash;	// 키에 대한 해시 값, key의 타입을 알 수 없으므로
				// 사용자로부터 정보를 얻어 해시 값을 계산하여 저장합니다.
	struct Node* next;
} Node;

typedef int(*HashFn)(void* key);
typedef int(*EqualsFn)(void* key1, void* key2);
typedef struct Hashmap {
	Node** buckets;
	size_t bucketSize;
	size_t count;

	HashFn hash;					// 키를 정수, 즉 해시로 변환하는 함수
	EqualsFn equlas;	// 데이터 비교를 위한 함수
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

int main() {
	
	return 0;
}