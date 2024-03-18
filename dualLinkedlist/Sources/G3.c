#include <stdio.h>
#include <stdlib.h>

// 定义双链表节点
typedef struct DListNode {
    int data;
    struct DListNode* prev;
    struct DListNode* next;
} DListNode;

// 定义双链表
typedef struct DLinkedList {
    DListNode* head;
    DListNode* tail;
    int size;
} DLinkedList;

// 初始化双链表
void DLinkedListInit(DLinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

// 在双链表末尾添加元素
void DLinkedListAdd(DLinkedList* list, int data) {
    DListNode* newNode = (DListNode*)malloc(sizeof(DListNode));
    if (!newNode) {
        printf("内存分配失败！\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = list->tail;
    newNode->next = NULL;

    if (list->tail != NULL) {
        list->tail->next = newNode;
    } else {
        list->head = newNode;
    }
    list->tail = newNode;
    list->size++;
}

// 从双链表中删除指定数据的元素
void DLinkedListRemove(DLinkedList* list, int data) {
    DListNode* current = list->head;

    while (current != NULL && current->data != data) {
        current = current->next;
    }

    if (current == NULL) return; // 没找到

    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        list->head = current->next;
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    } else {
        list->tail = current->prev;
    }

    free(current);
    list->size--;
}

// 打印双链表
void DLinkedListPrint(const DLinkedList* list) {
    DListNode* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 清理双链表
void DLinkedListFree(DLinkedList* list) {
    DListNode* current = list->head;
    while (current != NULL) {
        DListNode* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

int main() {
    DLinkedList list;
    DLinkedListInit(&list);

    int choice, data;

    while (1) {
        printf("\n--- 菜单 ---\n");
        printf("1. 添加数据\n");
        printf("2. 删除指定数据\n");
        printf("3. 打印所有数据\n");
        printf("4. 退出\n");
        printf("请输入数字: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("请输入要添加的数据: ");
                scanf("%d", &data);
                DLinkedListAdd(&list, data);
                break;
            case 2:
                printf("请输入要删除的数据: ");
                scanf("%d", &data);
                DLinkedListRemove(&list, data);
                break;
            case 3:
                printf("打印所有数据: ");
                DLinkedListPrint(&list);
                break;
            case 4:
                DLinkedListFree(&list);
                printf("退出成功\n");
                exit(0);
            default:
                printf("无效的选择!\n");
                break;
        }
    }

    return 0;
}
