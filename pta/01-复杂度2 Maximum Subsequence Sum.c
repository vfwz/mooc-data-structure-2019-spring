#include <stdio.h>

int main() {
    int K, num, i;
    int max = 0, maxHead = 0, maxTail = 0;
    int subMax = 0, subMaxHead;
    int firstNum, lastNum;
    int subFlag = 0; // 是否正在累加子列和
    int allNegativeFlag = 1;

    scanf("%d", &K);
    for(i = 0; i < K; i++) {
        scanf("%d", &num);
        if(i == 0) {
            firstNum = num; // 记录数列头
            lastNum = num;
        }
        if(i == K-1) {
            lastNum = num;// 记录数列尾
        }

        if(subFlag) {
            subMax += num;
            if(subMax < 0) {
                subMax = 0;
                subFlag = 0; // 如果当前子列和小于0，启动下一次子列和累加
                continue;
            }
        } else {
            if(num > 0) {
                subMaxHead = num;
                subMax = num;
                subFlag = 1;
            }
            if(num >= 0) {
                allNegativeFlag = 0; // 非全负
            }
        }

        if(max < subMax) { // 发现了目前的最大子列和
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
