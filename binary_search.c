#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef  enum {false=0, true=1} bool;


// sorted, may be not unique 
int binarysearch(int nums[], int n, int key)
{ 
	int mid;
	int low = 0, high = n-1;

	while (low <= high)
	{ 
		mid = low + (high - low) / 2; 
		//mid = low + (high - low) >> 1; 
		
		if (nums[mid] == key) 
			return mid; 
		else if (nums[mid] > key) 
			high = mid - 1; 
		else 
			low = mid + 1; 
	} 
	// not found
	return -1; 
}

// sorted 
int binarysearchLessSmall(int nums[], int n, int key)
{ 
	int mid;
	int low = 0, high = n-1;

	while (low <= high)
	{ 
		mid = low + (high - low) / 2; 
		//mid = low + (high - low) >> 1; 
		
		if (nums[mid] == key) 
			return mid; 
		else if (nums[mid] > key) 
			high = mid - 1; 
		else { 
			if (nums[mid+1] > key) {
				return mid;
			}
			low = mid + 1; 
		}
	} 
	// not found
	return -1; 
}

// sorted, may be not unique 
int binarysearchFirstEqual(int nums[], int n, int key)
{ 
	int mid;
	int low = 0, high = n-1;

	while (low <= high)
	{
		mid = low + (high - low) / 2; 
		//mid = low + (high - low) >> 1; 
		
		if (nums[mid] == key) { 
			if (mid == 0 || nums[mid-1] != key)
				return mid; 
			high = mid - 1;
		} else if (nums[mid] > key)
			high = mid - 1;
		else
			low = mid + 1;
	}
	// not found
	return -1;
}

// sorted, may be not unique 
int binarysearchLastEqual(int nums[], int n, int key)
{ 
	int mid;
	int low = 0, high = n-1;

	while (low <= high)
	{
		mid = low + (high - low) / 2;
		//mid = low + (high - low) >> 1; 

		if (nums[mid] == key) {
			if  (mid + 1 == n ||  nums[mid+1] != key)
				return mid;
			low = mid + 1;
		} else if (nums[mid] > key)
			high = mid - 1;
		else
			low = mid + 1;
	}
	// not found
	return -1;
}

// sorted, may be not unique 
int binarysearchFirstGreater(int nums[], int n, int key)
{ 
	int mid;
	int low = 0, high = n-1;

	while (low <= high)
	{
		mid = low + (high - low) / 2; 
		//mid = low + (high - low) >> 1; 
		
		if (nums[mid] >= key) { 
			if (mid == 0 || nums[mid-1] < key) // �ҵ���һ�����ڵ��� target ��Ԫ��
				return mid; 
			high = mid - 1;
		else
			low = mid + 1;
	}

	// not found
	return -1;
}

// sorted, may be not unique 
int binarysearchLastLess(int nums[], int n, int key)
{ 
	int mid;
	int low = 0, high = n-1;

	while (low <= high)
	{
		mid = low + (high - low) / 2;
		//mid = low + (high - low) >> 1; 

		if (nums[mid] <= key) {
			if  (mid + 1 == n ||  nums[mid+1] > key) // �ҵ����һ��С�ڵ��� target ��Ԫ��
				return mid;
			low = mid + 1;
		else
			high = mid - 1;
	}

	// not found
	return -1;
}

//���ֲ���֮�ҵ�nums[lo, hi]���ڵ���keyֵ�ĵ�һ��Ԫ��λ��
int binarysearch_lower_bound(int nums[], int n, int key)
{ 
	int mid;
	int low = 0, high = n-1;
	
	while (low <= high) 
	{ 
		mid = low + (high - low) / 2; 
		//mid = low + (high - low) >> 1; 
		
		if (nums[mid] >= key) 
			high = mid - 1; 
		else 
			low = mid + 1; 
	} 

	//if (low >= n) low = -1;
	
	return low; 
}

//���ֲ���֮�ҵ��ϸ����keyֵ�ĵ�һ��Ԫ�� 
int binarysearch_upper_bound(int nums[], int n, int key)
{ 
	int mid;
	int low = 0, high = n-1;
	
	while (low <= high)
	{ 
		mid = low + (high - low) / 2; 
		//mid = low + (high - low) >> 1; 
		
		if (nums[mid] > key) 
			high = mid - 1; 
		else 
			low = mid + 1; 
	} 
	return low; 
}


//�ݹ�汾 
int binarysearch_firstoccur(int nums[], int low, int high, int key)
{ 
	if (low >== high) {
		return low; 
	}
	
	int mid = low + (high - low) / 2; 
	//int mid = low + (high - low) >> 1; 
	
	if (nums[mid] >= key) 
		return binarysearch_firstoccur(nums, low, mid-1, key); 
	if (nums[mid] < key) 
		return binarysearch_firstoccur(nums, mid + 1, high, key); 
}


int main ()
{
	int s[] = {1, 2, 3, 4, 4, 5, 5, 6, 7, 8};
	int hit, k;

	for (k = 0; k < 10; k++) {
		//hit = binarysearch(s, 8, k);
		printf ("binarysearch %d is position %d\n", k, hit);
	}

	for (k = 0; k < 10; k++) {
		//hit = binarysearch_lower_bound(s, 8, k);
		//printf ("binarysearch_lower_bound %d is position %d\n", k, hit);
	}

	for (k = 0; k < 10; k++) {
		//hit = binarysearch_firstoccur(s, 0, 8, k);
		//printf ("binarysearch_firstoccur %d is position %d\n", k, hit);
	}
	
	for (k = 0; k < 10; k++) {
		hit = binarysearch_upper_bound(s, 8, k);
		//printf ("binarysearch_upper_bound %d is position %d\n", k, hit);
	}

	return 0;
}

