#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node{
    ElementType Coefficient;
    ElementType Exponent;
    PtrToNode Next;
};
typedef struct Node *List;

List Read();
void Print(List);
PtrToNode NewNode(ElementType coefficient, ElementType exponent); // ����һ���µĽ��
List Sum(List L1, List L2); // ����ʽ���
List Multiply(List L1, List L2); // ��������ʽ���
List _Multi(PtrToNode SNode, List L1); // ������������ʽ���

int main() {
    List L1, L2, SL, PL;
    L1 = Read();
    L2 = Read();
//    Print(L1);
//    Print(L2);
    PL = Multiply(L1, L2);
    SL = Sum(L1, L2);
    Print(PL);
    Print(SL);

    return 0;
}

List Read() {
    int num,coefficient, exponent, i;
    PtrToNode node, last;
    List polynomialList = NewNode(0, 0);
    last = polynomialList;

    scanf("%d", &num);
//    printf("����ʽ����Ϊ��%d\n", num);
    for(i = 0; i < num; i++) {
        scanf("%d %d", &coefficient,&exponent);
        node = NewNode(coefficient, exponent);
        last->Next = node;
        last = node;
//        printf("input elem:%d %d\t", coefficient, exponent);
    }
    return polynomialList;
}

void Print(List poly) {
//    printf("\nStart Print Poly:");
    if(poly->Next) {
        while(poly->Next){
            printf("%d %d", poly->Next->Coefficient, poly->Next->Exponent);
            poly = poly->Next;
            if(poly->Next){
                printf(" "); //���һ�����û�пո�
            }else {
                printf("\n");
            }
        }
    } else {
        printf("%d %d\n", poly->Coefficient, poly->Exponent);
    }
}

List Sum(List L1, List L2) {
    List SumList = NewNode(0, 0);
    PtrToNode Last = SumList;
    PtrToNode New;
    ElementType SumCoe, L1NodeExp, L2NodeExp;
    while(L1->Next || L2->Next) {
        if(L1->Next == NULL) { // L1Ϊ��, ֱ�ӽ���L2
            Last->Next = L2->Next;
            return SumList;
        }
        if(L2->Next == NULL) { // L2Ϊ��, ֱ�ӽ���L1
            Last->Next = L1->Next;
            return SumList;
        }
        L1NodeExp = L1->Next->Exponent;
        L2NodeExp = L2->Next->Exponent;
        if(L1NodeExp > L2NodeExp) {
            New = NewNode(L1->Next->Coefficient, L1NodeExp);
            Last->Next = New;
            Last = New;
            L1=L1->Next; // ����1ָ�����
        } else if(L1NodeExp < L2NodeExp) {
            New = NewNode(L2->Next->Coefficient, L2NodeExp);
            Last->Next = New;
            Last = New;
            L2=L2->Next; // ����2ָ�����
        } else { // ����
            SumCoe = L1->Next->Coefficient+L2->Next->Coefficient;
            if(SumCoe != 0) {// ϵ���Ͳ�Ϊ0
                New = NewNode(SumCoe, L2NodeExp);
                Last->Next = New;
                Last = New;
            }
            L1=L1->Next;
            L2=L2->Next;// ����1,2ָ�붼Ҫ����
        }
    }
    return SumList;
}

List Multiply(List L1, List L2) {
    List NodeProd, ProdList;
    ProdList = NewNode(0, 0);
    if(L1->Next == NULL || L2->Next==NULL) {// ������һ������ʽΪ0, ���������ʽ
        return ProdList;
    } else {
        while(L1->Next) {
            NodeProd = _Multi(L1->Next, L2); // ��L1�ĵ��������L2���
            ProdList = Sum(NodeProd, ProdList); // �������ĳ˻���Ϊ����ʽ�ĳ˻�
            L1 = L1->Next; // ����L1�����Ľ��
        }
    }
    return ProdList;
}

List _Multi(PtrToNode node, List list) {
    List NodeProd = NewNode(0, 0);
    ElementType coefficient, exponent;
    PtrToNode newNode, last;
    last = NodeProd;
    while(list->Next) {
        coefficient = node->Coefficient * list->Next->Coefficient; // ϵ�����
        exponent = node->Exponent + list->Next->Exponent; // ָ�����
        newNode = NewNode(coefficient, exponent);
        last->Next = newNode;
        last = newNode;
        list=list->Next; // list ����
    }
    return NodeProd;
}

PtrToNode NewNode(ElementType coefficient, ElementType exponent) {

    /*
     ע���ʼ�����Ĵ�С��
     ��������12, 4, 4
    printf("%d,%d,%d\n", sizeof(Node), sizeof(PtrToNode), sizeof(List));
    */
    PtrToNode newNode = (PtrToNode*)malloc(sizeof(struct Node));
    newNode->Coefficient = coefficient;
    newNode->Exponent = exponent;
    newNode->Next = NULL;
    return newNode;
}
