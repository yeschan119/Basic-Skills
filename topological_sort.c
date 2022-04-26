//
//  main.c
//  queue
//
//  Created by eungchan Kang on 2020/03/08.
//

/*
 input : 노드 개수, 숫자 집합, 연결관계(node + edge)
 ex: 5, {1,2,3,4,5}, 1->2, 2->3, 3->4...
 output : topological sorting 결과
 방법 :
 숫자 집합을 그래프의 vertex로 옮기고 연결관계를 edge로 설정하여 그래프 완성
 그래프로 옮기는 방법:
 숫자 잡합을 row X column으로 하는 빈 matrix 만들기
 indegree가 있을 경우 그 숫자들이 만나는 부분에 1씩 더해서 matrix 속성 채우기
 */

#include <stdio.h>
#include <stdlib.h>

//========================== Graph layer ========================================//
// define the graph structure
typedef struct _Graph *Graph;
struct _Graph
{
    int size;
    int *node;
    int **matrix;
};

Graph CreateGraph(int x)
{
    Graph new = malloc(sizeof(struct _Graph));
    new->size = x;
    new->node = malloc(sizeof(int) * x);
    new->matrix = (int **)malloc(sizeof(int *) * x);
    for (int i = 0; i < x; i++)
    {
        new->matrix[i] = malloc(sizeof(int) * x);
    }
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < x; j++)
        {
            new->matrix[i][j] = 0;
        }
    }
    return new;
}

// 매 노드마다 체크하면서 indegree가 나타날 때마다 matrix에서 해당 숫자의 결합부분을 1씩 증가
void InsertEdge(Graph G, int node_source, int node_dest)
{
    int s = 0, d = 0;
    for (int i = 0; i < G->size; i++)
    {
        if (G->node[i] == node_source)
            s = i;
        else if (G->node[i] == node_dest)
            d = i;
    }
    G->matrix[s][d]++;
}

//========================== Queue layer ========================================//
// mtrix에서 graph로 숫자들을 옮기는 과정에 스토리지로 queue 사용
// queue is made of linked list

typedef struct Node
{
    int key;
    struct Node *next;
} Node;

typedef struct Queue
{
    struct Node *front, *rear;
} Queue;

Queue *Init_queue(void)
{
    Queue *new = (Queue *)malloc(sizeof(Queue));
    new->front = new->rear = NULL;
    return new;
}

Node *CreateQueue(int key)
{
    Node *new = (Node *)malloc(sizeof(struct Node));
    new->key = key;
    new->next = NULL;
    return new;
}

void Enqueue(Queue *Q, int key)
{
    Node *new = CreateQueue(key);
    if (Q->front == NULL)
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
    // printf("New node(%d) is added\n", key);
}

int Dequeue(Queue *Q)
{
    if (Q->front != NULL)
    {
        Node *dequeue_node = Q->front;
        Q->front = Q->front->next;
        // printf("Node %d is dequeued\n", dequeue_node->key);
        int key = dequeue_node->key;
        free(dequeue_node);
        return key;
    }
    else
        return -1;
}

int IsEmpty(Queue *Q)
{
    if (Q->front == NULL)
        return 1;
    else
        return 0;
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
    printf("%d ", show->key);
    Print_Queue(q);

    return 0;
}

//=================================== Topological Sorting layer ==========================================//

// matrix에서 queue를 이용하여 숫자들을 하나씩 꺼내면서
// 순서대로 sorting, 즉 graph 완성

//
int get_index(int *Node, int size, int x)
{

    int i;
    for (i = 0; i < size; i++)
    {
        if (Node[i] == x)
            return i;
    }
    return -1;
}

// 해당 노드에 indegree edge가 있으면 1, 없으면 0 리턴
int checkIndegree(Graph G, int i)
{
    for (int j = 0; j < G->size; j++)
    {
        if (G->matrix[j][i] == 1)
            return 1;
    }
    return 0;
}

// indegree가 없는 노드를 queue에 저장하고
// 이 노드가 가지고 있는 outdegree를 모두 제거하여 다른 node의 indgree를 없애준다.
void removeOutdegree(Graph G, int index)
{
    for (int i = 0; i < G->size; i++)
    {
        G->matrix[index][i] = 0;
    }
}

void print_Graph(Graph G)
{
    for (int i = 0; i < G->size; i++)
    {
        for (int j = 0; j < G->size; j++)
        {
            printf("%d ", G->matrix[i][j]);
        }
        printf("\n");
    }
}

void check_indegree(Queue *Q, Graph G, int *enqueued_node)

{

    int Indegree_check;
    for (int i = 0; i < G->size; i++)
    {
        if (enqueued_node[i] == -1)
            continue;
        Indegree_check = checkIndegree(G, i); // matrix의 매 컬럼값을 받아, 세로방향으로 indgree 체크
        if (Indegree_check == 0)
        {
            Enqueue(Q, G->node[i]);
            enqueued_node[i] = -1; // to avoid duplicated indegree check
        }
    }
}

/*
 sorting  순서
 1. 매트릭스 컬럼을 하나씩 체크하면서 indegree 노드가 나오면 바로 enqueue
 2. 커낸 데이터가 연결하고 있는 outdegree를 모두 제거하여 그에 연결된 다른 노드들이 indegree가 될 확률 높이기
 3. 1-2를 반복하면서 indegree가 나오지 않을 때나 queue가 빌 때까지 반복
 */
void Topsort(Graph G)
{
    // matrix에서 graph로 빠져나간 데이터의 자리에 -1을 채우기 위해
    // original data set과 같은 크기의 set을 생성
    int *enqueued_node;
    enqueued_node = malloc(sizeof(int) * G->size);
    for (int i = 0; i < G->size; i++)
    {
        enqueued_node[i] = 0;
    }

    // queue 생성
    Queue *Q = Init_queue();

    // 매트릭스의 컬람을 하나씩 체크하고
    // indegree가 없는 데이터를 enqueue하기
    check_indegree(Q, G, enqueued_node);
    while (!IsEmpty(Q))
    {
        // Print_Queue(Q);

        int V = Dequeue(Q);
        printf("%d ", V);

        //꺼내온 데이터가 매트릭스 안에서 어느 자리에 있는 지를 알기 위해
        int index = get_index(G->node, G->size, V);

        // remove out-degree for all neighbors
        if (index >= 0)
            removeOutdegree(G, index);
        else
        {
            printf("Index Error\n");
            exit(1);
        }

        check_indegree(Q, G, enqueued_node);
    };

    printf("\nDone\n");
}

int main(int argc, const char *argv[])
{
    // insert code here...

    FILE *f = fopen(argv[1], "r");
    int x, node_s, node_d;

    fscanf(f, "%d", &x);

    Graph G = CreateGraph(x);

    for (int i = 0; i < x; i++)
    {
        fscanf(f, "%d", &G->node[i]);
    }

    printf("\n------nodes-----\n\n");
    for (int i = 0; i < x; i++)
    {
        printf("%d ", G->node[i]);
    }

    printf("\n\n----node with edges----\n\n");
    while (fscanf(f, "%d %d", &node_s, &node_d) != EOF)
    {
        InsertEdge(G, node_s, node_d);
        printf("%d --> %d\n", node_s, node_d);
    }
    printf("\n-----Graph-----\n\n");
    print_Graph(G);
    printf("\n---Topological sorting---\n\n");
    Topsort(G);

    return 0;
}