//
//  main.cpp
//  AVLTree
//
//  Created by eungchan Kang on 2020/04/29.
//

#include <iostream>
#include <fstream>
using namespace std;

typedef int ElementType;
typedef class AVLNode *AVLTree;
typedef class AVLNode *Position;

// max value를 리턴해주는 함수
template <class T>
const T &Max(const T &a, const T &b)
{
    return (a < b) ? b : a;
}

// AVLNode class 정의
class AVLNode
{
public:
    AVLNode() {}
    AVLTree BuildTree();
    ElementType Element;
    AVLTree Left;
    AVLTree Right;
    int Height;
};

AVLTree BuildTree()
{
    AVLTree newTree = new AVLNode();
    newTree->Left = NULL;
    newTree->Right = NULL;
    return newTree;
}

// AVL tree의 높이를 리턴해주는 함수
int Height(AVLTree P)
{
    if (P == NULL)
        return -1;
    else
        return P->Height;
}

// single rotating을 진행하는 함수
// node -> left1 -> left2 에서
// left1을 root, node를 right, left2를 left로 만들기
Position SingleRotateWithLeft(Position node)
{
    Position P;
    P = node->Left;
    node->Left = P->Right;
    P->Right = node;

    node->Height = Max(Height(node->Left), Height(node->Right)) + 1;
    P->Height = Max(Height(P->Left), node->Height) + 1;

    return P;
}

// single rotating를 진행하는 함수
// node -> right -> right
Position SingleRotateWithRight(Position node)
{
    Position P;
    P = node->Right;
    node->Right = P->Left;
    P->Left = node;

    node->Height = Max(Height(node->Left), Height(node->Right)) + 1;
    P->Height = Max(Height(P->Left), node->Height) + 1;

    return P;
}

// left child의 right subtree가 unbalanced인 경우
// right subtree에 대해서 먼저 singleRotatingwithRight을 진행하고
// left child에 대해서 singleRotatingwithLeft를 진행
Position DoubleRotateWithLeft(Position node)
{
    node->Left = SingleRotateWithRight(node->Left);
    return SingleRotateWithLeft(node);
}

// right child의 left subtree인 경우
Position DoubleRotateWithRight(Position node)
{
    node->Right = SingleRotateWithLeft(node->Right);
    return SingleRotateWithRight(node);
}

// 찾는 값이 tree에 있으면 true 없으면 false
bool Find(AVLTree T, ElementType X)
{
    if (T == NULL)
        return false;
    if (X < T->Element)
        return Find(T->Left, X);
    else if (X > T->Element)
        return Find(T->Right, X);
    else
        return true;
}

// Binary search Tree와 매우 유사
// insert을 진행할 때마다 height의 차가 2이상인 subtree를 찾아 rotating 진행
AVLTree Insert(ElementType X, AVLTree T)
{
    if (Find(T, X))
    {
        cout << "[Error] " << X << " already in the tree" << endl;
        return T;
    }

    if (T == NULL)
    {
        T = new AVLNode();
        if (T == NULL)
        {
            cout << "Out of space!" << endl;
            exit(1);
        }
        T->Element = X;
        T->Left = T->Right = NULL;
    }
    else if (X < T->Element) // may need left rotating
    {
        T->Left = Insert(X, T->Left);
        if (Height(T->Left) - Height(T->Right) == 2)
        {
            if (X < T->Left->Element) // T -> left -> left가 되므로 single rotating
                T = SingleRotateWithLeft(T);
            else
                T = DoubleRotateWithLeft(T); // ㅆ -> right가 되므로 double rotating
        }
    }
    else if (X > T->Element) // may need right rotating
    {
        T->Right = Insert(X, T->Right);
        if (Height(T->Right) - Height(T->Left) == 2)
        {
            if (X > T->Right->Element)
                T = SingleRotateWithRight(T);
            else
                T = DoubleRotateWithRight(T);
        }
    }
    T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
    return T;
}

void PrintInorder(AVLTree T)
{
    if (T)
    {
        PrintInorder(T->Left);
        if (T->Element != 0)
            cout << T->Element << " (" << T->Height << ") ";
        PrintInorder(T->Right);
    }
}

void DeleteTree(AVLTree T)
{
    if (T->Left != NULL)
        DeleteTree(T->Left);
    if (T->Right != NULL)
        DeleteTree(T->Right);
    free(T);
}

void specification()
{
    cout << "\
==========================================================================\n\
1. initiate AVLTree\n\
2. Insert value in order.\n\
3. keep the balance of the Tree and Print node and height of node.\n\
4. ex: 10 (1) means the value of node is 10, the height of this node is 1\n\
5. No allowed duplication\n\
==========================================================================\n"
         << endl;
}

int main(int argc, const char *argv[])
{

    specification();
    // insert code here...
    /*
    ifstream readFile;
    readFile.open(argv[1]);
    string elements;
    getline(readFile, elements);
     */
    AVLTree myTree = BuildTree();

    int S[] = {7, 5, 3, 10, 23, 4, 20, 21, 22, 23, 24, 25};
    int size = sizeof(S) / sizeof(int);

    int i = 0;
    while (i < size)
    {
        myTree = Insert(S[i], myTree);
        PrintInorder(myTree);
        cout << endl;
        i++;
    }

    DeleteTree(myTree);
    return 0;
}