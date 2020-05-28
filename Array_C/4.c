#include <stdio.h>
#include <stdlib.h>

// step 3. 이전 자료구조는 데이터들이 분리되어 있어 사용하기 어렵다는 단점이 있습니다.
// 이를 해결하기 위해 데이터를 묶어 새로운 타입으로 정의(추상화)합니다.
//int arr[5];
//int size = 5;
//int count = 0;

typedef struct Array {
	int contents[5];	// int arr[5];
	int size;
	int count;
} Array;

//int arrayAdd(int* arr, int size, int* count, int data) {
int arrayAdd(Array *array, int data) {
	if (array == NULL) {
		fprintf(stderr, "arrayAdd: argument is null\n");
	}

	if (array->count == array->size)
		return -1;

	array->contents[array->count] = data;
	++(array->count);
	return 0;
}

//void arrayDisplay(const int* arr, int size, int count) {
void arrayDisplay(const Array *array) {
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
	Array arr1;
	arr1.size = 5;
	arr1.count = 0;
	arrayDisplay(&arr1); // arrayDisplay(arr, size, count);
	for (int i = 0; i < 10; i++) {
		arrayAdd(&arr1, i + 1);
		arrayDisplay(&arr1); // arrayDisplay(arr, size, count);
	}

	Array arr2;
	arr2.size = 5;
	arr2.count = 0;
	arrayDisplay(&arr2); // arrayDisplay(arr, size, count);
	for (int i = 0; i < 10; i++) {
		arrayAdd(&arr2, i + 1);
		arrayDisplay(&arr2); // arrayDisplay(arr, size, count);
	}

}




