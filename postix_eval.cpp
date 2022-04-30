//
//  main.cpp
//  Lab4
//
//  Created by eungchan Kang on 2020/03/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define EmptyTop (-1)
#define MaxSize 101

typedef enum
{
    true,
    false
} bool;
typedef struct StackRecord *Stack;
typedef int ElementType;
char operators[] = {'+', '-', '*', '/', '%'};
struct StackRecord
{
    int max_stack_size;
    int Top;
    ElementType *key;
};

Stack CreateStack(int MaxElements)
{
    Stack S = malloc(sizeof(struct StackRecord));
    if (S == NULL)
    {
        perror("Out of Space!!\n");
        exit(1);
    }
    S->key = (int *)malloc(sizeof(ElementType) * MaxElements);
    S->max_stack_size = MaxElements;
    S->Top = EmptyTop;
    return S;
}

bool IsFull(Stack S)
{
    if (S->Top >= S->max_stack_size)
        return true;
    else
        return false;
}

bool IsEmpty(Stack S)
{
    if (S->Top == -1)
        return true;
    else
        return false;
}

void Push(ElementType X, Stack S)
{
    if (IsFull(S) == false)
        S->key[++S->Top] = X;
    else
    {
        perror("\nStack is Full\n");
        exit(1);
    }
}

ElementType Pop(Stack S)
{
    if (IsEmpty(S) == false)
        return S->key[S->Top--];
    else
    {
        perror("\nStack is Empty\n");
        exit(1);
        return 0;
    }
}

ElementType Top(Stack S)
{
    if (IsEmpty(S) == false)
        return S->key[S->Top];
    else
    {
        return 0;
    }
}
bool check_operator(char input_str)
{
    for (int i = 0; i < strlen(operators); i++)
    {
        if (input_str == operators[i])
            return true;
    }
    return false;
}

ElementType Perform_op(int a, int b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '%':
        return a % b;
    default:
        break;
    }
    return 0;
}

void Postfix(Stack S, char input_str)
{
    if (input_str > '0' && input_str <= '9')
    {
        ElementType X = input_str - '0';
        Push(X, S);
    }
    else if (check_operator(input_str) == true)
    {
        ElementType a = Pop(S);
        ElementType b = Pop(S);
        ElementType X = Perform_op(b, a, input_str);
        Push(X, S);
    }
    else
    {
        perror("Invalid input\n");
    }
}
void DeleteStack(Stack S)
{
    free(S->key);
    free(S);
}
int main(int argc, const char *argv[])
{
    // insert code here...
    FILE *file = fopen(argv[1], "r");

    Stack stack;
    char input_str[MaxSize];

    fgets(input_str, MaxSize, file);
    stack = CreateStack(MaxSize - 1);
    printf("Top numbers : ");

    for (int i = 0; i < strlen(input_str) && input_str[i] != '#'; i++)
    {
        Postfix(stack, input_str[i]);
        printf("%d ", Top(stack));
    }
    printf("\nevaluation result : %d\n", Top(stack));
    // fclose(file);
    DeleteStack(stack);
    return 0;
}