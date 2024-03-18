#include <stdio.h>
#include <stdlib.h>

// 定义链表节点
typedef struct ListNode {
    int data;
    struct ListNode* next;
} ListNode;

// 定义链表
typedef struct LinkedList {
    ListNode* head;
    int size;
} LinkedList;

// 初始化链表
void LinkedListInit(LinkedList* list) {
    list->head = NULL;
    list->size = 0;
}

// 在链表末尾添加元素
void LinkedListAdd(LinkedList* list, int data) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (!newNode) {
        printf("内存分配失败！\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        ListNode* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
}

// 从链表中删除指定数据的元素
void LinkedListRemove(LinkedList* list, int data) {
    if (list->head == NULL) return;

    ListNode* current = list->head;
    ListNode* prev = NULL;

    while (current != NULL && current->data != data) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) return; // 没找到

    if (prev == NULL) {
        list->head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    list->size--;
}

// 打印链表
void LinkedListPrint(const LinkedList* list) {
    ListNode* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 清理链表内存
void LinkedListFree(LinkedList* list) {
    ListNode* current = list->head;
    while (current != NULL) {
        ListNode* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->size = 0;
}


int main() {
    LinkedList list;
    LinkedListInit(&list);

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
                LinkedListAdd(&list, data);
                break;
            case 2:
                printf("请输入要删除的数据: ");
                scanf("%d", &data);
                LinkedListRemove(&list, data);
                break;
            case 3:
                printf("打印所有数据: ");
                LinkedListPrint(&list);
                break;
            case 4:
                LinkedListFree(&list);
                printf("退出成功\n");
                exit(0);
            default:
                printf("无效的选择!\n");
                break;
        }
    }

    return 0;
}
