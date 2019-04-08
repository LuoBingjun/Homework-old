#include <iostream>
#include <random>
#include <time.h>

using namespace std;

const int n = 200000000;//10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 200000000
unsigned A[n];
unsigned L[n/2 + 2];
unsigned R[n/2 + 2];

void get_random(unsigned A[], int n)
{
	random_device rd;
	uniform_int_distribution<unsigned> dist(0, numeric_limits<unsigned>::max());
	for (int i = 0; i < n; i++)
		A[i] = dist(rd);
}

void insertion_sort(unsigned A[],int n)
{
	for (int i = 0; i < n; i++)
	{
		int key = A[i];
		int j = i;
		for (; j > 0; j--)
		{
			if (key >= A[j - 1])
				break;
			A[j] = A[j - 1];
		}
		A[j] = key;
	}
}

void shell_sort(unsigned A[], int n)
{
	int gap, i, j;
	for (gap = n/2; gap > 0; gap /= 2)
		for (i = gap; i < n; i++)
		{
			int temp = A[i];
			for (j = i - gap; j >= 0 && A[j] > temp; j -= gap)
				A[j + gap] = A[j];
			A[j + gap] = temp;
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
			swap(A[i],A[j]);
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
		quick_sort(A, p, q - 1);
		quick_sort(A, q + 1, r);
	}
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

unsigned* radix_sort(unsigned A[], int n)
{
	unsigned* B = new unsigned[n];
	int r = log2(n);
	int k = 1 << r;
	int p = ceil(32.0 / r);
	unsigned x = k - 1;
	unsigned* C = new unsigned[k];
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < k; j++)
			C[j] = 0;
		for (int j = 0; j < n; j++)
		{
			unsigned a = (A[j] >> (i*r)) & x;
			C[a]++;
		}
		for (int j = 1; j < k; j++)
			C[j] = C[j] + C[j - 1];

		//cout << endl << "C:";
		//for (int j = 0; j < k; j++)
		//{
		//	cout << C[j] << ' ';
		//}

		for (int j = n - 1; j >= 0; j--)
		{
			unsigned a = (A[j] >> (i*r)) & x;
			C[a]--;
			B[C[a]] = A[j];
		}

		//cout << endl << "B:";
		//for (int j = 0; j < n; j++)
		//{
		//	cout << B[j] << ' ';
		//}

		//cout << endl << "A:";
		//for (int j = 0; j < n; j++)
		//{
		//	cout << A[j] << ' ';
		//}
		swap(A, B);
	}
	return A;
}

int main()
{
	int ns[] = { 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 200000000 };
	cout << "Insertion Sort:" << endl;
	cout << "n,time" << endl;
	for (auto n : ns)
	{
		get_random(A, n);
		unsigned start = clock();
		insertion_sort(A, n);
		unsigned end = clock();
		cout << n << ", " << (end - start) << endl;
	}
	cout << "Shellsort:" << endl;
	cout << "n,time" << endl;
	for (auto n : ns)
	{
		get_random(A, n);
		unsigned start = clock();
		shell_sort(A, n);
		unsigned end = clock();
		cout << n << ", " << (end - start) << endl;
	}
	cout << "Quicksort:" << endl;
	cout << "n,time" << endl;
	for (auto n : ns)
	{
		get_random(A, n);
		unsigned start = clock();
		quick_sort(A, 0, n - 1);
		unsigned end = clock();
		cout << n << ", " << (end - start) << endl;
	}
	cout << "Merge sort:" << endl;
	cout << "n,time" << endl;
	for (auto n : ns)
	{
		get_random(A, n);
		unsigned start = clock();
		merge_sort(A, 0, n - 1);
		unsigned end = clock();
		cout << n << ", " << (end - start) << endl;
	}
	cout << "Radix sort:" << endl;
	cout << "n,time" << endl;
	for (auto n : ns)
	{
		get_random(A, n);
		unsigned start = clock();
		radix_sort(A, n);
		unsigned end = clock();
		cout << n << ", " << (end - start) << endl;
	}
	return 0;
}