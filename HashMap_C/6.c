#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define KEY_LEN_MAX		(32)
#define VALUE_LEN_MAX	(92)
typedef struct HashData {
	char key[KEY_LEN_MAX];
	char value[VALUE_LEN_MAX];
} HashData;

typedef struct Hashmap {
	size_t count;	
	size_t capacity;
	size_t offsets[];
} Hashmap;

Hashmap* hashmapCreate(size_t nData) {
	if (nData == 0) {
		fprintf(stderr, "hashmapCreate: argument is zero\n");
		return NULL;
	}

	size_t mapSize = sizeof(Hashmap) + (sizeof(size_t) * nData) + (sizeof(HashData) * nData);
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


int hashmapPut(Hashmap* map, const char* key, const char* value) {
	if (map == NULL || key == NULL || value == NULL) {
		fprintf(stderr, "hashmapPut: argument is null\n");
		return -1;
	}

	int keyLen = strlen(key);
	int valLen = strlen(value);
	if (keyLen >= KEY_LEN_MAX || valLen >= VALUE_LEN_MAX) {
		fprintf(stderr, "hashmapPut: key or value too long\n");
		return -1;
	}

	// hashmapPut(map, "", "");
	if (keyLen == 0) {
		fprintf(stderr, "hashmapPut: key is null-string\n");
		return -1;
	}

	HashData* data = hashmapFind(map, key);
	if (data != NULL) {	// 기존 데이터가 존재하는 경우
		memcpy(data->value, value, valLen + 1);	// 덮어씁니다.
	}
	else {	// 기존 데이터가 없는 경우
		if (map->count == map->capacity) {
			fprintf(stderr, "hashmapPut: hashmap is full\n");
			return -1;
		}

		size_t hashDataStart = sizeof(Hashmap) + (sizeof(size_t) * map->capacity);
		HashData* hashData = (HashData*)((char*)map + hashDataStart);
		memcpy(hashData[map->count].key, key, keyLen + 1);
		memcpy(hashData[map->count].value, value, valLen + 1);

		map->offsets[map->count] = (keyLen << 24) | ((size_t)(hashData + map->count) - (size_t)map);
		++map->count;
	}
	return 0;
}




















int main() {
	Hashmap* map = hashmapCreate(10);

	hashmapDestroy(map);
}
