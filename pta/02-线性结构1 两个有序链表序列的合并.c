#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表；空链表将输出NULL */

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
    // 初始化头结点
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

/* 你的代码将被嵌在这里 */
List Merge(List L1, List L2) {
    List mergeList = (List)malloc(sizeof(List));
    PtrToNode lastNode;
    mergeList->Data = NULL;
    mergeList->Next = NULL;
    lastNode = mergeList;
//    printf("start merge list\n");
    while(L1->Next || L2->Next) {
        if(L1->Next == NULL) { // 如果L1后面没有结点了，直接接上L2的剩余结点
            lastNode->Next = L2->Next;
            L2->Next = NULL;
            return mergeList;
        }else if(L2->Next == NULL) { // 如果L2后面没有结点了，直接接上L1的剩余结点
            lastNode->Next = L1->Next;
            L1->Next = NULL;
            return mergeList;
        } else{
            if(L1->Next->Data <= L2->Next->Data) {
                lastNode->Next = L1->Next; // 先将L1的结点接到合并链表上
                lastNode = lastNode->Next;
                L1->Next = lastNode->Next; // 将L1链表的头指针向后移动， TODO 此处会修改原表的值， 需要free ??
            }else{
                lastNode->Next = L2->Next; // 将L2的结点接到合并链表上
                lastNode = lastNode->Next;
                L2->Next = lastNode->Next;
            }
        }

    }
    return mergeList;
}
