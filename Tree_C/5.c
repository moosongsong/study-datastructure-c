
// 8개의 LED(0~7)에 대하여 상태 정보를 저장하는 코드를 생각해 봅시다.
#include <stdio.h>
#include <stdlib.h>
enum { LED_OFF, LED_ON };

int main() {
	//int leds[8] = { 0, };	// 모두 꺼진 상태
	//char leds[8] = { 0, };	// 모두 꺼진 상태
	char leds = 0;	// 모두 꺼진 상태

	// 0번 LED가 켜진 경우
	leds[0] = LED_ON;

	// 3번 LED가 켜진 경우
	leds[3] = LED_ON;

	// LED 검사
	for (int i = 0; i < 8; i++) {
		if (leds[i] == LED_ON)
			printf("%d LED: ON\n", i);
		else
			printf("%d LED: OFF\n", i);
	}
	getchar(), system("cls");

	// 3번 LED가 꺼진 경우
	leds[3] = LED_OFF;

	// LED 검사
	for (int i = 0; i < 8; i++) {
		if (leds[i] == LED_ON)
			printf("%d LED: ON\n", i);
		else
			printf("%d LED: OFF\n", i);
	}
}