#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �ļ�����
typedef struct LinkNode {
    char name[20];
    struct LinkNode *next; // ͬ��Ŀ¼ָ��
    struct LinkNode *downNext; // �¼�Ŀ¼ָ��
} LinkNode, *LinkList;
// ����ջ
typedef struct LinkStack {
    LinkList link;
    struct LinkStack *next;
} LinkStack, *LinkStackList;

LinkStackList linkStackList;
LinkList currentDir;

LinkStack *InitStack() {
    LinkStack *head = (LinkStack *) malloc(sizeof(LinkStack));
    head->link = NULL;
    head->next = NULL;
    return head;
}

void Push(LinkStackList linkStackList, LinkList linkList) {
    while (linkStackList->next) {
        linkStackList = linkStackList->next;
    }
    LinkStack *newLink = (LinkStack *) malloc(sizeof(LinkStack));
    newLink->link = linkList;
    newLink->next = linkStackList->next;
    linkStackList->next = newLink;
}

LinkList Pop(LinkStackList linkStackList) {
    LinkStackList out;
    LinkStackList temp = linkStackList;
    if (temp->next) {
        while (temp->next->next) {
            temp = temp->next;
        }
        out = temp->next;
        temp->next = NULL;
        return out->link;
    } else {
        printf("ջΪ��");
        return NULL;
    }
}

void Travel(LinkStackList stack) {
    printf("\nTravel Stack\n");
    while (stack->next) {
        stack = stack->next;
        printf("%s ", stack->link->name);
    }
    printf("\n");
}

LinkList GetTop(LinkStackList stack) {
    if (stack->next) {
        while (stack->next) {
            stack = stack->next;
        }
        return stack->link;
    } else {
        printf("ջ��Ԫ��Ϊ��");
        return NULL;
    }
}

LinkNode *InitLinkList(char name[]) {
    LinkNode *head = (LinkNode *) malloc(sizeof(LinkNode));
    LinkNode *downHead = (LinkNode *) malloc(sizeof(LinkNode));
    strcpy(head->name, name);
    strcpy(downHead->name, name);
    downHead->next = NULL;
    downHead->downNext = NULL;
    head->next = NULL;
    head->downNext = downHead;
}

void GetDir(LinkList linkList, char name[]) {
    LinkList temp = linkList->downNext->next;
    printf("GetDir(LinkList linkList, char name[])\n");
    while (temp) {
        printf("%s ", temp->name);
        if (!strcmp(temp->name, name)) {
            printf("�ҵ� %s ", name);
            Push(linkStackList, temp);
            currentDir = temp;
            return;
        }
        temp = temp->next;
    }
    printf("δ�ҵ� %s", name);
    return;
}

void Create(LinkList linkList, char name[]) {
    LinkNode *newNode = InitLinkList(name);
    strcpy(newNode->name, name);
    newNode->next = linkList->downNext->next;
    linkList->downNext->next = newNode;
}

void FindDir(LinkList linkList, char name[]) {
    LinkList temp = linkList->downNext->next;
    while (temp) {
        printf("%s ", temp->name);
        if (!strcmp(temp->name, name)) {
            printf("�ҵ� %s ", name);
            return;
        }
        temp = temp->next;
    }
    printf("δ�ҵ� %s", name);
    return;
}

void Show(LinkList linkList) {
    LinkList temp = linkList->downNext->next;
    if (temp) {
        while (temp) {
            printf("%s ", temp->name);
            temp = temp->next;
        }
    } else {
        printf("���κ��ļ�");
    }
}

int main() {
    LinkList linkList = InitLinkList("root");
    currentDir = linkList;
    linkStackList = InitStack();
    LinkStackList watch = linkStackList;
    Push(linkStackList, linkList);
    Create(currentDir, "phl");
    Create(currentDir, "fyl");
    GetDir(currentDir,"phl");
    Create(currentDir, "main.exe");
    Create(currentDir, "demo.cdp");
    Create(currentDir, "Music");
    GetDir(currentDir,"Music");
    Create(currentDir, "CXK");
    Create(currentDir, "SHE");
    Create(currentDir, "EXO");
    Travel(linkStackList);
    printf("Show(currentDir)");
    currentDir = Pop(linkStackList);
    currentDir = Pop(linkStackList);
    currentDir = Pop(linkStackList);
    LinkList temp = currentDir;
    Show(currentDir);
    Travel(linkStackList);
    GetDir(currentDir, "phl");
    Travel(linkStackList);
    Show(currentDir);
    GetDir(currentDir, "Music");
    Show(currentDir);
    Travel(linkStackList);
    return 0;
}
