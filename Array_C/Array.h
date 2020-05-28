// Array.h
#ifndef _ARRAY_H_
#define _ARRAY_H_

typedef struct Array Array;	// 구조체 선언과 별칭

// 아래의 심볼은  사용자가 결정할 수 있도록 헤더에 정의합니다.
#define INITIAL_SIZE	(4)	
#define MAX_SIZE		(4096)

Array* arrayCreate();
void arrayDestroy(Array* array);
int arrayAdd(Array* array, void* data);
void arrayDisplay(const Array* array, const char* (*display)(const void*));
void* arraySet(Array* array, int index, void* newData);
int arrayInsert(Array* array, int index, void* newData);
int arrayCount(const Array* array);
void* arrayGet(const Array* array, int index);
void* arrayRemove(Array* array, int index);

#endif