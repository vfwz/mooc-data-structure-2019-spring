#include <stdio.h>


/*
二维数组存储图
一维数组存储无向图
链表存储图
*/

void visit(int* V, int i) {
    printf(" %d", i);
    V[i] = 1;
}

void initVertex(int* V, int N) {
    int i;

    for(i = 0; i < N; ++i) {
        V[i] = 0;
    }
}

void printGraph(int graph[][10], int N) {
    int i,j,k;
    printf("========start print graph, N = %d\n", N);
    for(i = 0; i < N; ++i) {
        for(j = 0; j < N; ++j) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
    printf("========end print graph\n");
}

void DFS_ITER(int graph[][10], int* V, int N, int row) {
    for(int j = 0; j < N; ++j) {
        if(graph[row][j] && !V[j]) {
            visit(V, j);
            DFS_ITER(graph, V, N, j);
        }

    }
}

void DFS(int graph[][10], int N) {
    int V[N], i;
    initVertex(V, N);
    for(i = 0; i < N; i++) {
        if(V[i]) {
            continue;
        }
        printf("{");
        visit(V, i);
        DFS_ITER(graph, V, N, i);
        printf(" }\n");
    }

}

void BFS(int graph[][10], int N) {
    int i, V[N], queue[N], qHead, qTail, j, k;
    initVertex(V, N);

    for(i = 0; i < N; i++) {
        if(V[i]) {
            continue;
        }
        printf("{");
        // 初始化队列
        queue[0] = i;
        visit(V, i);
        qHead = 0;
        qTail = 1;
        while(qHead != qTail) {
//            printf("N=%d, qHead=%d, qTail=%d\n", N, qHead, qTail);
            // 弹出队列首元素
            k = queue[qHead++];
            for(j = 0; j < N; j++) {
//                printf("current item: N=%d, k=%d, j=%d, graph[%d][%d]=%d, V[%d]=%d\n", N, k, j, k, j, graph[k][j], j, V[j]);
                if(graph[k][j] && !V[j]) { // k到j的边存在，并且j没被访问过
                    visit(V, j);
                    queue[qTail++] = j;
                }
            }
        }
        printf(" }\n");
    }
}

int main() {
    int N, E, i, j;
    int v1, v2; // vertex
    scanf("%d %d", &N, &E);
    int graph[N][10];

    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            graph[i][j] = 0; // 图的初始化
        }
    }

//    printGraph(graph, N);

    for(i = 0; i < E; i++) {
        scanf("%d %d", &v1, &v2);
        graph[v1][v2] = 1;
        graph[v2][v1] = 1;
    }

//    printGraph(graph, N);

    DFS(graph, N);
    BFS(graph, N);

    return 0;
}
