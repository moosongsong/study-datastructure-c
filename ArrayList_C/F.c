#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

	int* contents = malloc(sizeof(int) * INITIAL_SIZE);	// * size);
	if (contents == NULL) {
		perror("arrayCreate");
		free(array);
		return NULL;
	}

	array->contents = contents;
	array->size = INITIAL_SIZE;
	return array;
}

void arrayDestroy(Array* array) {
	if (array == NULL)
		return;
	free(array->contents);
	free(array);
}

// step 14. 이전 자료구조는 자원 할당 정책이 중복되어 있다는 단점이 있습니다.
// 이는 유지 보수를 어렵게 하고 버그가 발생할 확률이 높아진다는 문제가 있습니다.
// 이를 해결하기 위해 자원 할당 정책을 한 곳으로 모으도록 합니다.
#define MAX_SIZE	(4096)
static int increaseSize(Array* array, int size) {
	// ...
	return 0;
}

int arrayAdd(Array* array, int data) {
	if (array == NULL) {
		fprintf(stderr, "arrayAdd: argument is null\n");
		return -1;
	}

	//if (array->count == array->size) {
	//	fprintf(stderr, "arrayAdd: array is full\n");
	//	return -1;
	//}

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

	//if (array->count == array->size) {
	//	fprintf(stderr, "arrayInsert: array is full\n");
	//	return -1;
	//}

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
	if (index != newCount) {	// 삭제할 원소가 마지막 원소가 아닌 경우
		memmove(array->contents + index, array->contents + index + 1,
			sizeof(int) * (newCount - index));
	}

	array->count = newCount;
	return 0;
}

int main() {
	// 아래는 테스트 코드입니다.
	Array* arr = arrayCreate();	// int arr[4];
	//--------------------------
	for (int i = 0; i < 4; i++)
		arrayAdd(arr, i + 1);
	arrayDisplay(arr);	// 1 2 3 4

	arrayInsert(arr, 0, 0);
	arrayDisplay(arr);	// 0 1 2 3 4
	//--------------------------
	arrayDestroy(arr);
}



