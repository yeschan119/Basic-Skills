//
//  main.c
//  selection_sort
//
//  Created by eungchan Kang on 2020/03/03.
//

#include <stdio.h>
#include <math.h>

void swap(int *a, int *b, int *temp)
{
    *temp = *a;
    *a = *b;
    *b = *temp;
}
void array_print(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d, ", array[i]);
    }
}
int main(int argc, const char *argv[])
{
    // insert code here...
    // printf("input array size : ");
    // scanf("%d",&array_size);

    int test_array[] = {40, 10, 22, 99, 55, 10, 11, 0};
    int size = (sizeof(test_array)) / 4;

    array_print(test_array, size);
    printf("\n ============================== \n");
    int temp;
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (test_array[i] > test_array[j])
            {
                swap(&test_array[i], &test_array[j], &temp);
            }
        }
    }

    array_print(test_array, size);
    printf("\n");
    return 0;
}