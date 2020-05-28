#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Array {
	void **contents;	// int* contents;
	int size;
	int count;
} Array;

#define INITIAL_SIZE	(4)
Array* arrayCreate() {
	Array* array = calloc(1, sizeof(Array));
	if (array == NULL) {
		perror("arrayCreate");
		return NULL;
	}
	return array;
}

#define MAX_SIZE	(4096)
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

	void **newContents = NULL;
	if (array->contents == NULL) {	// 초기화
		newContents = calloc(newSize, sizeof(void*));
		if (newContents == NULL) {
			perror("increaseSize");
			return -1;
		}
	}
	else {	// 확장
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

int arrayAdd(Array* array, void *data) {
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

void arrayDisplay(const Array* array, const char*(*display)(const void*)) {
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

//int arraySet(Array* array, int index, int newData, int* oldData) {
void *arraySet(Array* array, int index, void *newData) {
	if (array == NULL) {
		fprintf(stderr, "arraySet: argument is null\n");
		return NULL;
	}

	if (index < 0 || index >= array->count) {
		fprintf(stderr, "arraySet: out of index\n");
		return NULL;
	}

	void *oldData = array->contents[index];
	array->contents[index] = newData;
	return oldData;
}

//int arrayInsert(Array* array, int index, int newData) {
int arrayInsert(Array* array, int index, void *newData) {
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

//int arrayGet(const Array* array, int index, int* outData) {
void *arrayGet(const Array* array, int index) {
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

//int arrayRemove(Array* array, int index, int* outData) {
void *arrayRemove(Array* array, int index) {
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

	void *outData = array->contents[index];

	int newCount = array->count - 1;
	if (index != newCount) {
		memmove(array->contents + index, array->contents + index + 1,
			sizeof(void*) * (newCount - index));
	}

	array->count = newCount;
	return outData;
}

// 위의 코드는 라이브러리 설계자가 구현하는 코드입니다.
// ------------------------------------------------------------------
// 아래의 코드는 사용자가 구현하는 코드입니다.

// step 16. 이전 자료구조는 정수만 저장 가능하다는 단점이 있습니다.
// 이제 모든 타입에 대하여 저장 가능한 자료구조로 변경해 보세요.
typedef struct {
	char name[32];
	int age;
} Person;

const char* toPerson(const void* data) {
	static char buf[32];
	const Person* person = (const Person*)data;
	sprintf(buf, "%s(%d)", person->name, person->age);
	return (const char*)buf;
}

int main() {
	Person people[5] = {
		{"daniel",20}, {"susan",30}, {"pororo", 40}, {"eddy", 50}, {"poby",60}
	};

	Array* arr = arrayCreate();
	arrayDisplay(arr, toPerson);
	for (int i = 0; i < 4; i++) {
		arrayAdd(arr, people + i);
		arrayDisplay(arr, toPerson);
	}

	arrayInsert(arr, 0, people + 4);
	arrayDisplay(arr, toPerson);

	arrayDestroy(arr);
}



