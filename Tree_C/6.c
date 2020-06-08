
// 8개의 LED(0~7)에 대하여 상태 정보를 저장하는 코드를 생각해 봅시다.
#include <stdio.h>
#include <stdlib.h>
enum { LED_OFF, LED_ON };

int main() {
	// 아래의 코드가 동작되도록 코드를 수정해 보세요 :D
	// char leds = 0;	// 0000 0000
	unsigned int leds = 0;

	// 0000 0001
	// 0000 1000
	// --------- | -> 합 연산자
	// 0000 1001

	// leds = leds | (1 << 0); // 0번 LED가 켜진 경우
	leds |= (1 << 0);
	leds |= (1 << 3);

	// 0000 1001 leds
	// 0000 1000 
	// --------- & -> 곱 연산자
	// 0000 1000
	for (int i = 0; i < 32; i++) {
		if ((leds & (1 << i)))	// if (leds[i] == LED_ON))
			printf("%d LED: ON\n", i);
		else
			printf("%d LED: OFF\n", i);
	}
	getchar(), system("cls");

	// 0000 1001 leds
	// 1111 0111
	// --------- &
	// 0000 0001

	// leds = leds & ~(1 << 3);	// leds[3] = LED_OFF;
	leds &= ~(1 << 3);
	for (int i = 0; i < 32; i++) {
		if ((leds & (1 << i)))	// if (leds[i] == LED_ON))
			printf("%d LED: ON\n", i);
		else
			printf("%d LED: OFF\n", i);
	}
}