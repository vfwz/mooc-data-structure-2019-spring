#include <stdio.h>

void InputConnection(int* set, int c1, int c2);
void CheckConnection(int* set, int c1, int c2);
void CheckComponent(int* set, int N);
int findRoot(int* set, int X);

int main() {

    int N, i;
    char action;
    int c1, c2;

    scanf("%d", &N);

    int set[N+1];
    for(i = 1; i < N+1; i++) {
        set[i] = -1; // 初始化所有集合元素个数为1
    }

    scanf("%c", &action);
    while(action != 'S') {
        scanf("%d %d", &c1, &c2);

        if(action == 'I') {
            InputConnection(set, c1, c2);
        } else if(action == 'C') {
            CheckConnection(set, c1, c2);
        }

        scanf("%c", &action);
    }
    CheckComponent(set, N);

    return 0;
}

void InputConnection(int* set, int c1, int c2) {
    int r1, r2;

    r1 = findRoot(set, c1);
    r2 = findRoot(set, c2);

    if(set[r1] < set[r2]) { // 如果r1集合的元素比r2多
        set[r1] += set[r2];
        set[r2] = r1;       // 将r2合并到r1上
    } else {
        set[r2] += set[r1];
        set[r1] = r2;
    }

}


void CheckConnection(int* set, int c1, int c2) {
    int r1, r2;
    r1 = findRoot(set, c1);
    r2 = findRoot(set, c2);

    if(r1 == r2) {
        printf("yes\n");
    } else {
        printf("no\n");
    }
}

void CheckComponent(int* set, int N) {
    int i, count = 0;
    for(i=1; i<N+1; i++) {
//        printf("[%d,%d] ", i, set[i]);
        if(set[i] <= 0) {
            count++;
        }
    }
//    printf("\n");

    if(count == 1) {
        printf("The network is connected.\n");
    } else {
        printf("There are %d components.\n", count);
    }

}

int findRoot(int* set, int X) {
    int i = X;
    while(set[i] > 0) {
        i = set[i];
    }
    return i;
}

