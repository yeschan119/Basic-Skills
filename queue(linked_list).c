//
//  main.c
//  queue
//
//  Created by eungchan Kang on 2020/03/08.
//

// enqueue, dequeue, print를 할 수 있는 queue 구현

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int key;
    struct Node *next;
} Node;

typedef struct Queue
{
    struct Node *front, *rear;
} Queue;

Node *Make_newNode(int key)
{
    Node *new = (Node *)malloc(sizeof(struct Node));
    new->key = key;
    new->next = NULL;
    return new;
}

Queue *Init_queue()
{
    Queue *new = (Queue *)malloc(sizeof(Queue));
    new->front = new->rear = NULL;
    return new;
}

void Enqueue(int key, Queue *Q)
{
    Node *new = Make_newNode(key);
    if (Q->front == NULL && Q->rear == NULL)
    {
        Q->front = new;
        Q->rear = new;
    }
    else
    {
        Node *temp = Q->front;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        Q->rear = new;
        temp->next = new;
    }
    printf("New node(%d) is added\n", key);
}

Node *Dequeue(Queue *Q)
{
    if (Q->front != NULL)
    {
        Node *dequeue_node = Q->front;
        Q->front = dequeue_node->next;
        printf("Node %d is dequeued\n", dequeue_node->key);
        return dequeue_node;
    }
    else
        return NULL;
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

int Print_Queue(Queue *Q)
{
    if (Q->front == NULL && Q->rear == NULL)
    {
        return -1;
    }
    Queue *q = Init_queue();
    Node *show = Q->front;
    q->front = show->next;
    Print_Queue(q);
    printf("<--%d", show->key);
    return 0;
}

void usage()
{
    printf("===============================================================================\n"
           "| if you wnat to enqueue a number(ex : 100) into the queue, type 'enqueue 100'|\n"
           "| if you want to dequeue from the stack, type 'dequeue'                       |\n"
           "| if you want to printout the stack, type 'print'                             |\n"
           "| if you want to end, type 'done'                                             |\n"
           "===============================================================================\n");
}

int main(int argc, const char *argv[])
{
    // insert code here...
    Queue *test = Init_queue();

    // char * temp = get_str("Enqueue 999");
    usage();
    // printf("Input\n");
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
            if (strcmp(temp, "dequeue") == 0)
                Dequeue(test);
            else if (strcmp(temp, "print") == 0)
                Print_Queue(test);
            else if (strcmp(temp, "done") == 0)
                break;
            else
                printf("Wrong input. Try again!!");
        }
        else // the op is 'push'
        {
            Enqueue(num, test);
        }
        printf("\n");
    }
    return 0;
}