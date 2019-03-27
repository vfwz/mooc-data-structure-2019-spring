#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* ϸ���ڴ˲��� */
void Print( List L ); /* ϸ���ڴ˲������������NULL */

List Merge( List L1, List L2 );

int main()
{

    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

List Read() {
    // ��ʼ��ͷ���
    List inList = (List)malloc(sizeof(List));
    PtrToNode curNode,lastNode;
    int num, data, i;
    inList->Data = NULL;
    inList->Next = NULL;
    lastNode = inList;

    scanf("%d", &num);
//    printf("NodeList Size is:%d\n", num);
    for(i=0; i<num;i++) {
        scanf("%d", &data);
        curNode = (PtrToNode)malloc(sizeof(PtrToNode));
        curNode->Next = NULL;
        curNode->Data = data;
        lastNode ->Next = curNode;
        lastNode = curNode;
    }

    return inList;
}

void Print(List L) {
//    printf("Start Print List: \n");
    if(L->Next == NULL) {
        printf("NULL\n");
        return;
    } else {
        while(L->Next) {
            L = L->Next;
            printf("%d ", L->Data);
        }
        printf("\n");
    }
}

/* ��Ĵ��뽫��Ƕ������ */
List Merge(List L1, List L2) {
    List mergeList = (List)malloc(sizeof(List));
    PtrToNode lastNode;
    mergeList->Data = NULL;
    mergeList->Next = NULL;
    lastNode = mergeList;
//    printf("start merge list\n");
    while(L1->Next || L2->Next) {
        if(L1->Next == NULL) { // ���L1����û�н���ˣ�ֱ�ӽ���L2��ʣ����
            lastNode->Next = L2->Next;
            L2->Next = NULL;
            return mergeList;
        }else if(L2->Next == NULL) { // ���L2����û�н���ˣ�ֱ�ӽ���L1��ʣ����
            lastNode->Next = L1->Next;
            L1->Next = NULL;
            return mergeList;
        } else{
            if(L1->Next->Data <= L2->Next->Data) {
                lastNode->Next = L1->Next; // �Ƚ�L1�Ľ��ӵ��ϲ�������
                lastNode = lastNode->Next;
                L1->Next = lastNode->Next; // ��L1�����ͷָ������ƶ��� TODO �˴����޸�ԭ���ֵ�� ��Ҫfree ??
            }else{
                lastNode->Next = L2->Next; // ��L2�Ľ��ӵ��ϲ�������
                lastNode = lastNode->Next;
                L2->Next = lastNode->Next;
            }
        }

    }
    return mergeList;
}
