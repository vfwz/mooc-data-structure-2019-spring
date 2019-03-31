#include <stdio.h>
#include <stdlib.h>

typedef struct TNode* BinTree;
struct TNode {
    int Data;
    BinTree Left;
    BinTree Right;
};

int max(int a, int b);
int min(int a, int b);
int powerOfTwo(int power);
void insertArr(int arr[], int X, int i);
BinTree generateCBT(int arr[], int start, int N);
BinTree rootOfCBT(int arr[], int start, int K);
BinTree newNode(int X);
int calcLeftNodes(int K);
void printArr(int arr[], int N);
void levelOrderTraversal(BinTree T, int N);

int main() {
    int N, X, i;
    BinTree T;

    scanf("%d", &N);
    int arr[N];
    for(i = 0; i < N; i++) {
        scanf("%d", &X);
        insertArr(arr, X, i);
    }
//    printArr(arr, N);

    T = generateCBT(arr, 0, N);

    levelOrderTraversal(T, N);

    return 0;
}

void printArr(int arr[], int N) {
    int i;
    for(i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/**
* 增序插入数值到数组中
*/
void insertArr(int arr[], int X, int i) {
    int j, k, tmp, cur;
    if(i == 0) {
        arr[i] = X;
    } else {
        for(j = 0; j < i; j++) {
            if(X >= arr[j]) {
                if(j == i-1) { // 遍历到最后一个元素仍然是最大值
                    arr[i] = X;
                }
                continue;
            } else {
                // put X at j and move numbers after j backwards
                tmp = X;
                for(k = j; k <= i; k++) {
                    cur = arr[k];
                    arr[k] = tmp;
                    tmp = cur;
                }
                break;
            }
        }
    }
}

BinTree generateCBT(int arr[], int start, int N) {
    BinTree T;
    int leftNodes;
    int rightNodes;

    if(N == 0) {
        return NULL;
    }

    leftNodes = calcLeftNodes(N);
    rightNodes = N - leftNodes - 1;
    T = rootOfCBT(arr, start, N);
    T->Left = generateCBT(arr, start, leftNodes);
    T->Right = generateCBT(arr, start+leftNodes+1, rightNodes);

    return T;
}

/**
* 在arr中，从start开始，对于K个已排序的数，获取其完全二叉树的根
*/
BinTree rootOfCBT(int arr[], int start, int K) {
    if(K == 0) {
        return NULL; // 空树
    } else if(K == 1) {
        return newNode(arr[start]);
    }

    return newNode(arr[start+calcLeftNodes(K)]);
}

/**
* K个元素的完全二叉树， 其左树的结点个数
*/
int calcLeftNodes(int K) {
    int mov, remain, leftNodes;
    int level = 0;
    // 计算K个元素生成的完全二叉树的层数

    if(K == 1) {
        return 0;
    }

    mov = K;
    while(mov) {
        level++;
        mov = mov >> 1;
    }
//    printf("K is %d and level is %d\n", K, level);

    // 计算K个元素的二叉树，左树的结点个数 2^(level-2) - 1 + min(remain, 2^(level-2))
    // remain = K - 2^(level-1) + 1
    remain = K - powerOfTwo(level-1) + 1;
//    printf("remain is %d \n", remain);

    leftNodes = powerOfTwo(level-2) - 1 + min(remain, powerOfTwo(level-2));
//    printf("leftNodes is %d \n", leftNodes);

    return leftNodes;
}

BinTree newNode(int X) {
    BinTree node;
    node = (BinTree)malloc(sizeof(struct TNode));
    node->Data = X;
    node->Left = NULL;
    node->Right = NULL;
    return node;
}

void levelOrderTraversal(BinTree T, int N) {
    BinTree queue[N];
    BinTree node;
    int cur, tail, first = 1;

    queue[0] = T;
    cur = 0;
    tail = 1;

    while(cur != tail) {
        node = queue[cur]; cur++;// 出队操作
        if(first) { // 防止打印结果尾部空格
            printf("%d", node->Data);
            first = 0;
        } else {
            printf(" %d", node->Data);
        }
        if(node->Left) {
            queue[tail++] = node->Left; // 入队操作
        }
        if(node->Right) {
            queue[tail++] = node->Right;  // 入队操作
        }
    }


}

int max(int a, int b) {
    return a>b?a:b;
}

int min(int a, int b) {
    return a<b?a:b;
}

int powerOfTwo(int power) {
    return 1 << power;
}
