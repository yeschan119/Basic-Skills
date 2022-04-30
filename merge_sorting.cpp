
#include <iostream>

using namespace std;

void Merge(int A[], int p, int q, int r)
{
    int n1 = q - p;
    int n2 = r - q;
    int *L = new int[n1];
    int *R = new int[n2];

    for (int i = 0; i < n1; i++)
    {
        L[i] = A[p + i - 1];
    }
    for (int j = 0; j < n2; j++)
        R[j] = A[q + j];

    L[n1 + 1] = numeric_limits<int>::max();
    R[n2 + 1] = numeric_limits<int>::max();

    int i = 0;
    int j = 0;

    for (int k = p; k < r; k++)
    {
        if (L[i] <= R[j])
        {
            A[k] = L[i];
            i++;
        }
        else
        {
            A[k] = R[j];
            j++;
        }
    }
}

void Merge_sort(int A[], int p, int r)
{
    if (p < r)
    {
        int q = (p + r) / 2;
        Merge_sort(A, p, q);
        Merge_sort(A, q + 1, r);
        Merge(A, p, q, r);
    }
}

int main()
{
    int A[] = {5, 3, 9, 8, 1, 0, 7, 6, 2};
    int p = 0;
    int r = sizeof(A) / sizeof(int);
    Merge_sort(A, p, r);

    for (int i = 0; i < r; i++)
        cout << A[i] << ", ";
    return 0;
}