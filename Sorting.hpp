#pragma once

#include <cmath>
#include "Vector.h"

void Swap(int&, int&);

void InsertionSort(Vector<int>&, int, int);

int Partition(Vector<int>&, int, int);

void Heapify(Vector<int>&, int, int, int);

void HeapSort(Vector<int>&, int, int);

int* MedianOfThree(int*, int*, int*);

void IntrosortUtil(Vector<int>&, int, int, int);

void Introsort(Vector<int>&, int, int);

void ReverseVector(Vector<int>&);
