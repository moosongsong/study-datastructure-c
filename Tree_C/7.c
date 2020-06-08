
#include <stdio.h>
#include <stdlib.h>
// 이전의 코드는 사용하기가 어렵다는 단점이 있습니다. 이를 해결하기 위해
// 연산을 추상화합니다. 즉 함수로 래핑합니다.
#define BIT_SET(set, idx)	((set) |= (1 << (idx)))
#define BIT_ISSET(set, idx) ((set) & (1 << (idx)))
#define BIT_CLR(set, idx)	((set) &= ~(1 << (idx)))

int main() {
	//unsigned int leds = 0;
	unsigned int leds[4] = 0;
	BIT_SET(leds, 0);	// leds |= (1 << 0);
	BIT_SET(leds, 31);	// leds |= (1 << 3);

	for (int i = 0; i < 32; i++) {
		if (BIT_ISSET(leds, i))	// if ((leds & (1 << i)))
			printf("%d LED: ON\n", i);
		else
			printf("%d LED: OFF\n", i);
	}
	getchar(), system("cls");

	BIT_CLR(leds, 31);	// leds &= ~(1 << 3);
	for (int i = 0; i < 32; i++) {
		if (BIT_ISSET(leds, i))	// if ((leds & (1 << i)))
			printf("%d LED: ON\n", i);
		else
			printf("%d LED: OFF\n", i);
	}
}