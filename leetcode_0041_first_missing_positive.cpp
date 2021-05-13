#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <map>
#include <vector>
using namespace std;

int firstMissingPositive(int nums[], int n)
{
	int i, ret;
	map<int,int> map1;
	
	for (i = 0; i < n; i++) {
		//map1.insert(pair<int,int>(nums[i], i));
		map1.insert(map<int,int>::value_type(nums[i], i));
	}

	// max is n !!!
	for (i = 1; i <= n; i++) {
		if (map1.find(i) == map1.end()) {
			ret = i;
			goto out;
		}
	}

	// not missing, return the next larger integer
	ret = n+1; 

out:
	return ret;
}

int firstMissingPositive2(vector<int> & nums)
{
	int i, ret;
	
	for(i = 0; i < nums.size(); ++i) { 
		while (nums[i] > 0 && nums[i] <= nums.size() &&
				nums[i] != nums[nums[i] - 1]) {
			swap(nums[i], nums[nums[i] - 1]);
		}
	}

	for (i = 0; i < nums.size(); ++i) { 
		if (nums[i] != i + 1)
			return i+1;
	}
	
	return nums.size() + 1;
}

int main(int argc, char **argv)
{
	int array[] = {3,4,-1,1};
	int ret;
	vector<int> v = {7,8,9,11,12};
	//vector<int> v = {3,4,-1,1};

	printf ("The first missing positive is %d\n", firstMissingPositive(array, 4));
	printf ("The first missing positive2 is %d\n", firstMissingPositive2(v));
}
