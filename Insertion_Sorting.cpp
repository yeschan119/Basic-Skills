#include <iostream>

void insertion_sort(int A[], int n)
{
    int key = 0;
    int j = 0;
    for (int i = 1; i < n; i++)
    {
        key = A[i];
        j = i - 1;
        while (j >= 0 && A[j] > key)
        {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = key;
    }
}

int main(void)
{

    int A[] = {3, 8, 1, 0, 10, 15, 60, 0, 2, 5};
    int n = sizeof(A) / sizeof(A[0]);
    int i;
    // std::cout<<"Input number of Array"<<std::endl;
    for (i = 0; i < n; i++)
    {
        std::cout << A[i] << ", ";
    }

    std::cout << "\nAfter insertion\n";
    insertion_sort(A, n);
    for (i = 0; i < n; i++)
    {
        std::cout << A[i] << ", ";
    }
    std::cout << "\n";
    return 0;
}