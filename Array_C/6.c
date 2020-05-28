#include <stdio.h>
#include <stdlib.h>

// step 5. 이전 자료구조는 자료구조의 컨텍스트를 저장하기 위해 스택 메모리를 사용하고 있다는
// 단점이 있습니다. 이를 해결하기 위해 정보 구조체를 힙에 생성하도록 합니다.
typedef struct Array {
	int contents[5];
	int size;
	int count;
} Array;

//int arrayInitiate(Array* array) {
int arrayCreate(Array **array) {
	if (array == NULL) {
		fprintf(stderr, "arrayAdd: argument is null\n");
		return -1;
	}

	Array* temp = malloc(sizeof(Array));
	if (temp == NULL) {
		perror("malloc");
		return -1;
	}

	temp->count = 0;
	temp->size = 5;
	*array = temp;
	return 0;
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
	Array* arr;// Array arr;
	arrayCreate(&arr); //arrayInitiate(&arr);
	//----------------------------
	arrayDisplay(arr);
	for (int i = 0; i < 10; i++) {
		arrayAdd(arr, i + 1);
		arrayDisplay(arr);
	}
	//----------------------------
	arrayDestroy(arr);
}




