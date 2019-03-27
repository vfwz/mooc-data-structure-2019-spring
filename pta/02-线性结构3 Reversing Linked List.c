#include<stdio.h>

#define MAX_SIZE 100000

void printArr(int[][3], int);
void printNode(int linkArr[][3], int pos);
void reverseSubList(int linkArr[][3], int K, int validNum, int *head);

/*
every K elements on L
可能需要反转多次的
*/
int main() {

    /*  二维数组实现一个双向链表, 100000空间的数组大小为 100000 * 3 * sizeof(int) Bytes = 1.2MB 内存
        i 当前结点地址
        link[i][0] 值
        link[i][1] 前一个结点地址
        link[i][2] 后一个结点地址
    */

    int linkArr[MAX_SIZE][3];
    // head 链表头地址，N 链表总长度，K 反转个数
    int head, N, K;
    int cur, data, next;
    int i, validNum=0;

//    while(1) {
//        printf("--------------\n");

        scanf("%d %d %d", &head, &N, &K);
        linkArr[head][1] = -1; // 将头结点的前一个结点地址设置为-1

        for(i = 0; i < N; i++) {
            scanf("%d %d %d", &cur, &data, &next);
            linkArr[cur][0] = data;
            if(next != -1) {
                linkArr[next][1] = cur; // 设置下一个结点的前一个结点地址
            }
            linkArr[cur][2] = next;   // 设置当前结点的下一个结点地址
//        printf("input:");
//        printNode(linkArr, cur);
        }
//        printf("排序前的链表为：\n");
//        printArr(linkArr, head);
        cur = head;
        while(cur != -1) {
            cur = linkArr[cur][2];
            ++validNum;
        };


        reverseSubList(linkArr, K, validNum, &head);

//        printf("排序后的链表为：\n");
        printArr(linkArr, head);

//    }
    return 0;
}

void reverseSubList(int linkArr[][3], int K, int validNum, int *head) {
    if(K <= 1 || K > validNum) { // K==1或者超出范围无需反转
        return;
    }
    int times,i = 0, tmp, start = *head, cur = *head;

    for(times = 0; times < validNum/K; ++times) { // 含有多个子序列，都要反转
//        printf("===start switch\n");
        for(i = 0; i < K; i++) {
//            printf("before:\t");
//            printNode(linkArr, cur);
            if(i == K-1) {
                tmp = linkArr[start][2]; // 子序列头结点的前一个结点地址
                linkArr[start][2] = linkArr[cur][2]; //原头结点的下一个结点地址指向第K个结点的下一结点地址
                linkArr[cur][2] = linkArr[cur][1];   // 当前结点的下一个结点地址为当前结点的前一个结点地址
                linkArr[cur][1] = tmp;  //  当前结点的前一个结点地址为子序列头结点的前一个结点地址, Note该节点地址被反转过
                if(tmp != -1) {
                    linkArr[tmp][2] = cur;
                }
                if(times == 0) { // 第一次反转，可以确定新序列的头
                    *head = cur;
                }
                tmp = start;
                start = linkArr[start][2]; // 下一个子序列的开始结点
                linkArr[start][1] = tmp;

//                printf("after:\t");
//                printNode(linkArr, cur);

                cur = start;
            } else { // 交换结点的前后结点地址
                tmp = linkArr[cur][1];
                linkArr[cur][1] = linkArr[cur][2];
                linkArr[cur][2] = tmp;

//                printf("after:\t");
//                printNode(linkArr, cur);

                cur = linkArr[cur][1]; // 继续处理下一个结点，由于前后地址互换，取前一个地址
            }
        }
//        printf("===end switch\n");
    }
}

void printArr(int linkArr[][3], int head) {
    int cur = head;
    while(cur != -1) {
        printNode(linkArr, cur);
        cur = linkArr[cur][2];
    };
}

void printNode(int linkArr[][3], int pos) {
    if(linkArr[pos][2] == -1) {
        printf("%05d %d %d\n", pos, linkArr[pos][0], linkArr[pos][2]);
    } else {
        printf("%05d %d %05d\n", pos, linkArr[pos][0], linkArr[pos][2]);
    }
}
