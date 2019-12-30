#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �ļ��ṹ��
typedef struct File {
    char name[20];
    int size;
    int type;
} File;

// �ļ�����
typedef struct LinkNode {
    File *file;
    struct LinkNode *next; // ͬ��Ŀ¼ָ��
    struct LinkNode *downNext; // �¼�Ŀ¼ָ��
} LinkNode, *LinkList;

// ·��ջ
typedef struct PathStackNode {
    char name[20];
    struct PathStackNode *next;
} PathStackNode, *PathStackList;

// ȫ�ֵ�ǰĿ¼
LinkList currentDir;
// ȫ�ָ�Ŀ¼
LinkList rootLinkList;
// ȫ��·��ջ
PathStackList pathStackList;
// ��Ŀ¼��
char rootPath[] = "C:";

void ShowWelcome();

void Dir(LinkList linkList);

// ��ʼ���ļ�����
LinkList InitLinkList(char name[20]) {
    LinkNode *head = (LinkNode *) malloc(sizeof(LinkNode));
    File *file = (File *) malloc(sizeof(File));
    strcpy(file->name, name);
    head->file = file;
    head->next = NULL;
    head->downNext = NULL;
    return head;
}

// ��ʼ��·��ջ
PathStackList InitPathStack() {
    PathStackNode *head = (PathStackNode *) malloc(sizeof(PathStackNode));
    strcpy(head->name, "head");
    head->next = NULL;
    return head;
}

// ��ջ
void Push(PathStackList pathStackList, char name[20]) {
    while (pathStackList->next) {
        pathStackList = pathStackList->next;
    }
    PathStackNode *newNode = (PathStackNode *) malloc(sizeof(PathStackNode));
    strcpy(newNode->name, name);
    newNode->next = pathStackList->next;
    pathStackList->next = newNode;
}

// ��ջ
void Pop(PathStackList pathStackList) {
    PathStackNode *del;
    PathStackList temp = pathStackList;
    if (temp->next) {
        while (temp->next->next) {
            temp = temp->next;
        }
        del = temp->next;
        temp->next = NULL;
        free(del);
    } else {
        printf("ջΪ��\n ");
    }
}

// ���ջ
void CleanStack(PathStackList pathStackList) {
    free(pathStackList);
    pathStackList = InitPathStack();
}

// ����ȷ��
int GetConfirm(char name[20]) {
    char answer[5];
    memset(answer, 0, sizeof answer);
    printf("\n===========================\n");
    printf(" �Ƿ�ɾ�� %s ? �˲��������棡 \n", name);
    printf("===========================\n");
    printf("ȷ�ϣ� [Y/N]��");
    gets(answer);
    if (strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0) {
        return 1;
    } else {
        return 0;
    }
}

// �ļ������
int Check(char name[20]) {
    int pass = 0;
    LinkList temp = InitLinkList("");
    temp = currentDir;
    while (temp->next) {
        if (!strcmp(temp->next->file->name, name)) {
            pass = 0;
            return pass;
        }
        temp = temp->next;
    }
    pass = 1;
    return pass;
}

// �����ļ���С��Ϣ
void UpdateInfo() {
    int size = 0;
    LinkList temp = InitLinkList("");
    printf("currentDir %s\n", currentDir->file->name);
    temp->next = currentDir->next;
    while (temp) {
        size += temp->file->size;
        temp = temp->next;
    }
    printf("���� %s Ŀ¼��СΪ %d\n", currentDir->file->name, size);
    currentDir->file->size = size;
    printf("currentDir->file->size %d.\n", currentDir->file->size);
}

// �½��ļ�
void MakeFile(LinkList linkList, File *file) {
    if (file != NULL) {
        LinkNode *newNode = (LinkNode *) malloc(sizeof(LinkNode));
        newNode->file = file;
        newNode->next = linkList->next;
        if (newNode->file->type == 0) {
            newNode->downNext = InitLinkList(file->name);
        } else {
            newNode->downNext = InitLinkList("<File>");
        }
        linkList->next = newNode;
    } else {
        return;
    }
}

// ɾ���ļ�
void DeleteFile(char name[20]) {
    LinkList temp = InitLinkList("");
    LinkList delete = InitLinkList("");
    temp = currentDir;
    while (temp->next) {
        if (!strcmp(temp->next->file->name, name)) {
            printf("�ҵ� %s \n", name);
            if (GetConfirm(name)) {
                delete = temp->next;
                temp->next = delete->next;
                free(delete);
                printf("ɾ�����\n");
                return;
            } else {
                printf("�ļ��ѱ���\n");
                return;
            }
        }
        temp = temp->next;
    }
    printf("δ�ҵ� %s\n", name);
}

// �������ļ�
void RenameFile(char name[20]) {
    char newName[20];
    LinkList temp = InitLinkList("");
    temp = currentDir;
    while (temp->next) {
        if (!strcmp(temp->next->file->name, name)) {
            printf("�ҵ� %s \n", name);
            printf("�������µ����ƣ�");
            scanf("%s", newName);
            if (Check(newName) == 1) {
                strcpy(temp->next->file->name, newName);
                printf("%s �����ɹ�.\n", newName);
                return;
            } else {
                printf("���ļ��������ļ�����ͻ��������ʧ��!\n");
                return;
            }
        }
        temp = temp->next;
    }
    printf("δ�ҵ� %s\n", name);
}

// �����ļ���Ϣ
File *GetFile(char name[20], int type) {
    if (Check(name) == 1) {
        int size = 0;
        if (type == 1) {
            // ��������ļ���С
            size = rand() % 200 * (rand() % 100 + rand() % 10 + rand() % 4);
        } else if (type == 0) {
            size = 0;
        }
        File *newFile = (File *) malloc(sizeof(File));
        strcpy(newFile->name, name);
        newFile->size = size;
        newFile->type = type;
        printf("ȡ���ļ���Ϣ %s %d %d\n", newFile->name, newFile->size, newFile->type);
        return newFile;
    } else {
        printf("��Ϊ %s ���ļ��Ѵ���.\n", name);
        return NULL;
    }
}

// ���ظ�Ŀ¼
void GoHome() {
    currentDir = rootLinkList;
    strcpy(currentDir->file->name, rootPath);
    // ���·��ջ
    CleanStack(pathStackList);
    Push(pathStackList, rootPath);
}

// �����ϼ�Ŀ¼
void GoSuper() {
    // ����ջ��Ԫ��
    if (pathStackList->next->next != NULL) {
        Pop(pathStackList);
    } else {
        printf("���Ǹ�Ŀ¼�������ٷ����ϼ�Ŀ¼\n");
    }
}

// �г���ǰĿ¼�ļ�
void Dir(LinkList linkList) {
    LinkList temp = linkList;
    printf("���� \t\t ��С \t\t ���� \n");
    if (temp == NULL) {
        printf("\t\t<û���κ��ļ�>\n");
    } else {
        while (temp) {
            if (temp->file->type == 1) {
                printf("%10s \t %6d \t <File>\n", temp->file->name, temp->file->size);
            } else if (temp->file->type == 0) {
                printf("%10s \t %6d \t <Dir>\n", temp->file->name, temp->file->size);
            } else {
                printf("δ֪�ļ�\n");
            }
            temp = temp->next;
        }
    }
}

// ȡ���б��ļ�����
int GetFileNumber(LinkList linkList) {
    int fileNum = 0;
    LinkList temp = linkList->next;
    if (temp == NULL) {
        printf("\t\t<û���κ��ļ�>\n");
    } else {
        while (temp) {
            fileNum++;
            temp = temp->next;
        }
    }
    printf("�ļ��� %d.\n", fileNum);
    return fileNum;
}

// ��ӡ������ļ�
void ShowSortFileList(File fileList[], int length) {
    int i = 0;
    printf("\n�����\n");
    printf("���� \t\t ��С \t\t ���� \n");
    for (i = 0; i < length; i++) {
        if (fileList[i].type == 1) {
            printf("%10s \t %6d \t <File>\n", fileList[i].name, fileList[i].size);
        } else {
            printf("%10s \t %6d \t <Dir>\n", fileList[i].name, fileList[i].size);
        }
    }
}

// �������� ����
void QuickSortByAsc(File fileList[], int L, int R) {
    int i = L;
    int j = R;
    //֧��
    int pivot = fileList[(L + R) / 2].size;
    //�������˽���ɨ�裬ֻҪ���˻�û�н��棬��һֱɨ��
    while (i <= j) {
        //Ѱ��ֱ����֧������
        while (pivot > fileList[i].size)
            i++;
        //Ѱ��ֱ����֧��С����
        while (pivot < fileList[j].size)
            j--;
        //��ʱ�Ѿ��ֱ��ҵ��˱�֧��С����(�ұ�)����֧������(���)�����ǽ��н���
            if (i <= j) {
                File temp = fileList[i];
                fileList[i] = fileList[j];
                fileList[j] = temp;
                i++;
                j--;
            }
    }
    //����һ��while��֤�˵�һ������֧�����߱�֧��С��֧����ұ߱�֧����ˡ�
    //����ߡ���������ֱ�����ʣ��һ����(�ݹ����)
    if (L < j)
        QuickSortByAsc(fileList, L, j);
    //���ұߡ���������ֱ���ұ�ʣ��һ����(�ݹ����)
    if (i < R)
        QuickSortByAsc(fileList, i, R);
}

// �������� ����
void QuickSortByDesc(File fileList[], int L, int R) {
    int i = L;
    int j = R;
    int pivot = fileList[(L + R) / 2].size;
    while (i <= j) {
        while (pivot < fileList[i].size)
            i++;
        while (pivot > fileList[j].size)
            j--;
        if (i <= j) {
            File temp = fileList[i];
            fileList[i] = fileList[j];
            fileList[j] = temp;
            i++;
            j--;
        }
    }
    if (L < j)
        QuickSortByDesc(fileList, L, j);
    if (i < R)
        QuickSortByDesc(fileList, i, R);
}

// �ļ���С����
void SortFile(LinkList linkList, int type) {
    int i = 0;
    int length = GetFileNumber(linkList);
    File fileList[length];
    if (length == 0) {
        printf("\t\t<û���κ��ļ�>\n");
        return;
    } else {
        LinkList temp = linkList->next;
        while (temp) {
            fileList[i] = *temp->file;
            temp = temp->next;
            i++;
        }
    }
    if (type == 1) {
        QuickSortByAsc(fileList, 0, length-1);
    } else {
        QuickSortByDesc(fileList, 0, length-1);
    }
    ShowSortFileList(fileList, length);
}

// ȡ��Ŀ¼
void GetDir(char name[20]) {
    LinkList temp = InitLinkList("");
    temp = currentDir;
    while (temp->next) {
        if (!strcmp(temp->next->file->name, name)) {
            printf("�ҵ� %s \n", name);
            if (temp->next->file->type == 0) {
                // ѹ��·��ջ
                Push(pathStackList, name);
                printf("�л��� %s Ŀ¼\n", temp->next->file->name);
                strcpy(currentDir->file->name, temp->next->file->name);
                temp->downNext = InitLinkList(name);
                currentDir = temp->downNext;
                return;
            } else {
                printf("%s Ϊ�ļ�\n", temp->next->file->name);
                return;
            }
        }
        temp = temp->next;
    }
    printf("δ�ҵ� %s\n", name);
    return;
}

// ����ʶ��
void ExecuteCommand(char commandLine[10][20]) {
    printf("%s \n", commandLine[0]);
    if (!strcmp(commandLine[0], "exit")) {
        printf("�˳�����.\n");
        exit(0);
    } else if (!strcmp(commandLine[0], "help")) {
        printf("��ʾ�����˵�.\n");
        ShowWelcome();
    } else if (!strcmp(commandLine[0], "cls")) {
        printf("������Ļ.\n");
        system("cls");
    } else if (!strcmp(commandLine[0], "dir")) {
        printf("�г���ǰĿ¼�����ļ�.\n");
        Dir(currentDir->next);
    } else if (!strcmp(commandLine[0], "mk")) {
        printf("�½��ļ�.\n");
        if (commandLine[1] != NULL) {
            if (strlen(commandLine[1]) == 0) {
                printf("��������ȷ������㲻֪���÷������ help �˽⡣\n");
                return;
            } else {
                MakeFile(currentDir, GetFile(commandLine[1], 1));
            }
        } else {
            return;
        }
    } else if (!strcmp(commandLine[0], "mkdir")) {
        printf("�½��ļ���.\n");
        if (commandLine[1] != NULL) {
            if (strlen(commandLine[1]) == 0) {
                printf("��������ȷ������㲻֪���÷������ help �˽⡣\n");
                return;
            } else {
                MakeFile(currentDir, GetFile(commandLine[1], 0));
            }
        } else {
            return;
        }
    } else if (!strcmp(commandLine[0], "cd")) {
        printf("Ŀ¼����.\n");
        if (commandLine[1] != NULL) {
            if (strlen(commandLine[1]) == 0) {
                printf("��������ȷ������㲻֪���÷������ help �˽⡣\n");
                return;
            } else if (!strcmp(commandLine[1], "..")) {
                printf("�����ϲ�Ŀ¼.\n");
                GoSuper();
            } else if (!strcmp(commandLine[1], "/")) {
                printf("���ظ�Ŀ¼.\n");
                GoHome();
            } else {
                printf("�� %s \n", commandLine[1]);
                GetDir(commandLine[1]);
            }
        } else {
            return;
        }
    } else if (!strcmp(commandLine[0], "del")) {
        printf("ɾ���ļ�����.\n");
        if (commandLine[1] != NULL) {
            if (strlen(commandLine[1]) == 0) {
                printf("��������ȷ������㲻֪���÷������ help �˽⡣\n");
                return;
            } else {
                printf("ɾ�� %s \n", commandLine[1]);
                DeleteFile(commandLine[1]);
            }
        } else {
            return;
        }
    } else if (!strcmp(commandLine[0], "rename")) {
        printf("�������ļ�����.\n");
        if (commandLine[1] != NULL) {
            if (strlen(commandLine[1]) == 0) {
                printf("��������ȷ������㲻֪���÷������ help �˽⡣\n");
                return;
            } else {
                printf("������ %s \n", commandLine[1]);
                RenameFile(commandLine[1]);
            }
        } else {
            return;
        }
    } else if (!strcmp(commandLine[0], "desc")) {
        printf("��������\n");
        SortFile(currentDir, 0);
    } else if (!strcmp(commandLine[0], "asc")) {
        printf("��������\n");
        SortFile(currentDir, 1);
    }
}

// �Զ�����Ŀ¼�ļ�
void AutoGenterateFile() {
    MakeFile(currentDir, GetFile("Music", 0));
    MakeFile(currentDir, GetFile("eclipse.exe", 1));
    MakeFile(currentDir, GetFile("User", 0));
    MakeFile(currentDir, GetFile("main.exe", 1));
    MakeFile(currentDir, GetFile("regedit.exe", 1));
    MakeFile(currentDir, GetFile("EFI", 0));
    MakeFile(currentDir, GetFile("setupact.log", 1));
    MakeFile(currentDir, GetFile("Windows", 0));
    MakeFile(currentDir, GetFile("winhlp32.exe", 1));
    MakeFile(currentDir, GetFile("ProgramData", 0));
    MakeFile(currentDir, GetFile("whois.exe", 1));
    MakeFile(currentDir, GetFile("system.ini", 1));
    MakeFile(currentDir, GetFile("Document", 0));
    GetDir("User");
    printf("AutoGenterateFile(). \n");
    Dir(currentDir);
    MakeFile(currentDir, GetFile("john", 0));
    MakeFile(currentDir, GetFile("config.con", 1));
    MakeFile(currentDir, GetFile("phl", 0));
//    UpdateInfo();
    GoHome();
}

// ��ʾ·��
void ShowPath(PathStackList pathStackList) {
    PathStackList temp = pathStackList->next;
    while(temp) {
        printf("%s/", temp->name);
        temp = temp->next;
    }
    printf(" > ");
}

// ��ʾ�����˵�
void ShowWelcome() {
    system("cls");
    printf("Simulate Explorer [�汾 V1.00]\n");
    printf("(c) 2019 Personal Development����������Ȩ����\n");
    printf("\n[�÷���]\n");
    printf("cd \t\t ��Ŀ¼(/��ʾ��Ŀ¼ | ..��ʾ�ϲ�Ŀ¼)\n");
    printf("dir \t\t �г���ǰĿ¼�ļ�\n");
    printf("mk \t\t �½��ļ�\n");
    printf("mkdir \t\t �½��ļ���\n");
    printf("del \t\t ɾ���ļ�\n");
    printf("rename \t\t �������ļ�\n");
    printf("desc \t\t ���������ļ�\n");
    printf("asc \t\t ���������ļ�\n");
    printf("cls \t\t ������Ļ��Ϣ\n");
    printf("exit \t\t �˳�����\n");
    printf("help \t\t ��ʾ�˰����˵�\n\n");
}

// ����������
void ShowCommandLine() {
    char commandLine[30];
    char parameter[10][20];
    char spilt[] = " ";
    ShowWelcome();
    while (1) {
        int i = 0;
        // ��ӡ��ǰ·��
        ShowPath(pathStackList);
        // �ȴ��û�����
        gets(commandLine);
        // ���������ַ��ָ�
        char *result = NULL;
        result = strtok(commandLine, spilt);
        while (result != NULL) {
            strcpy(parameter[i], result);
            result = strtok(NULL, spilt);
            i++;
        }
        // ִ������
        ExecuteCommand(parameter);
        // �����������
        memset(parameter, 0, sizeof parameter);
        memset(commandLine, 0, sizeof commandLine);
        printf("\n");
    }
}

// ����
void test() {

}

// ������
int main() {
    LinkList linkList = InitLinkList(rootPath);
    pathStackList = InitPathStack();
    Push(pathStackList, rootPath);
    rootLinkList = linkList;
    currentDir = linkList;
    AutoGenterateFile();
    ShowCommandLine();
    return 0;
}
