#include <stdio.h>

int main() {
    int K, num, i;
    int max = 0, subMax = 0;
    int subFlag = 0; // 是否正在累加子列和

    scanf("%d", &K);

    for(i = 0; i < K; i++) {
        scanf("%d", &num);
        if(subFlag) {
            subMax += num;
            if(subMax <= 0) {
                subMax = 0;
                subFlag = 0; // 如果当前子列和小于0，启动下一次子列和累加
            }
        } else {
            if(num > 0) {
                subMax = num;
                subFlag = 1;
            }
        }
        max = max<subMax?subMax:max;
    }
    printf("%d", max);

    return 0;
}
