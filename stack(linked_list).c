//
//  main.cpp
//  Lab4
//
//  Created by eungchan Kang on 2020/03/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum
{
    true,
    false
} bool;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;
typedef int ElementType;

struct Node
{
    ElementType element;
    PtrToNode next;
};

Stack CreateStack()
{
    Stack S = malloc(sizeof(struct Node));

    if (S == NULL)
    {
        perror("Out of space!!\n");
        EXIT_FAILURE;
    }
    S->element = 0;
    S->next = NULL;
    return S;
}

bool IsEmpty(Stack S)
{
    return S->next == NULL;
}

ElementType pop(Stack S)
{
    int picked_value = 0;
    if (IsEmpty(S))
        perror("Stack is Empty\n");
    else
    {
        PtrToNode picked_node = S->next;
        picked_value = picked_node->element;
        S->next = picked_node->next;
        free(picked_node);
    }
    return picked_value;
}
void push(ElementType X, Stack S)
{
    PtrToNode pushed_node = malloc(sizeof(struct Node));
    if (pushed_node == NULL)
    {
        perror("Out of space!!");
        EXIT_FAILURE;
    }
    else
    {
        pushed_node->element = X;
        pushed_node->next = S->next;
        S->next = pushed_node;
    }
}

ElementType Top(Stack S)
{
    if (!IsEmpty(S))
        return S->next->element;
    else
    {
        perror("Stack is Empty\n");
        return 0;
    }
}
void MakeEmpty(Stack S)
{
    if (S == NULL)
        perror("No Stack exists");
    else
    {
        while (!IsEmpty(S))
            pop(S);
    }
}

int get_num(char *str)
{
    int num = -1;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] >= '0' && str[i] <= '9') // check the number from the string.
        {
            if (num == -1)          // only for the first number, because the num has -1 at the first time.
                num = str[i] - '0'; // '9' - '0' = 9
            else
            {
                num *= 10; // to make 1 + 5 = 15
                num += str[i] - '0';
            }
        }
    }
    // return value will be any number if the op is 'push'
    // and it will be -1 if the op is not 'push'
    return num;
}

// to get string operation(push, peek, done) from user input
// input_str is the user input-string
// output_str will be the operation(push, peek, done)
char *get_str(char *input_str)
{
    int index = 0;
    for (int i = 0; i < strlen(input_str); i++)
    {
        if (input_str[i] > '9')
            index++;
    }
    char *output_str = (char *)malloc(sizeof(char) * index);
    for (int i = 0; i < strlen(input_str); i++)
    {
        if (input_str[i] > '9')
            output_str[i] = input_str[i];
    }

    return output_str;
}

void usage()
{
    printf("=========================================================================\n"
           "| if you wnat to push a number(ex : 100) into the stack, type 'push 100'|\n"
           "| if you want to pull from the stack, type 'pop'                       |\n"
           "| if you want to peek from the stack, type 'peek'                       |\n"
           "| if you want to printout the stack, type 'show'                        |\n"
           "| if you want to end, type 'done'                                       |\n"
           "=========================================================================\n");
}

int main(int argc, const char *argv[])
{
    // insert code here...

    Stack stack = CreateStack();
    usage();
    while (1)
    {

        char *op = malloc(sizeof(char) * 10);
        printf("input : ");
        scanf("%[^\n]s", op); // to include space when getting input-string, use [^\n]
        getchar();
        int num = get_num(op); // extract number from input-string.
        printf("\n");
        if (num == -1) // num == -1 means the op is not 'push', it is either 'peek', 'pull','done'
        {
            // char * temp = malloc(sizeof(char) * 4);
            char *temp = get_str(op); // get operation from input-string
            if (strcmp(temp, "pop") == 0)
                pop(stack);
            else if (strcmp(temp, "peek") == 0)
                printf("%d\n", Top(stack));
            // else if(strcmp(temp, "show") == 0)
            // stack_print(stack);
            else if (strcmp(temp, "done") == 0)
                break;
            else
                printf("Wrong input. Try again!!");
        }
        else // the op is 'push'
        {
            push(num, stack);
        }
    }
    return 0;
}