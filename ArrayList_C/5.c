#include <stdio.h>
#include <stdlib.h>

// step 4. 이전 자료구조는 자료구조 생성 시, 내부 데이터가 초기화되지 않는다는
// 단점이 있습니다. 이를 해결하기 위해 자료구조를 초기화하는 함수를 추가합니다.
typedef struct Array {
	int contents[5];
	int size;
	int count;
} Array;

int arrayInitiate(Array* array) {
	if (array == NULL) {
		fprintf(stderr, "arrayAdd: argument is null\n");
		return -1;
	}
	array->count = 0;
	array->size = 5;
	return 0;
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
	Array arr1;
	arrayInitiate(&arr1);

	arrayDisplay(&arr1);
	for (int i = 0; i < 10; i++) {
		arrayAdd(&arr1, i + 1);
		arrayDisplay(&arr1);
	}
}




