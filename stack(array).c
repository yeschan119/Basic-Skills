//
//  main.c
//  stack
//
//  Created by eungchan Kang on 2020/03/06.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    true,
    false
} bool; // create user defdined data type to use boolean type

// stack structure
// top is the index of the stack
// size is the capacity of the stack
// array is the stack
typedef struct Stack
{
    int top;
    unsigned size;
    int *array;
} Stack;

// to initialize the stack with size, top, array
Stack *init_stack(unsigned int stack_size)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->size = stack_size;
    stack->top = -1; // 'top' is used to index array(stack), so the start must be a -1.
    stack->array = (int *)malloc(stack_size * sizeof(int));

    for (int i = 0; i < stack_size; i++)
    {
        stack->array[i] = -1; // all elements of the stack are initialized with -1
    }
    return stack;
}

// check isFull for the stack
bool check_full(Stack *stack)
{
    if (stack->top == stack->size - 1)
        return true;
    else
        return false;
}
// check isEmpty for the stack
bool check_empty(Stack *stack)
{
    if (stack->top == -1)
        return true;
    else
        return false;
}
// push elements into the stack
void push(Stack *stack, int element)
{
    if (check_full(stack) == true) // true means stack is full
        printf("This stack is full.\nYou can push after popping\n");
    else
    {
        int i = ++stack->top; // increment the size of the stack
        stack->array[i] = element;
        printf("pushed %d into the stack\n", element);
    }
}

// take out the top element of the stack
// And decrease the top(size of the elements)
int pull(Stack *stack)
{
    if (check_empty(stack) == true)
    { // if stack is empty, output the error message.
        printf("This stack is empty.\nYou can pop after pushing.\n");
        return -1;
    }
    else
    {
        int top = stack->array[stack->top];
        stack->array[stack->top] = -1; // after pulling, fill the old top with -1
        stack->top--;
        printf("Top(%d) of stack is popped\n", top);
        return top;
    }
}
// check the top element of the stack
int peek(Stack *stack)
{
    if (check_empty(stack) == true) // it the stack is empty output the error message.
    {
        printf("No items to peek. Stack is empty %d/n", check_empty(stack));
        return -1;
    }
    else
    {
        printf("The top of stack is %d\n", stack->array[stack->top]);
        return stack->array[stack->top];
    }
}
// show the stack
void stack_print(Stack *stack)
{
    int i = stack->top;
    while ((stack->array[i] != -1) && i >= 0)
    { // To show the stack. print top-down.
        printf("|%d|\n", stack->array[i]);
        i--;
    }
    printf("\n");
}
// when pushing elements, only extract number from input
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
    int stack_size;
    printf("Insert the size of stack : ");
    scanf("%d", &stack_size);
    Stack *stack = init_stack(stack_size);
    printf("\n");
    usage();

    while (1)
    {
        getchar();
        char *op = malloc(sizeof(char) * 10);
        printf("input : ");
        scanf("%[^\n]s", op); // to include space when getting input-string, use [^\n]

        int num = get_num(op); // extract number from input-string.
        printf("\n");
        if (num == -1) // num == -1 means the op is not 'push', it is either 'peek', 'pull','done'
        {
            // char * temp = malloc(sizeof(char) * 4);
            char *temp = get_str(op); // get operation from input-string
            if (strcmp(temp, "pop") == 0)
                pull(stack);
            else if (strcmp(temp, "peek") == 0)
                peek(stack);
            else if (strcmp(temp, "show") == 0)
                stack_print(stack);
            else if (strcmp(temp, "done") == 0)
                break;
            else
                printf("Wrong input. Try again!!");
        }
        else // the op is 'push'
        {
            push(stack, num);
        }
        printf("\n");
    }
    return 0;
}