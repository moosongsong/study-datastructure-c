
#include <stdio.h>
#include <stdlib.h>
// 이전의 자료구조는 성능 상의 이슈가 존재합니다. 이 문제를 해결하기 위해
// 성능을 최적화합니다.
#define BIT_SET(set, idx)	((set)[(idx)>>5] |= (1 << ((idx)&31)))
#define BIT_ISSET(set, idx) ((set)[(idx)>>5] & (1 << ((idx)&31)))
#define BIT_CLR(set, idx)	((set)[(idx)>>5] &= ~(1 << ((idx)&31)))
#define BIT_ZERO(set)	\
	do { for (int i = 0; i <4; i++) (set)[i] = 0; } while(0)

typedef unsigned int bitset[4];
#define BITSET_INITIALIZER	{0,}

int main() {
	bitset leds = BITSET_INITIALIZER;
	BIT_SET(leds, 100);

	for (int i = 0; i < 128; i++) {
		if (BIT_ISSET(leds, i))
			printf("%d LED: ON\n", i);
		else
			printf("%d LED: OFF\n", i);
	}
	getchar(), system("cls");

	BIT_CLR(leds, 100);
	for (int i = 0; i < 128; i++) {
		if (BIT_ISSET(leds, i))
			printf("%d LED: ON\n", i);
		else
			printf("%d LED: OFF\n", i);
	}
}