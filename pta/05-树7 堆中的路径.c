#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct HNode *Heap; /* 堆的类型定义 */
struct HNode {
    ElementType *Data; /* 存储元素的数组 */
    int Size;          /* 堆中当前元素个数 */
    int Capacity;      /* 堆的最大容量 */
};
typedef Heap MinHeap; /* 最小堆 */

#define MINDATA -10001  /* 该值应根据具体情况定义为小于堆中所有可能元素的值 */

void insert(Heap h, ElementType e);
void printRoute(Heap h, int sub);

int main() {
    int N, M, i, X, sub;
    MinHeap h;

    scanf("%d %d", &N, &M);

    // 初始化堆
    h = (MinHeap)malloc(sizeof(struct HNode));
    h->Data = (ElementType*)malloc((N+1)*sizeof(ElementType));
    h->Data[0] = MINDATA;
    h->Size = 0;
    h->Capacity = N;

    for(i = 0; i < N; i++) {
        scanf("%d", &X);
        insert(h, X);
    }

    for(i = 0; i < M; i++) {
        scanf("%d", &sub);
        printRoute(h, sub);
    }

    return 0;
}

void insert(Heap h, ElementType X) {
    int i;

    i = ++h->Size;
    for(; h->Data[i/2] > X; i/=2) {
        h->Data[i] = h->Data[i/2];
    }
    h->Data[i] = X;
}

void printRoute(Heap h, int sub) {
    int i;
    for(i = sub; i > 0; i/=2) {
        if(i == sub) {
            printf("%d", h->Data[i]);
        } else {
            printf(" %d", h->Data[i]);
        }
    }
    printf("\n");
}
