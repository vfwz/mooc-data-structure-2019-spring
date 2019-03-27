#include <stdio.h>
#include <stdlib.h>

#define YES 1
#define NO 0

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

int isSameTree(BinTree T1, BinTree T2);
BinTree genTree(int N);
BinTree insert(BinTree T, int data);

int main() {
    int N, L;
    BinTree T1, T2;
    int i;

    scanf("%d", &N);
//    printf("序列元素个数：%d\n", N);
    while(N) {
        scanf("%d", &L);
//        printf("待检查序列个数：%d\n", L);
        T1 = genTree(N);
        for(i = 0; i < L; i++) {
            T2 = genTree(N);
            if(isSameTree(T1, T2)) {
                printf("Yes\n");
            } else {
                printf("No\n");
            }
        }
        scanf("%d", &N);
    }
}

BinTree genTree(int N) {
    int i, data;
    BinTree T = NULL;

    for(i = 0; i < N; i++) {
        scanf("%d", &data);
        T = insert(T, data);
    }

    return T;
}

BinTree insert(BinTree T, int data) {
    if(T){
        if(data < T->Data) {
//            printf("向%d的左侧插入结点：%d\n", T->Data, data);
            T->Left = insert(T->Left, data);
        } else {
//            printf("向%d的右侧插入结点：%d\n", T->Data, data);
            T->Right = insert(T->Right, data);
        }
        return T;
    } else {
//        printf("生成一个新的结点：%d\n", data);
        BinTree newNode = (BinTree)malloc(sizeof(struct TNode));
        newNode->Data = data;
        newNode->Left = NULL;
        newNode->Right= NULL;
        return newNode;
    }
}

int isSameTree(BinTree T1, BinTree T2) {
    if(T1&&T2) { // T1, T2均存在
        if(T1->Data != T2->Data) {
            return NO;
        }
        return isSameTree(T1->Left, T2->Left) && isSameTree(T1->Right, T2->Right);
    } else if(!T1 && !T2) {
        return YES;
    } else {
        return NO;
    }
}
