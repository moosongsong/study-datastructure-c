
#include <stdio.h>

typedef struct Node {
	struct Node* next;
	struct Node* prev;
} Node;

typedef struct {
	char name[32];
	int age;
	Node list;
} Person;

int main() {
	Person p = { "daniel", 20 };
	Node* pList = &p.list;

	// 아래의 한 줄을 완성해 보세요 :D
	Person* ptr = (Person*)((char*)pList - (long)&((Person*)0)->list);
	printf("%s, %d\n", ptr->name, ptr->age);

}