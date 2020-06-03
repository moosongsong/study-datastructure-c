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

#define GET_KEY_LENGTH(x)	((x) >> 24)
#define GET_HASH_DATA(start, offset)	\
	(HashData*)((char*)start + ((offset) & 0xFFFFFF))
static HashData* findHashData(Hashmap* map, const char* key) {
	if (map == NULL || key == NULL) {
		fprintf(stderr, "findHashData: argument is null\n");
		return NULL;
	}

	size_t* offsets = map->offsets;
	size_t keyLen = strlen(key);

	size_t count = map->count;
	while (count--) {
		size_t offset = *offsets++;
		if (GET_KEY_LENGTH(offset) != keyLen)
			continue;

		HashData* data = GET_HASH_DATA(map, offset);
		if (memcmp(key, data->key, keyLen + 1))
			continue;
		return data;
	}
	return NULL;
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

	if (keyLen == 0) {
		fprintf(stderr, "hashmapPut: key is null-string\n");
		return -1;
	}

	HashData* data = findHashData(map, key);
	if (data != NULL) {
		memcpy(data->value, value, valLen + 1);
	}
	else {
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

const char* hashmapGet(Hashmap* map, const char* key) {
	if (map == NULL || key == NULL) {
		fprintf(stderr, "hashmapGet: argument is null\n");
		return NULL;
	}

	HashData* data = findHashData(map, key);
	if (data == NULL) {
		fprintf(stderr, "hashmapGet: findHashData error\n");
		return NULL;
	}
	return data->value;
}

int main() {
	Hashmap* map = hashmapCreate(10);
	hashmapPut(map, "hello", "world");
	const char* value = hashmapGet(map, "hello");
	if (value)
		printf("key: %s, value: %s\n", "hello", value);

	hashmapPut(map, "hello", "kkkkkk");
	value = hashmapGet(map, "hello");
	if (value)
		printf("key: %s, value: %s\n", "hello", value);

	hashmapDestroy(map);
}
