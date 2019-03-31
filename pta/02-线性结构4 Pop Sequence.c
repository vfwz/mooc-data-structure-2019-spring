#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

#define ERROR -2
typedef int ElementType;
typedef int Position;
struct SNode
{
    ElementType *Data; /* �洢Ԫ�ص����� */
    Position Top;      /* ջ��ָ�� */
    int MaxSize;       /* ��ջ������� */
};
typedef struct SNode *Stack;

Stack CreateStack( int MaxSize );
bool IsFull( Stack S );
bool Push( Stack S, ElementType X );
bool IsEmpty( Stack S );
void EmptyStack(Stack S); // ��ն�ջ
ElementType Pop( Stack S );
void CheckPop(Stack stack, int[], int len);  // ����Ƿ�Ϸ�POP

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
    int cur = 1; // ��ǰ��Ҫ������е�ֵ
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
            printf("NO\n"); // ������������зǷ�ֵ
            EmptyStack(stack);
            return;
        }
        if(cur < chk)
        {
            for(; cur <= chk; cur++) // �����ǰ�����ֵС�ڼ������ͷ�����ջ��һֱ��ֵ��ֱ����������ͷ
            {
                flag = Push(stack, cur);
//                printf("[%d^%d^%d]", flag, stack->Top, stack->MaxSize);
                if(!flag)   // ��������ջʧ�ܣ���ʾջ����
                {
//                    printf("b%d|%d", cur, chk);
                    printf("NO\n");
                    EmptyStack(stack);
                    return;
                }
            }
            Pop(stack); //������ǰ����ͷ
            continue;
        }
        else if(cur == chk)
        {
            Push(stack, cur);
            Pop(stack);
            cur++;
            //continue;  // �������...
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
//        printf("��ջ��");
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
//        printf("��ջ��");
        return ERROR; /* ERROR��ElementType������ֵ����־���� */
    }
    else
        return ( S->Data[(S->Top)--] );
}
