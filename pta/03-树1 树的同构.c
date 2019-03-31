#include <stdio.h>
#include <stdlib.h>

typedef struct BinaryTree* BTree;
struct BinaryTree
{
    int DATA;
    BTree LEFT;
    BTree RIGHT;
};

BTree input();
BTree createBinaryTree(int);
void PreTraversal(BTree);
void printTwoBTree(BTree, BTree);
int isLeafNode(BTree);
int BigFirstTraversal(BTree, BTree);


int main()
{
    BTree T1, T2;

    T1 = input();
    T2 = input();
//    PreTraversal(T1);
//    T2 = input();
    if(BigFirstTraversal(T1, T2)) {
        printf("Yes");
    }else {
        printf("No");
    }

    return 0;
}

BTree input()
{
    int num, leftIndex, rightIndex, i, sum;
    char data, lt, rt;
    BTree tmpTree;
    scanf("%d", &num);
    BTree treeArr[num];
    int indexArr[num][2];

//    printf("step 1, num is %d\n", num);


    for(i = 0; i < num; i++)
    {
        scanf(" %c %c %c", &data, &lt, &rt);
        if(lt == '-')
        {
            indexArr[i][0] = -1;
        }
        else
        {
            indexArr[i][0] = lt - '0'; // 获取char的字面数字值
        }

        if(rt == '-')
        {
            indexArr[i][1] = -1;
        }
        else
        {
            indexArr[i][1] = rt - '0';
        }
//        printf("data is:%c - %d\n", data, data);
//        printf("%d-left&right is: %c&%c\n", i, lt, rt);
//        printf("%d-left&right is: %d&%d\n", i, indexArr[i][0], indexArr[i][1]);
        tmpTree = createBinaryTree(data);
        treeArr[i] = tmpTree;
    }

//    printf("step 2\n");
//    for(i = 0; i< num; i++)
//    {
//        printf("%d - %c %d %d\n", i, treeArr[i]->DATA, indexArr[i][0], indexArr[i][1]);
//    }

    sum = num*(num-1)/2; // 所有下标的和
    for(i = 0; i < num; i++ )
    {
        leftIndex = indexArr[i][0];
        rightIndex = indexArr[i][1];
        tmpTree = treeArr[i];
        if(leftIndex != -1)
        {
            tmpTree->LEFT = treeArr[leftIndex];
            sum = sum - leftIndex;
        }
        if(rightIndex != -1)
        {
            tmpTree->RIGHT = treeArr[rightIndex];
            sum = sum - rightIndex;
        }
    }

    /*
    printf("step 4\n");
    for(i = 0; i < num; i++)
    {
        tmpTree = treeArr[i];
        printf("DATA: %c", tmpTree->DATA);
        if(tmpTree->LEFT)
        {
            printf(", LEFT: %c", tmpTree->LEFT->DATA);
        }
        if(tmpTree->RIGHT)
        {
            printf(", RIGHT: %c", tmpTree->RIGHT->DATA);
        }
        printf("\n");
    }

    printf("The root is:%c\n", treeArr[sum]->DATA);
    */

    return treeArr[sum]; // 最终sum剩下的值为根结点的下标
}

BTree createBinaryTree(int Data)
{
    BTree T = (BTree)malloc(sizeof(struct BinaryTree));
    T->DATA = Data;
    T->LEFT = NULL; // 重要！！！ 必须赋值为空
    T->RIGHT= NULL;
    return T;
}

/**
* 先序遍历打印树
*/
void PreTraversal(BTree tree)
{
    if(tree)
    {
        printf("%c", tree->DATA);
        PreTraversal(tree->LEFT);
        PreTraversal(tree->RIGHT);
    }
}

/**
* 孩子结点先大后小遍历
*/
int BigFirstTraversal(BTree T1, BTree T2)
{
    int f1, f2;
    BTree FB1, FB2, SB1, SB2;
//    printf("start traversal:");
//    printTwoBTree(T1, T2);
    if(!T1 && !T2)      // 都是空树
    {
//        printf("Branch1 Result:[%d],:", 1);
//        printTwoBTree(T1, T2);
        return 1;
    }

    if((T1&&!T2) || (!T1&&T2))   // 其中一棵为空树
    {
//        printf("Branch2 Result:[%d],:", 0);
//        printTwoBTree(T1, T2);
        return 0;
    }

    if(T1->DATA != T2->DATA)   // 当前两棵树的结点值不同
    {
//        printf("Branch3 Result:[%d]\n", 0);
//        printTwoBTree(T1, T2);
        return 0;
    }

    if(isLeafNode(T1) && isLeafNode(T2)) { // 都是叶子节点
//        printf("Branch3.33 Result:[%d]\n", 1);
//        printTwoBTree(T1, T2);
        return 1;
    }

    if(T1->LEFT && T1->RIGHT)
    {
        if(!T2->LEFT || !T2->RIGHT)  // T1 有两个孩子，T2却只有一个或没有，一定不是同构树
        {
//        printf("Branch4 Result:[%d]\n", 0);
//        printTwoBTree(T1, T2);
            return 0;
        }
        // 接下来遍历两棵树的值较大的子节点

        if(T1->LEFT->DATA > T1->RIGHT->DATA)
        {
            FB1 = T1->LEFT;
            FB2 = T1->RIGHT;
        }
        else
        {
            FB1 = T1->RIGHT;
            FB2 = T1->LEFT;
        }
        if(T2->LEFT->DATA > T2->RIGHT->DATA)
        {
            SB1 = T2->LEFT;
            SB2 = T2->RIGHT;
        }
        else
        {
            SB1 = T2->RIGHT;
            SB2 = T2->LEFT;
        }
        f1 = BigFirstTraversal(FB1, SB1);
        f2 = f1?BigFirstTraversal(FB2, SB2):0; // 第一次比较是同构的才做第二次比较，节省性能
//        printf("Branch5 Result:[%d]\n", f1&&f2);
//        printTwoBTree(T1, T2);
        return f1&&f2;
    }
    else if(T1->LEFT || T1->RIGHT)
    {
        if(T2->LEFT && T2->RIGHT)  // T1 有一个孩子，T2却有两个，一定不是同构树
        {
            return 0;
        }
        if(!T2->LEFT && !T2->RIGHT)  // T1 有一个孩子，T2却没有，一定不是同构树
        {
            return 0;
        }
        FB1 = T1->LEFT ? T1->LEFT : T1->RIGHT;
        SB1 = T2->LEFT ? T2->LEFT : T2->RIGHT;
        f1 = BigFirstTraversal(FB1, SB1);
//        printf("Branch6 Result:[%d]\n", f1);
//        printTwoBTree(T1, T2);
        return f1;
    }

}

void printTwoBTree(BTree T1, BTree T2) {
    if(!T1 && !T2) {
        printf("T1 root: [Empty], T2 root: [Empty]\n");
    }
    if(T1 && !T2) {
        printf("T1 root: [%c], T2 root: [Empty]\n", T1->DATA);
    }
    if(!T1 && T2) {
        printf("T1 root: [Empty], T2 root: [%c]\n", T2->DATA);
    }
    if(T1 && T2) {
        printf("T1 root: [%c], T2 root: [%c]\n", T1->DATA, T2->DATA);
    }
}

int isLeafNode(BTree T) {
    return !T->LEFT && !T->RIGHT;
}
