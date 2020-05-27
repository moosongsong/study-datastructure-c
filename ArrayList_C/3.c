// 2.c의 모든 코드를 복사해 오세요 
#include <stdio.h>
#include <stdlib.h>	// system()

// step 2. 이전 자료구조는 추가가 잘 동작하나 2개 이상의 자료구조를 만들 수 없다는
// 문제가 있습니다. 이는 함수가 전역 심볼을 직접적으로 사용하고 있기 때문입니다.
// 이제 이 문제를 해결하기 위해 전역 심볼을 지역 심볼로 변경하여 처리합니다.
int arrayAdd(int *arr, int size, int *count, int data) {
	if (*count == size)
		return -1;
	arr[(*count)++] = data;
	return 0;
}

void arrayDisplay(const int *arr, int size, int count) {
	system("cls");
	for (int i = 0; i < size; i++) {
		if (i < count)
			printf("[%2d]", arr[i]);
		else
			printf("[%2c]", ' ');
	}
	getchar();
}

int main() {
	// 이제 2개 이상의 자료구조를 생성할 수 있습니다.
	int arr[5];
	int size = 5;
	int count = 0;
	arrayDisplay(arr, size, count);
	for (int i = 0; i < 10; i++) {
		arrayAdd(arr, size, &count, i + 1);
		arrayDisplay(arr, size, count);
	}

	int arr1[5];
	int size1 = 5;
	int count1 = 0;
	arrayDisplay(arr1, size1, count1);
	for (int i = 0; i < 10; i++) {
		arrayAdd(arr1, size1, &count1, i + 10);
		arrayDisplay(arr1, size1, count1);
	}
}




