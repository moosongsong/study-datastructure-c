#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// step 15. 이전의 자료구조는 언제 사용될지 모르는 배열에서 대하여 미리 할당한다는
// 단점이 있습니다. 이는 자칫 메모리 낭비가 될 수 있습니다. 이를 해결하기 위해
// 지연된 초기화(lazy initialization)를 도입합니다.
typedef struct Array {
	int* contents;
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

// 아래의 코드를 적절하게 수정하시면 됩니다.
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

	int* newContents = NULL;
	if (array->contents == NULL) {	// 초기화
		newContents = calloc(newSize, sizeof(int));
		if (newContents == NULL) {
			perror("increaseSize");
			return -1;
		}
	}
	else {	// 확장
		newContents = realloc(array->contents, sizeof(int) * newSize);
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

int arrayAdd(Array* array, int data) {
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

void arrayDisplay(const Array* array) {
	system("cls");
	for (int i = 0; i < array->size; i++) {
		if (i < array->count)
			printf("[%2d]", array->contents[i]);
		else
			printf("[%2c]", ' ');
	}
	getchar();
}

int arraySet(Array* array, int index, int newData, int* oldData) {
	if (array == NULL || oldData == NULL) {
		fprintf(stderr, "arraySet: argument is null\n");
		return -1;
	}

	if (index < 0 || index >= array->count) {
		fprintf(stderr, "arraySet: out of index\n");
		return -1;
	}

	*oldData = array->contents[index];
	array->contents[index] = newData;
	return 0;
}

int arrayInsert(Array* array, int index, int newData) {
	if (array == NULL) {
		fprintf(stderr, "arrayInsert: argument is null\n");
		return -1;
	}

	if (increaseSize(array, array->count + 1) == -1) {
		fprintf(stderr, "arrayAdd: memiry allocation failed\n");
		return -1;
	}

	memmove(array->contents + index + 1, array->contents + index,
		sizeof(int) * (array->count - index));

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

int arrayGet(const Array* array, int index, int* outData) {
	if (array == NULL || outData == NULL) {
		fprintf(stderr, "arrayGet: argument is null\n");
		return -1;
	}

	if (index < 0 || index >= array->count) {
		fprintf(stderr, "arrayGet: out of index\n");
		return -1;
	}

	*outData = array->contents[index];
	return 0;
}

int arrayRemove(Array* array, int index, int* outData) {
	if (array == NULL || outData == NULL) {
		fprintf(stderr, "arrayRemove: argument is null\n");
		return -1;
	}

	if (array->count == 0) {
		fprintf(stderr, "arrayRemove: array is empty\n");
		return -1;
	}

	if (index < 0 || index >= array->count) {
		fprintf(stderr, "arrayRemove: out of index\n");
		return -1;
	}

	*outData = array->contents[index];

	int newCount = array->count - 1;
	if (index != newCount) {
		memmove(array->contents + index, array->contents + index + 1,
			sizeof(int) * (newCount - index));
	}

	array->count = newCount;
	return 0;
}

int main() {
	Array* arr = arrayCreate();

	arrayDisplay(arr);
	for (int i = 0; i < 4; i++) {
		arrayAdd(arr, i + 1);
		arrayDisplay(arr);
	}

	arrayInsert(arr, 0, 0);
	arrayDisplay(arr);

	arrayDestroy(arr);
}



