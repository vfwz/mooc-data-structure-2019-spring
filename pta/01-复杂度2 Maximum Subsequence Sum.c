#include <stdio.h>

int main() {
    int K, num, i;
    int max = 0, maxHead = 0, maxTail = 0;
    int subMax = 0, subMaxHead;
    int firstNum, lastNum;
    int subFlag = 0; // �Ƿ������ۼ����к�
    int allNegativeFlag = 1;

    scanf("%d", &K);
    for(i = 0; i < K; i++) {
        scanf("%d", &num);
        if(i == 0) {
            firstNum = num; // ��¼����ͷ
            lastNum = num;
        }
        if(i == K-1) {
            lastNum = num;// ��¼����β
        }

        if(subFlag) {
            subMax += num;
            if(subMax < 0) {
                subMax = 0;
                subFlag = 0; // �����ǰ���к�С��0��������һ�����к��ۼ�
                continue;
            }
        } else {
            if(num > 0) {
                subMaxHead = num;
                subMax = num;
                subFlag = 1;
            }
            if(num >= 0) {
                allNegativeFlag = 0; // ��ȫ��
            }
        }

        if(max < subMax) { // ������Ŀǰ��������к�
            max = subMax;
            maxHead = subMaxHead;
            maxTail = num;
        }
    }

    if(allNegativeFlag) {
        maxHead = firstNum;
        maxTail = lastNum;
    }

    printf("%d %d %d\n", max, maxHead, maxTail);

    return 0;
}
