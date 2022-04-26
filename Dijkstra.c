//
//  main.c
//  Dijkstra's_Algorithm
//
//  Created by eungchan Kang on 2021/06/02.
//

/*
 Dijkstra Algorithm
 Every node(vertex) is placed in Array
 Distance(node -> node) is placed in the matrix
 shortest distance is placed in the min-heap
 intput :
    number of nodes
    relation(distance) from node to another node
 output :
    the cost(distance) from first node to all others
*/
#include <stdio.h>
#include <stdlib.h>

const int INF = (int)2e9; // initialize all distances with infinity
typedef enum
{
    true,
    false
} bool;

// dist is a distance
// prev is a node before vertex
typedef struct Node
{
    int vertex;
    int dist;
    int prev;
} Node;

// 1 ~ Vertices are placed in nodes
Node *initialize_node(Node *nodes, int Vertices)
{
    for (int i = 1; i < Vertices; i++)
    {
        nodes[i].vertex = i;
        nodes[i].prev = 0;
        nodes[i].dist = INF;
    }
    return nodes;
}

//===================================== Graph ======================================//

// nodes are vertices
// matrix contains distances for vertices
typedef struct Graph
{
    int size;
    Node *nodes;
    int **matrix;
} Graph;

Graph *createGraph(int size)
{
    Graph *G = malloc(sizeof(Graph));
    G->size = size;
    G->nodes = malloc(sizeof(Node) * size);
    G->nodes = initialize_node(G->nodes, size);
    G->matrix = (int **)malloc(sizeof(int *) * size);
    for (int i = 1; i < size; i++)
    {
        G->matrix[i] = malloc(sizeof(int) * size);
        for (int j = 1; j < size; j++)
        {
            G->matrix[i][j] = INF; // initialize the matrix with infinity
        }
    }
    return G;
}

//=================================== min Heap ===================================//
struct HeapStruct;
typedef struct HeapStruct *Heap;
typedef int ElementType;
struct HeapStruct
{
    int capacity;
    int size;
    Node *Elements;
};

Heap CreateHeap(int heapSize);
bool IsFull(Heap tree);
bool IsEmpty(Heap tree);
void insert(ElementType X, Heap H);
ElementType DeleteMax(Heap H);
int Find(Heap H, int value);
void printHeap(Heap H);
void PercDown(ElementType Tree[], int i, int N);
void BuildHeap(ElementType Tree[], int N);

Heap CreateHeap(int heapSize)
{
    Heap newTree = malloc(sizeof(struct HeapStruct));
    newTree->size = 0;
    newTree->capacity = heapSize;
    newTree->Elements = malloc(sizeof(Node) * heapSize);
    newTree->Elements[0].dist = 0;
    return newTree;
}
bool IsFull(Heap tree)
{
    return tree->size == tree->capacity;
}
bool IsEmpty(Heap tree)
{
    return tree->size == 0;
}

// X goes up until X is larger than its parent
// parent = floor(i/2)
void insertToMinHeap(Heap H, Node node)
{
    if (IsFull(H))
    {
        printf("Insertion Error : Min Heap is Full!\n");
        return;
    }
    else if (Find(H, node.vertex))
    {
        // printf("%d is already in the heap.\n",node.vertex);
        return;
    }
    int i;
    for (i = ++H->size; H->Elements[i / 2].dist > node.dist; i /= 2)
    {
        H->Elements[i] = H->Elements[i / 2];
    }

    H->Elements[i].dist = node.dist;
    H->Elements[i].vertex = node.vertex;
    H->Elements[i].prev = node.prev;
    // printf("insert vertex %d -> ",node.vertex);
    // printf("insert distance %d\n",node.dist);
}

Node *DeleteMin(Heap H)
{
    if (IsEmpty(H))
    {
        printf("Deletion Error : minHeap is Empty!\n");
        return NULL;
    }
    int i, child = 0;
    Node *minElement = malloc(sizeof(Node));
    Node *LastElement = malloc(sizeof(Node));

    minElement->dist = H->Elements[1].dist;
    minElement->vertex = H->Elements[1].vertex;
    minElement->prev = H->Elements[1].prev;
    int size = H->size--;
    LastElement->dist = H->Elements[size].dist;
    LastElement->vertex = H->Elements[size].vertex;
    LastElement->prev = H->Elements[size].prev;
    for (i = 1; i * 2 < H->size; i = child)
    {
        child = i * 2;
        if (child != H->size && H->Elements[child + 1].dist < H->Elements[child].dist) // compare left with right child
            child++;
        if (LastElement->dist > H->Elements[child].dist)
            H->Elements[i] = H->Elements[child];
        else
            break;
    }
    H->Elements[i].dist = LastElement->dist;
    H->Elements[i].vertex = LastElement->vertex;
    H->Elements[i].prev = LastElement->prev;
    // printf("Min vertex: %d is deleted, ",minElement->vertex);
    // printf("Min dist: %d is deleted\n",minElement->dist);
    return minElement;
}

int Find(Heap H, int value)
{

    for (int i = 1; i < H->size; i++)
    {
        if (value == H->Elements[i].vertex)
            return 1;
    }
    return 0;
}

// ===================== execute Dijkstra's Algorithm =================================//

void printShortesPath(Graph *G)
{
    Heap minHeap = CreateHeap(G->size);

    // d(1,1) is 0
    // prev(1,1) is 1
    G->nodes[1].dist = 0;
    insertToMinHeap(minHeap, G->nodes[1]);
    G->nodes[1].prev = G->nodes[1].vertex;
    Node *currentNode = malloc(sizeof(Node));

    int u;
    while (!IsEmpty(minHeap))
    {
        // current node has a shortest distance
        currentNode = DeleteMin(minHeap);
        u = currentNode->vertex;
        for (int v = 1; v < G->size; v++)
        {
            // d[u] + w[u + v] < d[v]
            //  d[v] = w[u+v]
            if ((G->nodes[u].dist + G->matrix[u][v]) < G->nodes[v].dist)
            {
                G->nodes[v].dist = G->nodes[u].dist + G->matrix[u][v];
                G->nodes[v].prev = u;
                insertToMinHeap(minHeap, G->nodes[v]);
            }
        }
    }
    printf("\n");
    // print distance from first to others
    for (int i = 2; i < G->size; i++)
    {
        if (G->nodes[i].dist == INF) // no link from first to this node
            printf("%d can not be reached.\n", G->nodes[i].vertex);
        else if (G->nodes[i].prev != G->nodes[1].vertex) // to print from first, check via nodes until meet first node
        {
            int p = i;
            while (G->nodes[p].vertex != G->nodes[1].vertex)
            {
                printf("%d <- ", G->nodes[p].vertex);
                p = G->nodes[p].prev;
            }
            printf("%d cost: %d\n", G->nodes[p].vertex, G->nodes[i].dist);
        }
        else
            printf("%d <- %d cost: %d\n", G->nodes[i].vertex, G->nodes[i].prev, G->nodes[i].dist);
    }
    printf("\n");
}

int main(int argc, const char *argv[])
{
    // insert code here...

    FILE *f = fopen(argv[1], "r");
    int size;
    fscanf(f, "%d", &size);
    Graph *G = createGraph(size + 1);

    int node_s, node_d, weight;

    // node_s : start node
    // node_d : destination node
    // weight : distance from start to distance
    while (fscanf(f, "%d %d %d", &node_s, &node_d, &weight) != EOF)
    {
        G->matrix[node_s][node_d] = weight;
    }
    printShortesPath(G);

    return 0;
}