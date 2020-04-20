#include <stdio.h>

// 本程序对常见的排序算法做一个梳理


/* 选择排序 */
void select_sort (int *arr, int len)
{
	int i, j;
	int min_pos;
	int min_val;
	int temp;
	for (i = 0; i < len - 1; ++i)
	{
		min_val = arr[i];
		for (j = i; j < len; ++j)
		{
			if (arr[j] < min_val)
			{
				min_val = arr[j];
				min_pos = j;
			}
		}
		if (i != min_pos)
		{
			temp = arr[i];
			arr[i] = arr[min_pos];
			arr[min_pos] = temp;
		}
	}
	return;
}

/*  插入排序 */
void insert_sort (int *arr, int len)
{
	int i;
	int j;
	int cur_num;
	for (i = 1; i < len; ++i)
	{
		cur_num = arr[i];
		for (j = i; j >= 1; --j)
		{
			if (arr[j] < arr[j-1])
			{
				arr[j] = arr[j-1];
				arr[j-1] = cur_num;
				continue;
			}
		}
	}
	return ;
}

/* 希尔排序 */

void shell_sort (int *arr, int len)
{}


void print_arr (int *arr, int len)
{
	int i;
	for (i = 0; i < len; ++i)
	{
		printf ("%d ", arr[i]);
	}
	printf ("\n");
	return;
}

#define ARR_LEN 10
int main (void)
{
	int arr[ARR_LEN] = {2,3,1,5,4,1,5,3,7,2};
	//select_sort (arr, ARR_LEN);
	insert_sort (arr, ARR_LEN);
	print_arr (arr, ARR_LEN);
	return 0;
}
