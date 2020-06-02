
#include <stdio.h>
#include <stdlib.h>


// 이전의 자료구조는 정수 타입의 데이터만 저장할 수 있다는 단점이 있습니다.
// 이제 모든 타입을 처리하기 위해 void*를 사용한 코드로 변경해 보세요 :D
typedef struct Node {
    void* data; // int data;
    struct Node* next;
    struct Node* prev;
} Node;

int listInitialize(Node* head) {
    if (head == NULL) {
        fprintf(stderr, "listInitialize(): argument is null\n");
        return -1;
    }
    head->next = head;
    head->prev = head;
    return 0;
}

static void insertNode(Node* new, Node* prev, Node* next) {
    new->next = next;
    new->prev = prev;
    prev->next = new;
    next->prev = new;
}

int listAdd(Node* head, Node* node) {
    if (head == NULL || node == NULL) {
        fprintf(stderr, "listAdd: argument is null\n");
        return -1;
    }
    insertNode(node, head->prev, head);
    return 0;
}

int listAddHead(Node* head, Node* node) {
    if (head == NULL || node == NULL) {
        fprintf(stderr, "listAddHead: argument is null\n");
        return -1;
    }
    insertNode(node, head, head->next);
    return 0;
}

// 위의 코드는 라이브러리가 제공하는 코드입니다.
// ----------------------------------------------------------------------------------
// 아래의 코드는 사용자가 구현하는 코드입니다.
typedef struct Person {
    char name[32];
    int age;
} Person;

void display(const Node* head) {
    if (head == NULL) {
        fprintf(stderr, "display(): argument is null\n");
        return;
    }

    system("cls");
    printf("[head]");
    for (Node* node = head->next; node != head; node = node->next) {
        // printf("<->[%2d]", node->data);
        Person* p = (Person*)node->data;
        printf("<->[%s(%d)]", p->name, p->age);
    }
    printf("<->[head]");
    getchar();
}

void displayBackwardly(const Node* head) {
    if (head == NULL) {
        fprintf(stderr, "displayBackwardly(): argument is null\n");
        return;
    }

    system("cls");
    printf("[head]");
    for (Node* node = head->prev; node != head; node = node->prev) {
        // printf("<->[%2d]", node->data);
        Person* p = (Person*)node->data;
        printf("<->[%s(%d)]", p->name, p->age);
    }
    printf("<->[head]");
    getchar();
}

int main(void) {
    Person people[4] = {
        {"eddy", 20}, {"pororo", 30}, {"petty", 40}, {"poby", 50}
    };

    Node nodes[4];

    Node head;
    listInitialize(&head);
    display(&head);
    for (int i = 0; i < 4; i++) {
        nodes[i].data = people + i; // nodes[i].data = &people[i];
        listAdd(&head, nodes + i);
        // listAddHead(&head, nodes + i);
        display(&head);
    }
    displayBackwardly(&head);
    return 0;
}
