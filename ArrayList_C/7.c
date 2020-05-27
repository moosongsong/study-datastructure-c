#include <stdio.h>
#include <stdlib.h>

// step 6. 이전 자료구조는 함수로 전달되는 배열에 대하여 그 방식이 일반화되지 않았습니다.
// 이는 자료구조의 사용을 어렵게 한다는 단점이 됩니다. 이를 해결해 보도록 합니다.
typedef struct Array {
	int contents[5];
	int size;
	int count;
} Array;

//int arrayCreate(Array** array) {
Array *arrayCreate() {
	Array* array = malloc(sizeof(Array));
	if (array == NULL) {
		perror("arrayCreate");
		return NULL;
	}

	array->count = 0;
	array->size = 5;
	return array;
}

void arrayDestroy(Array* array) {
	if (array == NULL)
		return;
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
	Array* arr = arrayCreate();
	if (arr == NULL)
		return -1;

	arrayDisplay(arr);
	for (int i = 0; i < 10; i++) {
		arrayAdd(arr, i + 1);
		arrayDisplay(arr);
	}
	arrayDestroy(arr);
}




