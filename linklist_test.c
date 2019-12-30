#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �ļ�����
typedef struct LinkNode {
    char name[20];
    struct LinkNode *next; // ͬ��Ŀ¼ָ��
    struct LinkNode *downNext; // �¼�Ŀ¼ָ��
} LinkNode, *LinkList;

LinkList currentDir;
LinkList rootDir;

LinkList Init() {
    LinkNode *head = (LinkNode *) malloc(sizeof(LinkNode));
    strcpy(head->name, "root");
    head->next = NULL;
    head->downNext = NULL;
    return head;
}

void Display(LinkList linkList) {
    printf("\n");
    if (linkList != NULL) {
        while (linkList) {
            printf("%s ", linkList->name);
            linkList = linkList->next;
        }
    } else {
        printf("<û���κ�����>");
    }
    printf("\n");
}

void CreateNext(LinkList linkList, char name[20]) {
    while(linkList->next) {
        linkList = linkList->next;
    }
    LinkNode *newNode = (LinkNode *) malloc(sizeof(LinkNode));
    strcpy(newNode->name, name);
    newNode->next = linkList->next;
    newNode->downNext = NULL;
    linkList->next = newNode;
}

void CreateDownNext(LinkList linkList, char name[20]) {
    LinkNode *head = (LinkNode *) malloc(sizeof(LinkNode));
    LinkNode *temp = (LinkNode *) malloc(sizeof(LinkNode));
    strcpy(head->name, "head");
    head->downNext = NULL;
    head->next = NULL;

    strcpy(temp->name, name);
    temp->next = head;
    temp->downNext = linkList->downNext;
    linkList->downNext = temp;
}

void GetDir(char name[20]) {
    LinkList temp = Init();
    temp->downNext = Init();
    temp->next = currentDir;
    printf("\nGetDir(%s)\n", name);
    Display(temp);
    while (temp->next) {
        if (!strcmp(temp->next->name, name)) {
            printf("\n�ҵ� %s �ļ�\n", name);
            printf(" -%s- \n ", temp->name);
            currentDir = temp->downNext;
            return;
        }
        temp = temp->next;
    }
    printf("\nδ�ҵ�\n");
    return;
}

int main() {
    LinkList linkList = Init();
    currentDir = linkList;
    rootDir = linkList;
    printf("�����¼�Ŀ¼\n");
    CreateDownNext(currentDir, "main");
//    Display(currentDir->downNext);
    printf("�л���ǰĿ¼ downNext\n");
    currentDir = rootDir->downNext;
    printf("�����ļ�\n");
    CreateNext(currentDir, "sub");
    CreateNext(currentDir, "testsub");
    CreateNext(currentDir, "666666");
    printf("��ӡ��ǰĿ¼\n");
    Display(currentDir->next);
    GetDir("666666");
    printf("switch 66666\n");
//    CreateNext(currentDir, "666");
    Display(currentDir);
    return 0;
}