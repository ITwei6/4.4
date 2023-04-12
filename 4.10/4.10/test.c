//左区间有序后，右区间有序后才可以归并
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
void _MergeSort(int *a,int begin,int end,int *tmp)
{
	if (begin >= end)
		return;
	int mid = (begin+end) / 2;
	//[begin   mid] [mid+1   end]
	_MergeSort(a, begin, mid, tmp);
	_MergeSort(a, mid + 1, end,tmp);//递归分割左右区间，直到分割成有序（1个区间）

	//归并[begin   mid] [mid+1   end]两个区间
	int begin1 = begin, end1 = mid;
	int begin2 = mid + 1, end2 = end;
	int i = begin;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (a[begin1] < a[begin2])
		{
			tmp[i++] = a[begin1++];
		}
		else
		{
			tmp[i++] = a[begin2++];
		}
	}
	while (begin1 <= end1)
	{
		tmp[i++] = a[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[i++] = a[begin2++];
	}
	//合并后，拷贝回去  对应位置拷贝
	memcpy(a + begin, tmp + begin, sizeof(int) * (end-begin+1));

}

void _MergeSortNon(int* a, int begin, int end, int* tmp,int n)//非递归
{
	int gap = 1;//gap表示每次归并几个
	while (gap < n)
	{
		for (int i = 0; i < n; i += 2 * gap)
		{
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2 = i + 2 * gap - 1;
			int j = i;
			while (begin1 <= end1 && begin2 <= end2)
			{
				if (a[begin1] < a[begin2])
				{
					tmp[j++] = a[begin1++];
				}
				else
				{
					tmp[j++] = a[begin2++];
				}
			}
			while (begin1 <= end1)
			{
				tmp[j++] = a[begin1++];
			}
			while (begin2 <= end2)
			{
				tmp[j++] = a[begin2++];
			}
			//合并后，拷贝回去  对应位置拷贝
			memcpy(a + begin, tmp + begin, sizeof(int) * (end - begin + 1));
		}
		gap *= 2;
	}
}
void MergeSort(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	if (tmp == NULL)
	{
		perror("malloc");
		return;
	}
	/*_MergeSort(a,0,n-1,tmp);*/
	_MergeSortNon(a,0,n-1,tmp, n);
	free(tmp);
}
int main()
{
	int a[] = { 9,8,7,6,5,4,3,2};
	int n = sizeof(a) / sizeof(a[0]);
	MergeSort(a,n);
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	return 0;
}