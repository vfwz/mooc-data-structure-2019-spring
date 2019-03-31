#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode {
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal( BinTree BT ); /* ����������ɲ���ʵ�֣�ϸ�ڲ��� */
void InorderTraversal( BinTree BT );  /* ����������ɲ���ʵ�֣�ϸ�ڲ��� */

BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );

int main() {
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for ( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:");
    PreorderTraversal(BST);
    printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL)
            printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp==MinP)
                printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp==MaxP)
                printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:");
    InorderTraversal(BST);
    printf("\n");

    return 0;
}

/* ����������ɲ���ʵ�֣�ϸ�ڲ��� */
void PreorderTraversal( BinTree BT ) {
    if(BT) {
        printf(" %d", BT->Data);
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    }
}

/* ����������ɲ���ʵ�֣�ϸ�ڲ��� */
void InorderTraversal( BinTree BT ) {
    if(BT) {
        InorderTraversal(BT->Left);
        printf(" %d", BT->Data);
        InorderTraversal(BT->Right);
    }
}

/* ��Ĵ��뽫��Ƕ������ */

BinTree Insert( BinTree BST, ElementType X ) {
    if(BST) {
        if(X < BST->Data) {
            BST->Left = Insert(BST->Left, X);
        } else {
            BST->Right = Insert(BST->Right, X);
        }
        return BST;
    } else {
        BinTree newNode = (BinTree) malloc(sizeof(struct TNode));
        newNode->Data = X;
        newNode->Left = NULL;
        newNode->Right = NULL;
        return newNode;
    }
}

BinTree Delete( BinTree BST, ElementType X ) {
    BinTree tmp;
    if(BST) {
        if(BST->Data == X) {
            if(!BST->Left && !BST->Right) { // ��ɾ�����û���ӽ�㣬ֱ��ɾ��
                free(BST);
                BST = NULL;
            } else if(!BST->Left || !BST->Right) { // ��ɾ�����û�����㣬���ҽ���ƶ���ɾ�����λ��
                tmp = BST->Left?BST->Left:BST->Right;
                BST->Data = tmp->Data;
                BST->Left = tmp->Left;
                BST->Right = tmp->Right;
                free(tmp);
            } else { // ��ɾ�����������Һ��ӽ�㣬�������ƶ����ҽ��������С����ϣ��ɽ���滻��ɾ�����λ��
                tmp = FindMin(BST->Right);
                tmp->Left = BST->Left;

                tmp = BST->Right;
                BST->Data = tmp->Data;
                BST->Left = tmp->Left;
                BST->Right = tmp->Right;
                free(tmp);
            }
        } else if(BST->Data > X) {
            BST->Left = Delete(BST->Left, X);
        } else {
            BST->Right = Delete(BST->Right, X);
        }
        return BST;
    } else {
        printf("Not Found\n");
        return BST;
    }
}

Position Find( BinTree BST, ElementType X ) {
    if(BST) {
        if(X == BST->Data) {
            return BST;
        } else if(X < BST->Data) {
            return Find(BST->Left, X);
        } else {
            return Find(BST->Right, X);
        }
    } else {
        return NULL;
    }
}
Position FindMin( BinTree BST ) {
    if(BST) {
        if(BST->Left) {
            return FindMin(BST->Left);
        } else {
            return BST;
        }
    } else {
        return NULL;
    }
}
Position FindMax( BinTree BST ) {
    /*
    if(BST) {
        if(BST->Right) {
            return FindMax(BST->Right);
        } else {
            return BST;
        }
    } else {
        return NULL;
    }
    */
    // ���ڷǵݹ麯����ִ��Ч�ʸߣ��ɽ���β�ݹ顱������Ϊ��������
    BinTree result = NULL;
    while(BST) {
        result = BST;
        BST = BST->Right;
    }
    return result;
}
