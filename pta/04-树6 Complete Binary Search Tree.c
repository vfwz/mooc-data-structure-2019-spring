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
* ���������ֵ��������
*/
void insertArr(int arr[], int X, int i) {
    int j, k, tmp, cur;
    if(i == 0) {
        arr[i] = X;
    } else {
        for(j = 0; j < i; j++) {
            if(X >= arr[j]) {
                if(j == i-1) { // ���������һ��Ԫ����Ȼ�����ֵ
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
* ��arr�У���start��ʼ������K���������������ȡ����ȫ�������ĸ�
*/
BinTree rootOfCBT(int arr[], int start, int K) {
    if(K == 0) {
        return NULL; // ����
    } else if(K == 1) {
        return newNode(arr[start]);
    }

    return newNode(arr[start+calcLeftNodes(K)]);
}

/**
* K��Ԫ�ص���ȫ�������� �������Ľ�����
*/
int calcLeftNodes(int K) {
    int mov, remain, leftNodes;
    int level = 0;
    // ����K��Ԫ�����ɵ���ȫ�������Ĳ���

    if(K == 1) {
        return 0;
    }

    mov = K;
    while(mov) {
        level++;
        mov = mov >> 1;
    }
//    printf("K is %d and level is %d\n", K, level);

    // ����K��Ԫ�صĶ������������Ľ����� 2^(level-2) - 1 + min(remain, 2^(level-2))
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
        node = queue[cur]; cur++;// ���Ӳ���
        if(first) { // ��ֹ��ӡ���β���ո�
            printf("%d", node->Data);
            first = 0;
        } else {
            printf(" %d", node->Data);
        }
        if(node->Left) {
            queue[tail++] = node->Left; // ��Ӳ���
        }
        if(node->Right) {
            queue[tail++] = node->Right;  // ��Ӳ���
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
