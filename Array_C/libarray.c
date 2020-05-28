// libarray.c
// 2.c에서 라이브러리 설계자가 구현하는 코드를 복사해 오세요

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Array.h"

// 소스 코드에 구조체를 정의합니다.
typedef struct Array {
	void** contents;
	int size;
	int count;
} Array;

Array* arrayCreate() {
	Array* array = calloc(1, sizeof(Array));
	if (array == NULL) {
		perror("arrayCreate");
		return NULL;
	}
	return array;
}

static int increaseSize(Array* array, int size) {
	if (array == NULL) {
		fprintf(stderr, "increaseSize: argument is null\n");
		return -1;
	}

	if (size <= 0) {
		fprintf(stderr, "increaseSize: size is zero or negative\n");
		return -1;
	}

	if (size < array->size)
		return 0;

	int newSize = (array->size == 0) ? INITIAL_SIZE : array->size;
	while (newSize < size) {
		newSize *= 2;
		if (newSize > MAX_SIZE || newSize < array->size)
			newSize = MAX_SIZE;
	}

	void** newContents = NULL;
	if (array->contents == NULL) {	
		newContents = calloc(newSize, sizeof(void*));
		if (newContents == NULL) {
			perror("increaseSize");
			return -1;
		}
	}
	else {
		newContents = realloc(array->contents, sizeof(void*) * newSize);
		if (newContents == NULL) {
			perror("increaseSize");
			return -1;

		}
	}

	array->contents = newContents;
	array->size = newSize;
	return 0;
}


void arrayDestroy(Array* array) {
	if (array == NULL)
		return;
	free(array->contents);
	free(array);
}

int arrayAdd(Array* array, void* data) {
	if (array == NULL) {
		fprintf(stderr, "arrayAdd: argument is null\n");
		return -1;
	}

	if (increaseSize(array, array->count + 1) == -1) {
		fprintf(stderr, "arrayAdd: memiry allocation failed\n");
		return -1;
	}

	array->contents[array->count] = data;
	++(array->count);
	return 0;
}

void arrayDisplay(const Array* array, const char* (*display)(const void*)) {
	if (array == NULL || display == NULL) {
		fprintf(stderr, "arrayDisplay: argument is null\n");
		return;
	}

	system("cls");
	for (int i = 0; i < array->size; i++) {
		if (i < array->count)
			printf("[%s]", display(array->contents[i]));
		else
			printf("[%2c]", ' ');
	}
	getchar();
}

void* arraySet(Array* array, int index, void* newData) {
	if (array == NULL) {
		fprintf(stderr, "arraySet: argument is null\n");
		return NULL;
	}

	if (index < 0 || index >= array->count) {
		fprintf(stderr, "arraySet: out of index\n");
		return NULL;
	}

	void* oldData = array->contents[index];
	array->contents[index] = newData;
	return oldData;
}

int arrayInsert(Array* array, int index, void* newData) {
	if (array == NULL) {
		fprintf(stderr, "arrayInsert: argument is null\n");
		return -1;
	}

	if (increaseSize(array, array->count + 1) == -1) {
		fprintf(stderr, "arrayAdd: memiry allocation failed\n");
		return -1;
	}

	memmove(array->contents + index + 1, array->contents + index,
		sizeof(void*) * (array->count - index));

	array->contents[index] = newData;
	++(array->count);
	return 0;
}

int arrayCount(const Array* array) {
	if (array == NULL) {
		fprintf(stderr, "arrayCount: argument is null\n");
		return -1;
	}
	return array->count;
}

void* arrayGet(const Array* array, int index) {
	if (array == NULL) {
		fprintf(stderr, "arrayGet: argument is null\n");
		return NULL;
	}

	if (index < 0 || index >= array->count) {
		fprintf(stderr, "arrayGet: out of index\n");
		return NULL;
	}
	return  array->contents[index];
}

void* arrayRemove(Array* array, int index) {
	if (array == NULL) {
		fprintf(stderr, "arrayRemove: argument is null\n");
		return NULL;
	}

	if (array->count == 0) {
		fprintf(stderr, "arrayRemove: array is empty\n");
		return NULL;
	}

	if (index < 0 || index >= array->count) {
		fprintf(stderr, "arrayRemove: out of index\n");
		return NULL;
	}

	void* outData = array->contents[index];

	int newCount = array->count - 1;
	if (index != newCount) {
		memmove(array->contents + index, array->contents + index + 1,
			sizeof(void*) * (newCount - index));
	}

	array->count = newCount;
	return outData;
}