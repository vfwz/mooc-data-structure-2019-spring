#include <stdio.h>
#include <stdlib.h>

typedef struct BinaryTree* BTree;
struct BinaryTree
{
    int DATA;
    BTree LEFT;
    BTree RIGHT;
};

BTree input(int);
BTree createBinaryTree(int);
int isLeafNode(BTree);
void PrintLeafNode(BTree, int);
void printResult(int *, int);


int main()
{
    BTree T;

    int num;
    scanf("%d", &num);
    T = input(num);

    PrintLeafNode(T, num);

    return 0;
}

BTree input(int num)
{
    int leftIndex, rightIndex, i, sum;
    char lt, rt;
    BTree tmpTree;
    BTree treeArr[num];
    int indexArr[num][2];

//    printf("step 1, num is %d\n", num);

    for(i = 0; i < num; i++)
    {
        scanf(" %c %c", &lt, &rt);
        if(lt == '-')
        {
            indexArr[i][0] = -1;
        }
        else
        {
            indexArr[i][0] = lt - '0'; // ��ȡchar����������ֵ
        }

        if(rt == '-')
        {
            indexArr[i][1] = -1;
        }
        else
        {
            indexArr[i][1] = rt - '0';
        }
//        printf("%d-left&right is: %c&%c\n", i, lt, rt);
//        printf("%d-left&right is: %d&%d\n", i, indexArr[i][0], indexArr[i][1]);
        tmpTree = createBinaryTree(i);
        treeArr[i] = tmpTree;
    }

//    printf("step 2\n");
//    for(i = 0; i< num; i++)
//    {
//        printf("%d - %c %d %d\n", i, treeArr[i]->DATA, indexArr[i][0], indexArr[i][1]);
//    }

    sum = num*(num-1)/2; // �����±�ĺ�
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
        printf("DATA: %d", tmpTree->DATA);
        if(tmpTree->LEFT)
        {
            printf(", LEFT: %d", tmpTree->LEFT->DATA);
        }
        if(tmpTree->RIGHT)
        {
            printf(", RIGHT: %d", tmpTree->RIGHT->DATA);
        }
        printf("\n");
    }

    printf("The root is:%d\n", treeArr[sum]->DATA);
    */

    return treeArr[sum]; // ����sumʣ�µ�ֵΪ�������±�
}

void PrintLeafNode(BTree T, int num)
{
    if(!T)   // ��������
    {
        return;
    }
    int i, head = 0, tail=0;
    int flag = 1;
    BTree BQ[num]; // �������10�����
    BQ[tail++] = T; // ��ʼ������򵥵Ķ���
    while(head != tail)
    {
        if(isLeafNode(T))
        {
            printResult(&flag, T->DATA);
        }
        // ����ǰ�����ӽ����뵽����β��
        if(T->LEFT)
            BQ[tail++] = T->LEFT;
        if(T->RIGHT)
            BQ[tail++] = T->RIGHT;
        T = BQ[++head]; // Tȡ���е��¸����
    }
}

/*
* ��ֹ��β�ո�
*/
void printResult(int *firstFlag, int result)
{
    if(*firstFlag)
    {
        printf("%d", result);
        (*firstFlag) = 0;
    }
    else
    {
        printf(" %d", result);
    }
}

BTree createBinaryTree(int Data)
{
    BTree T = (BTree)malloc(sizeof(struct BinaryTree));
    T->DATA = Data;
    T->LEFT = NULL; // ��Ҫ������ ���븳ֵΪ��
    T->RIGHT= NULL;
    return T;
}

int isLeafNode(BTree T)
{
    return !T->LEFT && !T->RIGHT;
}
