#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Array.h"

typedef struct {
	char name[32];
	char tel[32];
} Person;


#define STDIN_FLUSH()					\
	do {								\
		char ch;						\
		do {							\
			ch = getchar();				\
		} while(ch != '\n' && ch != EOF);	\
	} while(0)

void getString(const char* msg, char* out) {
	printf("%s: ", msg);
	scanf("%s", out);
	STDIN_FLUSH();
}

void pause(const char* msg) {
	printf("%s\n", msg);
	system("pause");
}

int menu() {
	system("cls");
	printf(
		"# 전화번호부 관리 프로그램 #\n"
		"1. 등록\n"
		"2. 수정\n"
		"3. 검색\n"
		"4. 삭제\n"
		"5. 목록\n"
		"-------------------------\n"
		"입력(0. 종료): "
	);
	int cmd;
	scanf("%d", &cmd);
	STDIN_FLUSH();
	return cmd;
}

int findPerson(const Array *array, const char* name) {
	for (int i = 0; i < arrayCount(array); i++) {
		Person* person = arrayGet(array, i);
		if (person != NULL) {
			if (strcmp(person->name, name) == 0) {
				return 1;
			}
		}
	}
	return 0;
}


void register_(Array *array) {
	system("cls");
	printf("# 전화번호부 등록 #\n");

	Person* p = malloc(sizeof(Person));
	getString("이름 입력", p->name);
	if (findPerson(array, p->name)) {
		pause("이미 등록된 이름입니다.");
		free(p);
		return;
	}

	getString("전화번호 입력", p->tel);
	arrayAdd(array, p);
	pause("등록되었습니다.");
}


void edit(Array *array) {
	system("cls");
	printf("# 전화번호부 수정 #\n");

	char name[32];
	getString("이름 입력", name);
	if (!findPerson(array, name)) {
		pause("그런 이름은 없습니다.");
		return;
	}

	Person* person = NULL;
	for (int i = 0; i < arrayCount(array); i++) {
		person = arrayGet(array, i);
	}

	if (person != NULL) {
		getString("새로운 전화번호 입력", person->tel);
		pause("수정되었습니다.");
	}
}

void search(const Array *array) {
	system("cls");
	printf("# 전화번호부 검색 #\n");

	char name[32];
	getString("이름 입력", name);
	for (int i = 0; i < arrayCount(array); i++) {
		Person* p = arrayGet(array, i);
		if (strcmp(p->name, name) == 0) {
			printf("전화번호는 %s입니다\n", p->tel);
			system("pause");
			return;
		}
	}
	pause("그런 이름은 없습니다.");
}
void delete(Array *array) { 
	system("cls");
	printf("# 전화번호부 삭제 #\n");

	char name[32];
	getString("이름 입력", name);
	if (!findPerson(array, name)) {
		pause("그런 이름은 없습니다.");
		return;
	}

	for (int i = 0; i < arrayCount(array); i++) {
		Person* p = arrayGet(array, i);
		if (strcmp(p->name, name) == 0) {
			free(arrayRemove(array, i));
			pause("삭제되었습니다.");
			return;
		}
	}
}
void list(const Array* array) {
	system("cls");
	printf("# 전화번호부 목록 #\n");

	for (int i = 0; i < arrayCount(array); i++) {
		Person* p = arrayGet(array, i);
		printf("%d. %s, %s\n", i + 1, p->name, p->tel);
	}
	pause("끝");
}

void run(Array *array) {
	while (1) {
		int cmd = menu();
		switch (cmd) {
		case 0: printf("프로그램을 종료합니다.\n"); return;
		case 1: register_(array); break;
		case 2: edit(array); break;
		case 3: search(array); break;
		case 4: delete(array); break;
		case 5: list(array); break;
		default:
			pause("잘못 입력하셨습니다. 다시 입력해 주세요.");
			continue;
		}
	}
}

int main() {
	Array* array = arrayCreate();
	if (array != NULL)
		run(array);
	arrayDestroy(array);
}