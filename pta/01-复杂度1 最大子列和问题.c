#include <stdio.h>

int main() {
    int K, num, i;
    int max = 0, subMax = 0;
    int subFlag = 0; // �Ƿ������ۼ����к�

    scanf("%d", &K);

    for(i = 0; i < K; i++) {
        scanf("%d", &num);
        if(subFlag) {
            subMax += num;
            if(subMax <= 0) {
                subMax = 0;
                subFlag = 0; // �����ǰ���к�С��0��������һ�����к��ۼ�
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
