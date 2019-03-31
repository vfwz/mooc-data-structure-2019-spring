#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

#define ERROR -2
typedef int ElementType;
typedef int Position;
struct SNode
{
    ElementType *Data; /* 存储元素的数组 */
    Position Top;      /* 栈顶指针 */
    int MaxSize;       /* 堆栈最大容量 */
};
typedef struct SNode *Stack;

Stack CreateStack( int MaxSize );
bool IsFull( Stack S );
bool Push( Stack S, ElementType X );
bool IsEmpty( Stack S );
void EmptyStack(Stack S); // 清空堆栈
ElementType Pop( Stack S );
void CheckPop(Stack stack, int[], int len);  // 检查是否合法POP

int main()
{

    // M (the maximum capacity of the stack),
    // N (the length of push sequence),
    // K (the number of pop sequences to be checked)
    int M, N, K;
    int i, j;
    scanf("%d %d %d", &M, &N, &K);
    int data[K][N];
    Stack stack = CreateStack(M);;

    for(i = 0; i < K; i++)
    {
        for(j = 0; j < N; j++)
        {
            scanf("%d", &data[i][j]);
        }
    }

    /* print array
    for(i = 0; i < K; i++) {
        for(j = 0; j < N; j++) {
            printf("%d\t", data[i][j]);
        }
        printf("\n");
    }
    */
    for(i = 0; i < K; i++)
    {
        CheckPop(stack, data[i], N);
    }


    return 0;
}

void CheckPop(Stack stack, int arr[], int len)
{

    int i, chk;
    int cur = 1; // 当前将要放入队列的值
    bool flag;

    /*
    printf("seq to be checked: ");
    for(i = 0; i<len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    */

    for(i = 0; i < len; i ++)
    {
        chk = arr[i];
//        printf("[%d-%d]", cur, chk);
        if(chk < 1 || chk > len)
        {
//            printf("a%d|%d", cur, chk);
            printf("NO\n"); // 被检查序列中有非法值
            EmptyStack(stack);
            return;
        }
        if(cur < chk)
        {
            for(; cur <= chk; cur++) // 如果当前带存放值小于检查序列头，向堆栈中一直放值，直到等于序列头
            {
                flag = Push(stack, cur);
//                printf("[%d^%d^%d]", flag, stack->Top, stack->MaxSize);
                if(!flag)   // 如果放入堆栈失败，表示栈已满
                {
//                    printf("b%d|%d", cur, chk);
                    printf("NO\n");
                    EmptyStack(stack);
                    return;
                }
            }
            Pop(stack); //弹出当前序列头
            continue;
        }
        else if(cur == chk)
        {
            Push(stack, cur);
            Pop(stack);
            cur++;
            //continue;  // 忘了这个...
        }
        else if(cur > chk)
        {
            if(chk != Pop(stack))
            {
//                printf("c%d|%d", cur, chk);
                printf("NO\n");
                EmptyStack(stack);
                return;
            }
        }
    }

    if(cur == len+1)
    {
        printf("YES\n");
        return;
    }
    else
    {
        printf("d|NO\n");
        EmptyStack(stack);
        return;
    }
}

Stack CreateStack( int MaxSize )
{
    Stack S = (Stack)malloc(sizeof(struct SNode));
    S->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
    S->Top = -1;
    S->MaxSize = MaxSize;
    return S;
}

bool IsFull( Stack S )
{
    return (S->Top == S->MaxSize-1);
}

bool Push( Stack S, ElementType X )
{
    if ( IsFull(S) )
    {
//        printf("堆栈满");
        return false;
    }
    else
    {
        S->Data[++(S->Top)] = X;
        return true;
    }
}

bool IsEmpty( Stack S )
{
    return (S->Top == -1);
}

void EmptyStack(Stack S)
{
    S->Top = -1;
}

ElementType Pop( Stack S )
{
    if ( IsEmpty(S) )
    {
//        printf("堆栈空");
        return ERROR; /* ERROR是ElementType的特殊值，标志错误 */
    }
    else
        return ( S->Data[(S->Top)--] );
}
