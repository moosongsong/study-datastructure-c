#include <stdio.h>
#include <stdlib.h>
#include <string.h>	// memmove

typedef struct Array {
	int* contents;
	int size;
	int count;
} Array;

Array* arrayCreate(size_t size) {
	if (size == 0) {
		fprintf(stderr, "arrayCreate: size is zero\n");
		return NULL;
	}

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

// step 9. 특정 위치에 삽입을 하는 arrayInsert 함수를 구현해 보세요  :D
int arrayInsert(Array* array, int index, int newData) {
	if (array == NULL) {
		fprintf(stderr, "arrayInsert: argument is null\n");
		return -1;
	}

	if (array->count == array->size) {
		fprintf(stderr, "arrayInsert: array is full\n");
		return -1;
	}

	if (index < 0 || index >= array->count) {
		fprintf(stderr, "arrayInsert: out of index\n");
		return -1;
	}

	// 아래의 코드는 성능 상의 이슈가 있으므로 memmove를 사용하도록 합니다.
	//for (int i = array->count; i != index; i--)
	//	array->contents[i] = array->contents[i - 1];
	//memmove(&array->contents[index + 1], &array->contents[index],
	//	sizeof(int) * (array->count - index));
	memmove(array->contents + index + 1, array->contents + index,
		sizeof(int) * (array->count - index));

	array->contents[index] = newData;
	++(array->count);
	return 0;
}

int main() {
	Array* arr = arrayCreate(10);
	//--------------------------
	for (int i = 0; i < 5; i++)
		arrayAdd(arr, i + 1);
	arrayDisplay(arr);	// 1 2 3 4 5 

	arrayInsert(arr, 2, 0);
	arrayDisplay(arr);	// 1 2 0 3 4 5 

	arrayInsert(arr, 0, 0);
	arrayDisplay(arr);	// 0 1 2 0 3 4 5 

	//--------------------------
	arrayDestroy(arr);
}



