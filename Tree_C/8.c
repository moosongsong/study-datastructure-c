
#include <stdio.h>
#include <stdlib.h>
#define BIT_SET(set, idx)	((set)[(idx)/32] |= (1 << ((idx)%32)))
#define BIT_ISSET(set, idx) ((set)[(idx)/32] & (1 << ((idx)%32)))
#define BIT_CLR(set, idx)	((set)[(idx)/32] &= ~(1 << ((idx)%32)))
#define BIT_ZERO(set)	\
	do { for (int i = 0; i <4; i++) (set)[i] = 0; } while(0)

// 이전 자료구조는 타입이 추상화되어 있지 않다는 단점이 있습니다. 이를 해결하기 위해
// 타입을 추상화합니다.
typedef unsigned int bitset[4];

// 정적 초기화를 위한 매크로 심볼을 제공합니다.
#define BITSET_INITIALIZER	{0,}

int main() {
	//bitset leds = { 0, };	// unsigned int leds[4] = { 0, };
	bitset leds = BITSET_INITIALIZER; //bitset leds = 0;
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

	//leds = BITSET_INITIALIZER;
	BIT_ZERO(leds);
}