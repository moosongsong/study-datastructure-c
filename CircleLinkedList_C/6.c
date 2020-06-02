
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    // void* data; // int data;
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
    Node list;  
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
        // Person* p = (Person*)node->data;
        Person* p = (Person*)node;
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
        // Person* p = (Person*)node->data;
        Person* p = (Person*)node;
        printf("<->[%s(%d)]", p->name, p->age);
    }
    printf("<->[head]");
    getchar();
}

int main(void) {
    Person people[4] = {
        {{0}, "eddy", 20}, {{0}, "pororo", 30}, {{0}, "petty", 40}, {{0}, "poby", 50}
    };

    Node head;
    listInitialize(&head);
    display(&head);
    for (int i = 0; i < 4; i++) {
        listAdd(&head, &(people[i].list));
        // listAddHead(&head, nodes + i);
        display(&head);
    }
    displayBackwardly(&head);
    return 0;
}
