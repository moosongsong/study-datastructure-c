
#include <stdio.h>

// 배열의 한계
// 1. 배열의 크기(길이) 정보가 없음
// 2. 배열의 범위를 넘어설 경우를 알 수 없음
// 3. 배열의 크기를 조절할 수 없음
#define ARR_SIZE(a)		(sizeof((a))/sizeof(*(a)))
void printArray(const int arr[]) {	// void printArray(const int *arr) {
	for (int i = 0; i < ARR_SIZE(arr); i++)
		printf("%d ", arr[i]);
	printf("\n");
}

int main() {
	//            0 1 2 3 4
	int arr[] = { 1,2,3,4,5 };

	// for (int i = 0; i < 5; i++)
	//for (int i = 0; i < ARR_SIZE(arr); i++)
	//	printf("%d ", arr[i]);
	//printf("\n");
	printArray(arr);

	arr[5] = 10;	// ??
}