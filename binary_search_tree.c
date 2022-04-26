//
//  main.c
//  Lab6
//
//  Created by eungchan Kang on 2020/04/07.
//

#include <stdio.h>
#include <stdlib.h>
int count = 0; // to avoid duplicated print key

typedef struct BinarySearchTree *Tree;
struct BinarySearchTree
{
    int value;
    Tree left;
    Tree right;
};

Tree insertNode(Tree root, int key)
{
    if (root == NULL)
    {
        root = malloc(sizeof(struct BinarySearchTree));
        if (root == NULL)
        {
            perror("Out of space!!");
            exit(1);
        }
        root->value = key;
        root->left = NULL;
        root->right = NULL;
        printf("insert %d\n", key);
    }
    else if (key < root->value)
        root->left = insertNode(root->left, key);
    else if (key > root->value)
        root->right = insertNode(root->right, key);
    else
        printf("There is already %d in the tree\n", key);

    return root;
}

Tree findNode(Tree root, int key)
{
    if (root == NULL)
    {
        printf("%d is not in the tree\n", key);
        return root;
    }
    else if (key < root->value)
        return findNode(root->left, key);
    else if (key > root->value)
        return findNode(root->right, key);
    else
    {
        printf("%d is in the tree\n", key);
        return root;
    }
}

Tree getMaxValueInTree(Tree root)
{
    if (root == NULL)
    {
        perror("Tree is empty\n");
    }
    else
    {
        while (root->right != NULL)
            root = root->right;
    }
    return root;
}

Tree findMax(Tree root)
{
    if (root == NULL)
    {
        perror("Tree is empty\n");
    }
    else
    {
        while (root->right != NULL)
            root = root->right;
    }
    return root;
}

Tree deleteNode(Tree root, int key)
{
    Tree Tmp;
    if (root == NULL)
        printf("Deletion Error: %d is not in the tree\n", key);
    else if (key < root->value)
        root->left = deleteNode(root->left, key);
    else if (key > root->value)
        root->right = deleteNode(root->right, key);
    else if (root->left && root->right) // found node to be deleted and it has two children
    {
        count = 1; // to avoid duplicated print key
        Tmp = getMaxValueInTree(root->left);
        root->value = Tmp->value;
        root->left = deleteNode(root->left, root->value);
        printf("Delete %d\n", key);
    }
    else
    {

        Tree Tmp = root;
        if (root->left == NULL)
            root = root->right;
        else if (root->right == NULL)
            root = root->left;
        free(Tmp);
        if (count != 1) // to avoid duplicated print key
            printf("Delete %d\n", key);
        count = 0; // get back to zero to get chance print key
    }

    return root;
}

void printInorder(Tree root)
{
    if (root)
    {
        printInorder(root->left);
        printf("%d ", root->value);
        printInorder(root->right);
    }
}

void printPreorder(Tree root)
{
    if (root)
    {

        printf("%d ", root->value);
        printPreorder(root->left);
        printPreorder(root->right);
    }
}

void usage1(void)
{
    printf("Open terminal or prompt\
           And Make exe file using 'gcc -0 test main.c' and type ./test input.txt\n");
}
void usage2(void)
{
    printf("-> i 10 is insert 10\
            -> d 10 is delete 10\
            -> f 10 is find 10\
            -> pi is print by inorder\n");
}
int main(int argc, const char *argv[])
{
    // insert code here...
    char cv;
    int key;
    FILE *file = fopen(argv[1], "r");
    Tree root = NULL;

    while (!feof(file))
    {
        fscanf(file, "%c", &cv);
        switch (cv)
        {
        case 'i':
            fscanf(file, "%d", &key);
            root = insertNode(root, key);
            break;
        case 'd':
            fscanf(file, "%d", &key);
            root = deleteNode(root, key);
            break;
        case 'f':
            fscanf(file, "%d", &key);
            findNode(root, key);
            break;
        case 'p':
            fscanf(file, "%c", &cv);
            if (cv == 'i')
                printInorder(root);
            printf("\n");
            break;
        }
    }

    return 0;
}