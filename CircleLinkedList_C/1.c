
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 이전의 자료구조는 노드의 생성 및 파괴를 사용자가 처리하므로 가볍다는 장점이 있습니다.
// 하지만 더미 헤드가 여전히 동적 할당을 하고 있다는 단점이 있습니다. 이를 해결 하기위해
// 더미 헤드를 스택에 생성하겠습니다.
int listInitialize(Node* head) {
    if (head == NULL) {
        fprintf(stderr, "listInitialize(): argument is null\n");
        return -1;
    }

    head->next = head;
    return 0;
}

int listAdd(Node* head, Node* node) {
    if (head == NULL || node == NULL) {
        fprintf(stderr, "listAdd(): argument is null\n");
        return -1;
    }
    node->next = head;

    Node* cur = head;
    while (cur->next != head)
        cur = cur->next;
    cur->next = node;

    return 0;
}

void listDisplay(const Node* head) {
    if (head == NULL) {
        fprintf(stderr, "listDisplay(): argument is null\n");
        return;
    }

    system("cls");
    printf("[head]");
    for (Node* node = head->next; node != head; node = node->next)
        printf("->[%2d]", node->data);
    printf("->[head]");
    getchar();
}

int listReverse(Node* head) {
    if (head == NULL) {
        fprintf(stderr, "listReverse(): argument is null\n");
        return -1;
    }

    Node* prev = head;
    Node* cur = head->next;
    Node* next;

    while (cur != head) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    cur->next = prev;
    return 0;
}

int main(void) {
    Node head;  // Node* head;
    listInitialize(&head);

    Node nodes[5];  // 스택에 생성

    listDisplay(&head);
    for (int i = 0; i < 5; i++) {
        nodes[i].data = i + 1;
        listAdd(&head, nodes + i);
        listDisplay(&head);
    }

    listReverse(&head), listDisplay(&head);
    return 0;
}
