#include <stdio.h>
#include <stdlib.h>

// step 7. 이전 자료구조는 배열의 크기가 고정되어 있다는 단점이 있습니다. 이를 해결하기 위해
// 포인터를 도입합니다.
typedef struct Array {
	int *contents;	// int contents[5];
	int size;
	int count;
} Array;

Array* arrayCreate(size_t size) {
	if (size == 0) {
		fprintf(stderr, "arrayCreate: size is zero\n");
		return NULL;
	}

	//Array* array = malloc(sizeof(Array));
	Array* array = calloc(1, sizeof(Array));
	if (array == NULL) {
		perror("arrayCreate");
		return NULL;
	}

	int* contents = malloc(sizeof(int) * size);
	if (contents == NULL) {
		perror("arrayCreate");
		free(array);
		return NULL;
	}

	array->contents = contents;
	array->size = size;
	return array;
}

void arrayDestroy(Array* array) {
	if (array == NULL)
		return;
	// 자원의 해제는 생성의 역순으로 해야 합니다.
	free(array->contents);
	free(array);
}

int arrayAdd(Array* array, int data) {
	if (array == NULL) {
		fprintf(stderr, "arrayAdd: argument is null\n");
		return -1;
	}

	if (array->count == array->size)
		return -1;

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

int main() {
	Array* arr = arrayCreate(7);
	if (arr == NULL)
		return -1; 
	arrayDisplay(arr);
	for (int i = 0; i < 10; i++) {
		arrayAdd(arr, i + 1);
		arrayDisplay(arr);
	}
	arrayDestroy(arr);
}



