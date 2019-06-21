#include <iostream>
#include <random>
#include <time.h>
#include <omp.h>

using namespace std;

const int n = 10000000;//10, 100, 1000, 10000, 100000, 1000000
unsigned A[n];
unsigned L[n / 2 + 2];
unsigned R[n / 2 + 2];

void get_random(unsigned A[], int n)
{
	random_device rd;
	uniform_int_distribution<unsigned> dist(0, numeric_limits<unsigned>::max());
//#pragma omp parallel for
	for (int i = 0; i < n; i++)
		A[i] = dist(rd);
}

void merge(unsigned A[], int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	for (int i = 0; i < n1; i++)
		L[i] = A[p + i];
	for (int i = 0; i < n2; i++)
		R[i] = A[q + i + 1];
	L[n1] = R[n2] = UINT32_MAX;

	int i = 0, j = 0;
	for (int k = p; k <= r; k++)
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

void merge_sort(unsigned A[], int p, int r)
{
	if (p < r)
	{
		int q = (p + r) / 2;
		merge_sort(A, p, q);
		merge_sort(A, q + 1, r);
		merge(A, p, q, r);
	}
}

void merge_sort_parallel(unsigned A[], int p, int r)
{
	int size = r - p;
	int step = 1;
	while (step <= size)
	{
#pragma omp parallel for
		for (int i = p; i < r; i += 2 * step)
		{
			if (i + 2 * step - 1 <= r)
			{
				merge(A, i, i + step - 1, i + 2 * step - 1);
			}
			else if (i + step - 1 < r)
			{
				merge(A, i, i + step - 1, r);
			}
		}
		step = step * 2;
	}
}

int partition(unsigned A[], int p, int r)
{
	int pivot = A[r];
	int i = p - 1;
	for (int j = p; j < r; j++)
	{
		if (A[j] <= pivot)
		{
			i++;
			swap(A[i], A[j]);
		}
	}
	swap(A[r], A[i + 1]);
	return i + 1;
}

void quick_sort(unsigned A[], int p, int r)
{
	if (p < r)
	{
		int q = partition(A, p, r);
		{
			quick_sort(A, p, q - 1);
			quick_sort(A, q + 1, r);
		}
	}
}

void quick_sort_parallel(unsigned A[], int p, int r)
{
	if (p < r)
	{
		int q = partition(A, p, r);
#pragma omp parallel sections
		{
#pragma omp section
			quick_sort_parallel(A, p, q - 1);
#pragma omp section
			quick_sort_parallel(A, q + 1, r);
		}
	}
}

void quick_sort_new_parallel(unsigned A[], int p, int r)
{
	int q0 = partition(A, p, r);
	int q[4] = { partition(A, p, q0 - 1),  q0, partition(A, q0 + 1, r) };
#pragma omp parallel sections
	{
#pragma omp section
		quick_sort(A, p, q[0] - 1);
#pragma omp section
		quick_sort(A, q[0] + 1, q[1] - 1);
#pragma omp section
		quick_sort(A, q[1] + 1, q[2] - 1);
#pragma omp section
		quick_sort(A, q[2] + 1, r);
	}
}

int main()
{	
	int time = 0;
	for(int i = 1; i <= 5; i++)
	{
		get_random(A, n);
		unsigned start = clock();
		merge_sort(A, 0, n - 1);
		unsigned end = clock();
		time += (end - start);
	}
	cout << "Merge sort:" << time / 5 << endl;

	time = 0;
	for (int i = 1; i <= 5; i++)
	{
		get_random(A, n);
		unsigned start = clock();
		quick_sort(A, 0, n - 1);
		unsigned end = clock();
		time += (end - start);
	}
	cout << "Quick sort:" << time / 5 << endl;

	time = 0;
	for (int i = 1; i <= 5; i++)
	{
		get_random(A, n);
		unsigned start = clock();
		merge_sort_parallel(A, 0, n - 1);
		unsigned end = clock();
		time += (end - start);
	}
	cout << "Parallel merge sort:" << time / 5 << endl;

	time = 0;
	for (int i = 1; i <= 5; i++)
	{
		get_random(A, n);
		unsigned start = clock();
		quick_sort_parallel(A, 0, n - 1);
		unsigned end = clock();
		time += (end - start);
	}
	cout << "Parallel quick sort:" << time / 5 << endl;

	time = 0;
	for (int i = 1; i <= 5; i++)
	{
		get_random(A, n);
		unsigned start = clock();
		quick_sort_new_parallel(A, 0, n - 1);
		unsigned end = clock();
		time += (end - start);
	}
	cout << "Parallel new quick sort:" << time / 5 << endl;
	return 0;
}