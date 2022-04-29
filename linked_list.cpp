//
//  main.cpp
//  linked_list
//
//  Created by eungchan Kang on 2021/03/23.

// insert, delete, find, find previous, print 기능을 갖춘 stack을 linked list로 구현

#include <iostream>
#include <string>

using namespace std;
typedef class Node *PtrToNode;
typedef PtrToNode Position;
typedef PtrToNode List;
typedef int ElementType;

class Node
{
public:
    ElementType element;
    Position next;
    Node() {}
    List MakeEmpty();
    int IsEmpty(List L);
    int IsLast(Position P, List L);
    Position Find(ElementType X, List L);
    Position FindPrevious(ElementType X, List L);
    void Delete(ElementType X, List L);
    void Insert(ElementType X, List L, Position P);
    void DeleteList(List L);
    void printList(List L);
};

List MakeEmpty()
{
    List L = new Node();
    L->element = 0;
    L->next = NULL;
    return L;
}

bool IsEmpty(List L)
{
    return L->next == NULL;
}

bool IsLast(Position P, List L)
{
    return P->next == NULL;
}

Position Find(ElementType X, List L)
{
    Position P = L->next;
    while (P != NULL && P->element != X)
    {
        P = P->next;
    }
    return P;
}

Position FindPrevious(ElementType X, List L)
{
    Position P = L;
    while (P->next->element != X && P->next != NULL)
    {
        P = P->next;
    }
    return P;
}

void Delete(ElementType X, List L)
{
    Position P = FindPrevious(X, L);
    if (!IsLast(P, L))
    {
        Position deleted_node = P->next;
        P->next = deleted_node->next;
        free(deleted_node);
    }
    else
    {
        cout << "No element(" << X << ")"
             << "to delete" << endl;
    }
}

void Insert(ElementType X, List L, Position P)
{
    Position inserted_node = new Node();
    if (inserted_node == NULL)
    {
        perror("Out of space!\n");
        EXIT_FAILURE;
    }
    else if (P)
    {
        inserted_node->element = X;
        inserted_node->next = P->next;
        P->next = inserted_node;
    }
    else
    {
        inserted_node->element = X;
        inserted_node->next = L->next;
        L->next = inserted_node;
    }
}

void DeleteList(List L)
{
    Position P = L->next;
    Position Tmp;
    L->next = NULL;
    while (P != NULL)
    {
        Tmp = P->next;
        free(P);
        P = Tmp;
    }
    free(L);
}

void printList(List L)
{
    Position print_node;
    if (!IsEmpty(L))
    {
        print_node = L->next;
        while (print_node != NULL)
        {
            cout << print_node->element << " ";
            print_node = print_node->next;
        }
    }
    else
        printf("List is Empty\n");
}

int main(int argc, const char *argv[])
{
    // insert code here...

    List chan = MakeEmpty();
    int X;
    for (int i = 10, j = 0; i < 20; i++)
    {
        X = i * 10;
        Insert(X, chan, Find(j, chan));
        j = X;
    }
    cout << "after insertion : ";
    printList(chan);
    cout << endl;
    for (int i = 10; i < 19; i++)
    {
        X = i * 10;
        Delete(X, chan);
    }
    cout << "after deletion : ";
    printList(chan);
    cout << endl;
    DeleteList(chan);
    return 0;
}