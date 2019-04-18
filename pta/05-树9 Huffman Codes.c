#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 64
#define MIN_FRQ 0
#define NONE -1

typedef struct HNode* MinHeap;
typedef struct TNode* Node;
typedef struct TNode* HufTree;

// 定义最小堆
struct HNode {
    Node Data[MAX_SIZE];
    int Size;
};
// 定义哈夫曼树
struct TNode {
    int Character; // 字符ASCII码
    int Frequency; // 字频
    Node Left;
    Node Right;
};

int insertHeap(MinHeap heap, Node node);
HufTree genHufTreeFromHeap(MinHeap heap);
Node popMin(MinHeap heap);
Node combineNode(Node nodeA, Node nodeB);
Node newNode(int ch, int fq);
int calcWPLOfHTree(HufTree hTree, char* code, int deepth);
void printHeap(MinHeap heap);
int checkCode(HufTree sTree, int ch, char* code);
int checkCode2(HufTree sTree, int ch, char* code);
void freeTree(HufTree T);

void printTree(HufTree T) {
    if(T) {
        printf("Ch is %c, Flg is %d\n", T->Character, T->Frequency);
        printTree(T->Left);
        printTree(T->Right);
    }
}

int main() {
    int N, M;
    char ch; // character
    int fq, freq[128];  // frequency, freq数组保存字符频率

    int i, j, cost, sCost, flag = 1;

    char code[200];

    MinHeap heap;
    HufTree hTree, sTree;

    // 初始化一个最小堆
    heap = (MinHeap)malloc(sizeof(struct HNode));
    heap->Size = 0;
    heap->Data[0] = newNode(NONE, MIN_FRQ);

    // 将输入的字符数据根据频率插入到最小堆中
    scanf("%d", &N);
//    printf("N is %d\n", N);
    for(i = 0; i < N; i++) {
        scanf(" %c %d", &ch, &fq);
        freq[ch] = fq;
        insertHeap(heap, newNode(ch, fq));
//        printf("insert success %c %d\n", ch, fq);
    }

//    printHeap(heap);

    // 根据最小堆构建哈夫曼树
    hTree = genHufTreeFromHeap(heap);
    cost = calcWPLOfHTree(hTree, code, 0); // 哈夫曼编码总位数

//    printf("cost is %d\n", cost);

    scanf("%d", &M);
    for(i = 0; i < M; i++) {
        sTree = newNode(NONE, 0);
        sCost = 0;

        for(j = 0; j < N; j++) {
            scanf(" %c", &ch);
            scanf(" %s", code);
//            printf("student input [%c:%s]\n", ch, code);
            flag = flag?checkCode2(sTree, ch, code):flag;
            sCost += strlen(code) * freq[ch];
        }
        if(flag && cost == sCost) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }

        // 进行下一组检测，恢复初始化值，flag忘了恢复 ORZ, 调试了很久......
        freeTree(sTree);
        flag = 1;
    }

    freeTree(hTree);

    return 0;
}

int checkCode(HufTree sTree,  int ch, char* code) {

    int i;
    Node node, curNode = sTree;

    for(i = 0; i < strlen(code); i++) {
//        printf("%c,", code[i]);
        if('0' == code[i]) {
            node = curNode->Left?curNode->Left:newNode(NONE, 0);
            curNode->Left = node;
        } else { // if('1' == code[i])
            node = curNode->Right?curNode->Right:newNode(NONE, 0);
            curNode->Right = node;
        }

        if(node->Frequency  == 1) {// 结点已被占用
//            printf("node is already used by [%c, %d]\n", node ->Character, node->Frequency);
            return 0;
        }

        curNode = node;

    }

    if(curNode->Left || curNode->Right) {// 编码结束，但编码结点还有子结点
//                printf("node still has child\n");
        return 0;
    }

    curNode->Character = ch;
    curNode->Frequency = 1; // 标识当前结点已被使用

    return 1;

//    printf("\n");
}

int checkCode2(HufTree sTree, int ch, char* code) {
    int i, flag = 0;
    Node node, curNode = sTree;

    for(i = 0; code[i] != '\0'; i++) {
//        printf("%c,", code[i]);
        if('0' == code[i]) {
            node = curNode->Left;
            if(!node) {
                node = newNode(NONE, 0); // 新建了结点，一定不是前缀
                curNode->Left = node;
                flag = 1;
            }
        } else { //  if('1' == code[i])
            node = curNode->Right;
            if(!node) {
                node = newNode(NONE, 0); // 新建了结点，一定不是前缀
                curNode->Right = node;
                flag = 1;
            }
        }
        curNode = node;
    }
    return flag;

//    printf("\n");
}

// 将字符ASCII码与频率值插入到最小堆中
int insertHeap(MinHeap heap, Node node) {
    int i;
    i = ++heap->Size;

    for(; heap->Data[i/2]->Frequency > node->Frequency; i /= 2) {
        heap->Data[i] = heap->Data[i/2];
    }
    heap->Data[i] = node;
}

HufTree genHufTreeFromHeap(MinHeap heap) {
    Node nodeA, nodeB, nodeP;

    while(heap->Size > 1) {
        // 从堆中取出最小频率的两个结点，合并为一个结点再插入到堆中
        nodeA = popMin(heap);
        nodeB = popMin(heap);
        nodeP = combineNode(nodeA, nodeB);
        insertHeap(heap, nodeP);
    }
    return popMin(heap);
}

int calcWPLOfHTree(HufTree hTree, char* code, int deepth) {
    int subCost = 0;
    if(hTree->Left) {
        code[deepth] = '0';
        subCost += calcWPLOfHTree(hTree->Left, code, deepth+1);
    }
    if(hTree->Right) {
        code[deepth] = '1';
        subCost += calcWPLOfHTree(hTree->Right, code, deepth+1);
    }
    if(!hTree->Left && !hTree->Right) { // 叶结点
        code[deepth] = '\0';
        subCost += hTree->Frequency * deepth;
//        printf("[%c,%d], deepth is %d, code is %s\n", hTree->Character,hTree->Frequency, deepth, code);
    }

    return subCost;

}

Node popMin(MinHeap heap) {
    Node minNode, tmpNode;
    int i, j;

    minNode = heap->Data[1]; // 堆的第一个结点为最小结点

    // 删除第一个结点， 取最后一个结点到首结点，然后从首结点开始调整整个堆
    heap->Data[1] = heap->Data[heap->Size];
    --heap->Size;

    for(i = 1; i*2 <= heap->Size; ) {
        j = i*2;
        if(j+1 <= heap->Size && heap->Data[j+1]->Frequency < heap->Data[j]->Frequency) { // 右结点的值小， 取右结点
            j++;
        }
        if(heap->Data[i]->Frequency > heap->Data[j]->Frequency) { // 父结点大于子结点
            // 父节点与最小值的结点互换
            tmpNode = heap->Data[i];
            heap->Data[i] = heap->Data[j];
            heap->Data[j] = tmpNode;
            i = j; // 继续遍历
        } else {
            break; // 父结点已经是最小结点
        }
    }
//    printf("pop [%c,%d]\n", minNode->Character, minNode->Frequency);

    return minNode;

}

Node combineNode(Node nodeA, Node nodeB) {
    Node nodeP;
    nodeP = newNode(NONE, nodeA->Frequency + nodeB->Frequency);
    nodeP->Left = nodeA;
    nodeP->Right = nodeB;

    return nodeP;
}


Node newNode(int ch, int fq) {
    Node node;

    node = (Node)malloc(sizeof(struct TNode));
    node->Character = ch;
    node->Frequency = fq;
    node->Left = NULL;
    node->Right = NULL;
    return node;
}

void printHeap(MinHeap heap) {
    int i;
    for(i = 0; i <= heap->Size; i++) {
        printf("%d:%c %d\n", i, heap->Data[i]->Character, heap->Data[i]->Frequency);
    }
}

void freeTree(HufTree T) {
    if(T) {
        if(T->Left || T->Right) {
            freeTree(T->Left);
            freeTree(T->Right);
        }
        free(T);
    }
}
