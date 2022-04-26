//
//  main.c
//  BinaryHeap
//
//  Created by eungchan Kang on 2020/04/13.
//
// maxHeap code

#include <stdio.h>
#include <stdlib.h>

struct HeapStruct;
typedef struct HeapStruct *Heap;
typedef int ElementType;
typedef enum
{
    true,
    false
} bool;
struct HeapStruct
{
    int capacity;
    int size;
    ElementType *Elements;
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
    newTree->Elements = malloc(sizeof(ElementType) * heapSize);
    newTree->Elements[0] = 0xFFFFFFF;
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

// X goes up until X is smaller than its parent
// parent = floor(i/2)
void insert(ElementType X, Heap H)
{
    if (IsFull(H))
    {
        printf("Insertion Error : Max Heap is Full!\n");
        return;
    }
    else if (Find(H, X))
    {
        printf("%d is already in the heap.\n", X);
        return;
    }
    int i;
    for (i = ++H->size; H->Elements[i / 2] < X; i /= 2)
    {
        H->Elements[i] = H->Elements[i / 2];
    }

    H->Elements[i] = X;
    printf("insert %d\n", X);
}

ElementType DeleteMax(Heap H)
{
    if (IsEmpty(H))
    {
        printf("Deletion Error : maxHeap is Empty!\n");
        return 0;
    }
    int i, child = 0;
    ElementType maxElement, LastElement;

    maxElement = H->Elements[1];
    LastElement = H->Elements[H->size--];

    for (i = 1; i * 2 < H->size; i = child)
    {
        child = i * 2;
        if (child != H->size && H->Elements[child + 1] > H->Elements[child]) // compare left with right child
            child++;
        if (LastElement < H->Elements[child])
            H->Elements[i] = H->Elements[child];
        else
            break;
    }
    H->Elements[i] = LastElement;
    printf("Max Element: %d is deleted\n", maxElement);
    return maxElement;
}

int Find(Heap H, int value)
{

    for (int i = 1; i <= H->size; i++)
    {
        if (value == H->Elements[i])
            return 1;
    }
    return 0;
}

void printHeap(Heap H)
{

    if (IsEmpty(H))
    {
        printf("Print Error : maxHeap is empty!\n");
        return;
    }
    for (int i = 1; i <= H->size; i++)
    {
        printf("%d ", H->Elements[i]);
    }
    printf("\n");
}

#define LeftChild(i) (2 * i) // leftchild = 2 * i
void PercDown(ElementType Tree[], int i, int N)
{
    int child = 0;
    ElementType Tmp;
    for (Tmp = Tree[i]; LeftChild(i) <= N; i = child)
    {
        child = LeftChild(i); // 2 * i
        if (child != N && Tree[child + 1] > Tree[child])
            child++;
        if (Tmp < Tree[child])
            Tree[i] = Tree[child];
        else
            break;
    }
    Tree[i] = Tmp;
}

void BuildHeap(ElementType Tree[], int N)
{
    int i;
    for (i = N / 2; i > 0; i--)
    {
        PercDown(Tree, i, N);
    }
}

int main(int argc, const char *argv[])
{
    // insert code here...
    FILE *file = fopen(argv[1], "r");
    char cv;
    Heap maxHeap;
    int heapSize, key;

    while (!feof(file))
    {
        fscanf(file, "%c", &cv);
        switch (cv)
        {
        case 'n':
            fscanf(file, "%d", &heapSize);
            maxHeap = CreateHeap(heapSize);
            break;
        case 'i':
            fscanf(file, "%d", &key);
            insert(key, maxHeap);
            break;
        case 'd':
            DeleteMax(maxHeap);
            break;
        case 'p':
            printHeap(maxHeap);
            break;
        case 'f':
            fscanf(file, "%d", &key);
            if (Find(maxHeap, key))
                printf("%d is in the heap.\n", key);
            else
                printf("%d is not in the heap.\n", key);
            break;
        default:
            break;
        }
    }

    return 0;
}