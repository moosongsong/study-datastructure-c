
#include <stdlib.h>
#include <stdio.h>

// 1. 해쉬 데이터 타입 설계
#define KEY_LEN_MAX		(32)
#define VALUE_LEN_MAX	(92)
typedef struct HashData {
	char key[KEY_LEN_MAX];
	char value[VALUE_LEN_MAX];
} HashData;

// 2. 해시맵 정보 구조체(context) 설계
typedef struct Hashmap {
	size_t count;		// 해시맵에 저장된 데이터의 갯수
	size_t capacity;	// 해시맵에 저장할 수 있는 최대 데이터 갯수
	size_t offsets[];
} Hashmap;

Hashmap* hashmapCreate(size_t nData) {
	if (nData == 0) {
		fprintf(stderr, "hashmapCreate: argument is zero\n");
		return NULL;
	}

	size_t mapSize = sizeof(Hashmap) +  (sizeof(size_t) * nData) + (sizeof(HashData) * nData);
	Hashmap* map = calloc(1, mapSize);
	if (map == NULL) {
		perror("hashmapCreate");
		return NULL;
	}
	map->capacity = nData;
	return map;
}

void hashmapDestroy(Hashmap* map) {
	if (map == NULL)
		return;
	free(map);
}

int main() {
	Hashmap* map = hashmapCreate(10);
	if (map == NULL)
		return -1;

	hashmapDestroy(map);
}
