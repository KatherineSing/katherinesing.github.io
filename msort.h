#include <vector>
#include "tweet.h"

template <class T, class Compare>
void mergesort(std::vector<T>& mylist, Compare comp);
template <class T, class Compare>
void msort(std::vector<T>& mylist,int start, int end, Compare comp);
template <class T, class Compare>
void merge(std::vector<T>& mylist,
int s, int m, int e, Compare comp);

template <class T, class Compare>
void mergesort(std::vector<T>& mylist, Compare comp)
{
	msort(mylist, 0, mylist.size()-1, comp);
}

template <class T, class Compare>
void msort(std::vector<T>& mylist,int start, int end, Compare comp)
{
	// base case
	if(start < end)
	{
		// recursive calls
		int mid = (start+end)/2;
		msort(mylist, start, mid, comp);
		msort(mylist, mid+1, end, comp);
		// merge
		merge(mylist, start, mid, end, comp);
	}
}

template <class T, class Compare>
void merge(std::vector<T>& mylist,
int s, int m, int e, Compare comp)
{
	//compare the elements from each index range
	//to each other
	int i, j, k; //indices
	int size1 = m - s + 1;
	int size2 = e - m;

	//create temp vectors
	std::vector<T> v1;
	std::vector<T> v2;
	//copy data into the temp vectors
	for (i = 0; i < size1; i++)
	{
		v1.push_back(mylist[s + i] );
	}
	for (j = 0; j < size2; j++)
	{
		v2.push_back(mylist[m + 1 + j] );
	}

	//merge the temp arrays back into mylist[s1...e2]
	i = 0;
	j = 0;
	k = s;

	while(i < size1 && j < size2)
	{
		if(comp(v1[i], v2[j]) == true) //then v2[j]<v1[i], v1[i] is later
		{
			mylist[k] = v1[i];
			i++;
		}
		else
		{
			mylist[k] = v2[j];
			j++;
		}
		k++;
	}

	//if elements in v1 remain, copy them over
	while(i < size1)
	{
		mylist[k] = v1[i];
		i++;
		k++;
	}

	//if elements in v2 remain, copy them over
	while(j < size2)
	{
		mylist[k] = v2[j];
		j++;
		k++;
	}
}