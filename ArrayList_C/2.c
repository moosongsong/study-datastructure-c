#include <stdio.h>
#include <stdlib.h>	// system()

// step 1. 정수를 저장하는 배열을 생각해 봅시다.
int arr[5];
int size = 5;
int count;	// 배열 안의 원소의 갯수 & 저장할 다음 위치

int arr1[5];
int size1 = 5;
int count1;	// 배열 안의 원소의 갯수 & 저장할 다음 위치

// 다른 라이브러리의 심볼과 충돌을 막기 위해 관례적으로 라이브러리 이름을
// 접두어로 사용합니다.
int arrayAdd(int data) {
	// 배열이 가득 찼는지를 조사
	if (count == size)
		return -1;
	arr[count++] = data;
	return 0;
}

int arrayAdd(int data) {
	// 배열이 가득 찼는지를 조사
	if (count1 == size1)
		return -1;
	arr1[count1++] = data;
	return 0;
}

// 디버깅 코드
void arrayDisplay() {
	system("cls");	// cls: 윈도우에서 화면을 지우는 명령어
					// clear: 리눅스에서 화면을 지우는 명령어

	for (int i = 0; i < size; i++) {
		if (i < count)
			printf("[%2d]", arr[i]);
		else
			printf("[%2c]", ' ');
	}
	getchar();
}

int main() {
	arrayDisplay();
	for (int i = 0; i < 10; i++) {
		arrayAdd(i + 1);
		arrayDisplay();
	}
}




