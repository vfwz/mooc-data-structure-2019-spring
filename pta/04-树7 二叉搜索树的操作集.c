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

void PreorderTraversal( BinTree BT ); /* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal( BinTree BT );  /* 中序遍历，由裁判实现，细节不表 */

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

/* 先序遍历，由裁判实现，细节不表 */
void PreorderTraversal( BinTree BT ) {
    if(BT) {
        printf(" %d", BT->Data);
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    }
}

/* 中序遍历，由裁判实现，细节不表 */
void InorderTraversal( BinTree BT ) {
    if(BT) {
        InorderTraversal(BT->Left);
        printf(" %d", BT->Data);
        InorderTraversal(BT->Right);
    }
}

/* 你的代码将被嵌在这里 */

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
            if(!BST->Left && !BST->Right) { // 被删除结点没有子结点，直接删除
                free(BST);
                BST = NULL;
            } else if(!BST->Left || !BST->Right) { // 被删除结点没有左结点，将右结点移动到删除结点位置
                tmp = BST->Left?BST->Left:BST->Right;
                BST->Data = tmp->Data;
                BST->Left = tmp->Left;
                BST->Right = tmp->Right;
                free(tmp);
            } else { // 被删除结点存在左右孩子结点，将左结点移动到右结点树的最小结点上，由结点替换被删除结点位置
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
    // 由于非递归函数的执行效率高，可将“尾递归”函数改为迭代函数
    BinTree result = NULL;
    while(BST) {
        result = BST;
        BST = BST->Right;
    }
    return result;
}
