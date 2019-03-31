#include <stdio.h>
#include <stdlib.h>

/*
Note: �˽ⷨ�Ƚϱ����Ѷ���
��ͳ�ⷨRR��LL������ת������RL��LR����Ӧ�ò��Ϊ���ε���ת����
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

    printf("%d\n", T->Data); // ��ӡ������ֵ

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
        if(balanceFactor > 1) { // ���ֲ�ƽ��Ľ��
            if(branch) {// R
                HL = GetHeight(T->Right->Left);
                HR = GetHeight(T->Right->Right);
                if(HL > HR) { // L �µĽ������������
//                    printf("RL Rotation\n");
                    tmpNode = T->Left;

                    handleNode = T->Right->Left; // �鷳���
                    T->Right->Left = handleNode->Right; // ����������Ľ��
                    T->Left = handleNode;
                    handleNode->Right = handleNode->Left;
                    handleNode->Left = tmpNode;

                    tmp = T->Data;
                    T->Data = handleNode->Data;
                    handleNode->Data = tmp;
                } else { // R �µĽ������������
//                    printf("RR Rotation\n");
                    handleNode = T->Right;
                    T->Right = handleNode->Left;
                    handleNode->Left = T;

                    T = handleNode; // ����ͷ���

                }
            } else {  // L
                HL = GetHeight(T->Left->Left);
                HR = GetHeight(T->Left->Right);
                if(HL > HR) { // L �µĽ������������
//                    printf("LL Rotation\n");
                    handleNode = T->Left;
                    T->Left = handleNode->Right;
                    handleNode->Right = T;

                    T = handleNode; // ����ͷ���

                } else { // R �µĽ������������
//                    printf("LR Rotation\n");
                    tmpNode = T->Right;

                    handleNode = T->Left->Right; // �鷳���
                    T->Left->Right = handleNode->Left; // ����������Ľ��
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


// ����ƽ�����Ӿ���ֵ
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

