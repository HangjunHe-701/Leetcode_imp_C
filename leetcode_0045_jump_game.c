#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h"

static int jump(int nums[], int n)
{
	int i, canReach = 0, needChoose = 0;
	int step = 0;

	if (n == 1) return 0;

	for (i = 0; i < n -1; i++) {
		
		if (i + nums[i] > canReach) {
			canReach = i + nums[i];

			if (canReach >= n - 1) {
				return step + 1;
			}
		}
		// greed
		if (i == needChoose) {
			needChoose = canReach;
			step ++;
		}
	}

	return step;	
}

static bool canJump(int nums[], int n)
{
	int i, canReach = 0, needChoose = 0;
	int step = 0;

	if (n == 1) return 0;

	for (i = 0; i < n -1; i++) {
		
		if (i + nums[i] > canReach) {
			canReach = i + nums[i];

			if (canReach >= n - 1) {
				return true;
			}
		}
		// greed
		if (i == needChoose) {
			// canReach no update, can't move forward
			if (needChoose == canReach) {
				return false;
			}
			needChoose = canReach;
			step ++;
		}
	}

	return false;	
}

static bool canJump2(int nums[], int n)
{
	int i, maxJump= 0;

	if (n == 1) return true;

	for (i = 0; i < n; i++) {
		
		if (i > maxJump)
			return false;

		maxJump = MAX(maxJump, i+nums[i]);
	}

	return true;	
}

int main(int argc, char **argv)
{
	int array[] = {2,3,1,1,4};
	int array2[] = {3,2,1,0,4};

	printf ("The mimimul steps is %d\n", jump(array, 5));
	printf ("can jump %d\n", canJump(array, 5));
	printf ("can jump2 %d\n", canJump2(array, 5));
}
