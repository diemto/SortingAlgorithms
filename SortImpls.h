/* Author: Diem To
 * CSS 342 A - Fall 2014
 * Prof. Robert Dimpsey
 * Lab #4: Sorting
 * SortImpls.h consists of implementations of BubbleSort, InsertSort, MergeSort, IterativeMergeSort, and QuickSort.
 *
 * Merge is a helper function used in Recursive Merge Sort that merges two vectors.
 * Merge takes in 4 parameters: a reference to the orginal vector, the first index as an integer,
 * the middle index as an integer, and the last index as an integer.
 *
 * Interchange is a helper function used in Partition that swap the values of two indexes in an array.
 *
 * SortFirstMiddleLast is a helper function used in Partition that arranges the first, middle, and last entries
 * in an array into ascending order.
 *
 * Partition is a helper function used in QuickSort that partitions the array and returns the index of the pivot.
 *
 * BetterMerge is a helper function used in Iterative Merge Sort that merges two vectors.
 * BetterMerge takes in 5 parameters: a reference to the original vector, a reference to a temporary vector,
 * the first index as an integer, the middle index as an integer, and the last index as an integer.
 */

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

// BubbleSort
template <class ItemType>
void BubbleSort(vector<ItemType>& myVector, int first, int last)
{
	bool sorted = false;
	int pass = 1;
	while (!sorted && (pass < (last + 1)))
	{
		sorted = true;
		for (int index = 0; index < (last + 1 - pass); index++)
		{
			int nextIndex = index + 1;
			if (myVector[index] > myVector[nextIndex])
			{
				std::swap(myVector[index], myVector[nextIndex]);
				sorted = false;
			}
		}
		pass++;
	}
}

// InsertSort
template <class ItemType>
void InsertSort(vector<ItemType>& myVector, int first, int last)
{
	for (int unsorted = 1; unsorted < (last + 1); unsorted++)
	{
		ItemType nextItem = myVector[unsorted];
		int location = unsorted;
		while ((location > 0) && (myVector[location - 1] > nextItem))
		{
			myVector[location] = myVector[location - 1];
			location--;
		}
		myVector[location] = nextItem;
	}
}

// Merge
template <class ItemType>
void Merge(vector<ItemType>& myVector, int first, int middle, int last)
{
	vector<ItemType> tempVector(middle + last + 2);

	int first1 = first;
	int last1 = middle;
	int first2 = middle + 1;
	int last2 = last;

	int index = first1;
	while ((first1 <= last1) && (first2 <= last2))
	{
		if (myVector[first1] <= myVector[first2])
		{
			tempVector[index] = myVector[first1];
			first1++;
		}
		else
		{
			tempVector[index] = myVector[first2];
			first2++;
		}
		index++;
	}
	while (first1 <= last1)
	{
		tempVector[index] = myVector[first1];
		first1++;
		index++;
	}
	while (first2 <= last2)
	{
		tempVector[index] = myVector[first2];
		first2++;
		index++;
	}
	for (index = first; index <= last; index++)
	{
		myVector[index] = tempVector[index];
	}
}

// MergeSort
template <class ItemType>
void MergeSort(vector<ItemType>& vector, int first, int last)
{
	if (first < last)
	{
		int middle = first + (last - first) / 2;
		MergeSort(vector, first, middle);
		MergeSort(vector, middle + 1, last);
		Merge(vector, first, middle, last);
	}
}

// Interchange
template <class ItemType>
void Interchange(vector<ItemType>& vector, int index1, int index2)
{
	ItemType temp = vector[index1];
	vector[index1] = vector[index2];
	vector[index2] = temp;
}

// SortFirstMiddleLast
template <class ItemType>
void SortFirstMiddleLast(vector<ItemType>& vector, int first, int mid, int last)
{
	if (vector[first] > vector[mid])
	{
		Interchange(vector, first, mid);
	}
	if (vector[mid] > vector[last])
	{
		Interchange(vector, mid, last);
	}
	if (vector[first] > vector[mid])
	{
		Interchange(vector, first, mid);
	}
}

// Partition
template <class ItemType>
int Partition(vector<ItemType>& vector, int first, int last)
{
	int mid = first + (last - first) / 2;
	SortFirstMiddleLast(vector, first, mid, last);
	Interchange(vector, mid, last - 1);
	int pivotIndex = last - 1;
	int pivot = vector[pivotIndex];

	int indexFromLeft = first + 1;
	int indexFromRight = last - 2;

	bool done = false;
	while (!done)
	{
		while (vector[indexFromLeft] < pivot)
		{
			indexFromLeft++;
		}
		while (vector[indexFromRight] > pivot)
		{
			indexFromRight--;
		}
		if (indexFromLeft < indexFromRight)
		{
			Interchange(vector, indexFromLeft, indexFromRight);
			indexFromLeft++;
			indexFromRight--;
		}
		else
		{
			done = true;
		}
	}
	Interchange(vector, pivotIndex, indexFromLeft);
	pivotIndex = indexFromLeft;
	return pivotIndex;
}

// QuickSort
template <class ItemType>
void QuickSort(vector<ItemType>& vector, int first, int last)
{
	if ((last - first + 1) < 4)
	{
		InsertSort(vector, first, last);
	}
	else
	{
		int pivotIndex = Partition(vector, first, last);
		QuickSort(vector, first, pivotIndex - 1);
		QuickSort(vector, pivotIndex + 1, last);
	}
}

// BetterMerge
template <class ItemType>
void BetterMerge(vector<ItemType>& myVector, vector<ItemType>& tempVector, int first, int middle, int last)
{
	int first1 = first;
	int last1 = first + middle - 1;
	int first2 = first + middle;
	int last2 = last;

	int index = first1;
	while ((first1 <= last1) && (first2 <= last2))
	{
		if (myVector[first1] <= myVector[first2])
		{
			tempVector[index] = myVector[first1];
			first1++;
		}
		else
		{
			tempVector[index] = myVector[first2];
			first2++;
		}
		index++;
	}
	while (first1 <= last1)
	{
		tempVector[index] = myVector[first1];
		first1++;
		index++;
	}
	while (first2 <= last2)
	{
		tempVector[index] = myVector[first2];
		first2++;
		index++;
	}
	for (index = first; index <= last; index++)
	{
		myVector[index] = tempVector[index];
	}
}

// IterativeMergeSort
template <class ItemType>
void IterativeMergeSort(vector<ItemType>& myVector, int first, int last)
{
	vector<ItemType> tempVector(last + 1);
	int m = 1;
	while (m < (last + 1))
	{
		int i = 0;
		while (i < (last + 1 - m))
		{
			BetterMerge(myVector, tempVector, i, m, min(i+2*m-1, last));
			i = i + 2 * m;
		}
		m = m * 2;
	}
}