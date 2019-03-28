#include <stdio.h>
#include <stdlib.h>

/*
Note: 此解法比较暴力难懂，
正统解法RR和LL做单旋转操作，RL、LR操作应该拆分为两次单旋转操作
*/

typedef struct TNode *BinTree;
struct TNode {
    int Data;
    BinTree Left;
    BinTree Right;
};

BinTree Insert(BinTree T, int X);
int CalcBalanceFactor(BinTree T);
int GetHeight(BinTree T);

int main() {
    int N, X, i;
    BinTree T = NULL;

    scanf("%d", &N);
    for(i = 0; i < N; i++) {
        scanf("%d", &X);
        T = Insert(T, X);
    }

    printf("%d\n", T->Data); // 打印根结点的值

    return 0;
}

BinTree Insert(BinTree T, int X) {
    int balanceFactor, branch;
    int HL, HR;
    int tmp;
    BinTree tmpNode, handleNode;
    if(T) {
        if(X < T->Data) {
            T->Left = Insert(T->Left, X);
            branch = 0;
        } else {
            T->Right = Insert(T->Right, X);
            branch = 1;
        }
        balanceFactor = CalcBalanceFactor(T);
        if(balanceFactor > 1) { // 发现不平衡的结点
            if(branch) {// R
                HL = GetHeight(T->Right->Left);
                HR = GetHeight(T->Right->Right);
                if(HL > HR) { // L 新的结点在左子树上
//                    printf("RL Rotation\n");
                    tmpNode = T->Left;

                    handleNode = T->Right->Left; // 麻烦结点
                    T->Right->Left = handleNode->Right; // 这个是新增的结点
                    T->Left = handleNode;
                    handleNode->Right = handleNode->Left;
                    handleNode->Left = tmpNode;

                    tmp = T->Data;
                    T->Data = handleNode->Data;
                    handleNode->Data = tmp;
                } else { // R 新的结点在右子树上
//                    printf("RR Rotation\n");
                    handleNode = T->Right;
                    T->Right = handleNode->Left;
                    handleNode->Left = T;

                    T = handleNode; // 重置头结点

                }
            } else {  // L
                HL = GetHeight(T->Left->Left);
                HR = GetHeight(T->Left->Right);
                if(HL > HR) { // L 新的结点在左子树上
//                    printf("LL Rotation\n");
                    handleNode = T->Left;
                    T->Left = handleNode->Right;
                    handleNode->Right = T;

                    T = handleNode; // 重置头结点

                } else { // R 新的结点在右子树上
//                    printf("LR Rotation\n");
                    tmpNode = T->Right;

                    handleNode = T->Left->Right; // 麻烦结点
                    T->Left->Right = handleNode->Left; // 这个是新增的结点
                    T->Right = handleNode;
                    handleNode->Left = handleNode->Right;
                    handleNode->Right = tmpNode;

                    tmp = T->Data;
                    T->Data = handleNode->Data;
                    handleNode->Data = tmp;
                }
            }
        }


    } else {
        BinTree newNode = (BinTree)malloc(sizeof(struct TNode));
        newNode->Data = X;
        newNode->Left = NULL;
        newNode->Right= NULL;
        T = newNode;
    }
    return T;
}


// 返回平衡因子绝对值
int CalcBalanceFactor(BinTree T) {
    int HL, HR;
    if(T) {
        HL = GetHeight(T->Left);
        HR = GetHeight(T->Right);
    } else {
        return 0;
    }
    return HL>HR?HL-HR:HR-HL;
}

int GetHeight(BinTree T) {
    int HL, HR;
    int height = 0;
    if(T) {
        HL = GetHeight(T->Left);
        HR = GetHeight(T->Right);
        height = HL>HR?HL+1:HR+1;
    }
    return height;
}

