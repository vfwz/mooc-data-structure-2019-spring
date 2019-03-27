#include<stdio.h>

#define MAX_SIZE 100000

void printArr(int[][3], int);
void printNode(int linkArr[][3], int pos);
void reverseSubList(int linkArr[][3], int K, int validNum, int *head);

/*
every K elements on L
������Ҫ��ת��ε�
*/
int main() {

    /*  ��ά����ʵ��һ��˫������, 100000�ռ�������СΪ 100000 * 3 * sizeof(int) Bytes = 1.2MB �ڴ�
        i ��ǰ����ַ
        link[i][0] ֵ
        link[i][1] ǰһ������ַ
        link[i][2] ��һ������ַ
    */

    int linkArr[MAX_SIZE][3];
    // head ����ͷ��ַ��N �����ܳ��ȣ�K ��ת����
    int head, N, K;
    int cur, data, next;
    int i, validNum=0;

//    while(1) {
//        printf("--------------\n");

        scanf("%d %d %d", &head, &N, &K);
        linkArr[head][1] = -1; // ��ͷ����ǰһ������ַ����Ϊ-1

        for(i = 0; i < N; i++) {
            scanf("%d %d %d", &cur, &data, &next);
            linkArr[cur][0] = data;
            if(next != -1) {
                linkArr[next][1] = cur; // ������һ������ǰһ������ַ
            }
            linkArr[cur][2] = next;   // ���õ�ǰ������һ������ַ
//        printf("input:");
//        printNode(linkArr, cur);
        }
//        printf("����ǰ������Ϊ��\n");
//        printArr(linkArr, head);
        cur = head;
        while(cur != -1) {
            cur = linkArr[cur][2];
            ++validNum;
        };


        reverseSubList(linkArr, K, validNum, &head);

//        printf("����������Ϊ��\n");
        printArr(linkArr, head);

//    }
    return 0;
}

void reverseSubList(int linkArr[][3], int K, int validNum, int *head) {
    if(K <= 1 || K > validNum) { // K==1���߳�����Χ���跴ת
        return;
    }
    int times,i = 0, tmp, start = *head, cur = *head;

    for(times = 0; times < validNum/K; ++times) { // ���ж�������У���Ҫ��ת
//        printf("===start switch\n");
        for(i = 0; i < K; i++) {
//            printf("before:\t");
//            printNode(linkArr, cur);
            if(i == K-1) {
                tmp = linkArr[start][2]; // ������ͷ����ǰһ������ַ
                linkArr[start][2] = linkArr[cur][2]; //ԭͷ������һ������ַָ���K��������һ����ַ
                linkArr[cur][2] = linkArr[cur][1];   // ��ǰ������һ������ַΪ��ǰ����ǰһ������ַ
                linkArr[cur][1] = tmp;  //  ��ǰ����ǰһ������ַΪ������ͷ����ǰһ������ַ, Note�ýڵ��ַ����ת��
                if(tmp != -1) {
                    linkArr[tmp][2] = cur;
                }
                if(times == 0) { // ��һ�η�ת������ȷ�������е�ͷ
                    *head = cur;
                }
                tmp = start;
                start = linkArr[start][2]; // ��һ�������еĿ�ʼ���
                linkArr[start][1] = tmp;

//                printf("after:\t");
//                printNode(linkArr, cur);

                cur = start;
            } else { // ��������ǰ�����ַ
                tmp = linkArr[cur][1];
                linkArr[cur][1] = linkArr[cur][2];
                linkArr[cur][2] = tmp;

//                printf("after:\t");
//                printNode(linkArr, cur);

                cur = linkArr[cur][1]; // ����������һ����㣬����ǰ���ַ������ȡǰһ����ַ
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
