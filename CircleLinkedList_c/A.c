
#include <stdio.h>
#include <stdlib.h>

// 이전 자료구조는 메모리 사용 정책을 사용자에게 강요하고 있다는 단점이 있습니다.
// 이를 해결 하기위해 메모리 할당 정책을 사용자에게 위임하도록 합니다.
typedef struct Node {
    int data;
    struct Node* next;
} Node;

int listInitialize(Node** head) {
    if (head == NULL) {
        fprintf(stderr, "listInitialize(): argument is null\n");
        return -1;
    }

    *head = calloc(1, sizeof(Node));
    if (*head == NULL) {
        perror("listInitialize()");
        return -1;
    }

    (*head)->next = *head;
    return 0;
}

void listFinalize(Node** head) {
    if (head == NULL) {
        fprintf(stderr, "listFinalize(): argument is null\n");
        return;
    }

    if (*head == NULL) {
        fprintf(stderr, "listFinalize(): list is wrong\n");
        return;
    }

    if ((*head)->next == *head) {
        fprintf(stderr, "listFinalize(): list is empty\n");
        return;
    }

    Node* cur = (*head)->next;
    while (cur->next != *head) {
        Node* target = cur;
        cur = cur->next;
        free(target);
    }

    free(*head);
    *head = NULL;
}

// 아래의 코드를 수정해 보세요 :D
// 아래의 코드를 다 수정하신 분들은 데이터를 힙에 생성하는 코드와 스택에 생성하는 코드를
// 2개 작성해 보세요 :D -> main 함수를 변경하시면 됩니다.
//int listAdd(Node* head, int data) {
int listAdd(Node* head, Node* node) {
    if (head == NULL || node == NULL) {
        fprintf(stderr, "listAdd(): argument is null\n");
        return -1;
    }

    //Node* node = calloc(1, sizeof(Node));
    //if (node == NULL) {
    //    perror("listAdd()");
    //    return -1;
    //}
    //node->data = data;

    node->next = head;  // node->next = tail;

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
    Node* head;
    listInitialize(&head);

    Node nodes[5];  // 스택에 생성

    listDisplay(head);
    for (int i = 0; i < 5; i++) {
        //Node* node = malloc(sizeof(Node));  // 힙에 생성
        //node->data = i + 1;
        nodes[i].data = i + 1;
        listAdd(head, nodes + i);
        listDisplay(head);
    }

    listReverse(head), listDisplay(head);
    listReverse(head), listDisplay(head);

    listFinalize(&head);
    return 0;
}
