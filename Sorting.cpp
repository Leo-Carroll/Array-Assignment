#include "Sorting.h"

static void Swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

static void InsertionSort(Vector<int>& vec, int left, int right) {
	for (int i = left + 1; i <= right; ++i) {
		int key = vec[i];
		int j = i - 1;
		while (j >= left && vec[j] > key) {
			vec[j + 1] = vec[j];
			--j;
		}
		vec[j + 1] = key;
	}
}

static int Partition(Vector<int>& vec, int low, int high) {
	int pivot = vec[high];
	int i = low - 1;

	for (int j = low; j <= high - 1; ++j) {
		if (vec[j] <= pivot) {
			++i;
			Swap(vec[i], vec[j]);
		}
	}
	Swap(vec[i + 1], vec[high]);
	return i + 1;
}

static void Heapify(Vector<int>& vec, int n, int i, int start) {
	int largest = i;
	int l = 2 * (i - start) + 1 + start;
	int r = 2 * (i - start) + 2 + start;

	if (l < n && vec[l] > vec[largest]) {
		largest = l;
	}
	if (r < n && vec[r] > vec[largest]) {
		largest = r;
	}
	if (largest != i) {
		Swap(vec[i], vec[largest]);
		Heapify(vec, n, largest, start);
	}
}

static void HeapSort(Vector<int>& vec, int start, int end) {
	int n = end - start + 1;
	for (int i = start + n / 2 - 1; i >= start; --i) {
		Heapify(vec, end + 1, i, start);
	}
	for (int i = end; i > start; --i) {
		std::swap(vec[start], vec[i]);
		Heapify(vec, i, start, start);
	}
}

static int* MedianOfThree(int* aPtr, int* bPtr, int* cPtr) {
	int a = *aPtr;
	int b = *bPtr;
	int c = *cPtr;

	if (a < b && b < c) {
		return bPtr;
	}
	if (a < c && c <= b) {
		return cPtr;
	}
	if (b <= a && a < c) {
		return aPtr;
	}
	if (b < c && c <= a) {
		return cPtr;
	}
	if (c <= a && a < b) {
		return aPtr;
	}
	if (c <= b && b <= a) {
		return bPtr;
	}
	return nullptr;
}

static void IntrosortUtil(Vector<int>& vec, int start, int end, int maxDepth) {
	int size = end - start + 1;

	if (size <= 16) {
		InsertionSort(vec, start, end);
		return;
	}

	if (maxDepth == 0) {
		HeapSort(vec, start, end);
		return;
	}

	int pivot = Partition(vec, start, end);
	IntrosortUtil(vec, start, pivot - 1, maxDepth - 1);
	IntrosortUtil(vec, pivot + 1, end, maxDepth - 1);
}

void Introsort(Vector<int>& vec, int start, int end) {
	int maxDepth = static_cast<int>(2 * std::log(vec.Size()));
	IntrosortUtil(vec, start, end, maxDepth);
}

void ReverseVector(Vector<int>& vec) {
	int start = 0;
	int end = vec.Size() - 1;
	while (start < end) {
		Swap(vec[start++], vec[end--]);
	}
}
