/*
�ֶ���֮�ķ�ʽ���
https://www.jianshu.com/p/18cff70b673d
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct BinaryTree* BTree;
struct BinaryTree {
    int DATA;
    BTree LEFT;
    BTree RIGHT;
};

void input(int[][2], int);
BTree generateBTreeFromStack(int[][2], int);
BTree createBinaryTree(int);
void printResult(int *, int);
void printBTree(BTree T);
void postTraverseTree(BTree T, int *firstFlag);

int main() {

    int num, firstFlag = 1;;
    scanf("%d", &num);
    BTree tree;

    int opArr[num*2][2];
    input(opArr, num);

    tree = generateBTreeFromStack(opArr, num);

    postTraverseTree(tree, &firstFlag);

    return 0;
}

void input(int arr[][2], int num) {
    int data, i;
    char str[5];

    for(i = 0; i < num*2; i++) {
        scanf("%s", str);
//        printf("=%s=%d=\n", str, data);
        if(str[1] == 'u') {
            arr[i][0] = 1;
            scanf("%d", &data);
            arr[i][1] = data;
        } else if(str[1] == 'o') {
            arr[i][0] = -1;
            arr[i][1] = -1;
        } else {
            printf("wrong input\n");
        }

//        printf("arr=%d=%d=\n", arr[i][0], arr[i][1]);
    }
}


BTree generateBTreeFromStack(int opArr[][2], int num) {
    int i, cur = 0;
    BTree root, node;
    BTree trees[num]; // ��Ŷ�ջ�����Ա�

//    printf("step1\n");

    root = createBinaryTree(opArr[0][1]);
    trees[cur] = root;

    for(i = 1; i < num*2; i++) {
        if(opArr[i][0] == 1) { // Push����
            node = createBinaryTree(opArr[i][1]);

            if(opArr[i-1][0] == 1) { // �����һ��������Push�������ý����֮ǰPush�����Ľ�������
                trees[cur]->LEFT = node;
            } else if(opArr[i-1][0] == -1) { // �����һ��������Pop�������ý����֮ǰPop�����Ľ����Һ���
                trees[cur+1]->RIGHT = node;
            }
            trees[++cur] = node;
        } else if(opArr[i][0] == -1) { // Pop����
            cur--;

        }
    }

    printBTree(root);

    return root;
}

void postTraverseTree(BTree T, int *firstFlag) {
    if(T) {
        postTraverseTree(T->LEFT, firstFlag);
        postTraverseTree(T->RIGHT, firstFlag);
        printResult(firstFlag, T->DATA);
    }
}

void printBTree(BTree T) {
    if(T) {
        printf("���%d", T->DATA);
        if(T->LEFT) {
            printf(", ����%d", T->LEFT->DATA);
        }
        if(T->RIGHT) {
            printf(", �Һ���%d", T->RIGHT->DATA);
        }
        printf("\n");

        printBTree(T->LEFT);
        printBTree(T->RIGHT);
    }
}

/*
* ��ֹ��β�ո�
*/
void printResult(int *firstFlag, int result) {
    if(*firstFlag) {
        printf("%d", result);
        (*firstFlag) = 0;
    } else {
        printf(" %d", result);
    }
}

BTree createBinaryTree(int Data) {
    BTree T = (BTree)malloc(sizeof(struct BinaryTree));
    T->DATA = Data;
    T->LEFT = NULL; // ��Ҫ������ ���븳ֵΪ��
    T->RIGHT= NULL;
    return T;
}
