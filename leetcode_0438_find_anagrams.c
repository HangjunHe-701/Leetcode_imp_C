#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h" 

/*
这一题和第 438 题，第 3 题，第 76 题，第 567 题类似，用的思想都是"滑动窗口”。
 */

// 567 implementation is better
int* leetcode438_findAnagrams(char* s, char* t, int *n)
{
	int left = 0, right = 0;
	int len = strlen(s);
	int lenT = strlen(t);
	int count = 0;
    int mapT[256];
	int start = 0;
	int * ret = NULL;

    if (len == 0) return 0;

    memset(mapT, 0, sizeof(int) * 256);
	for (int i = 0; i < lenT; i++) {
		mapT[t[i]]++;	
	}

	// max number string len 
	ret = malloc(sizeof(int)*len);
	//failure not handled
	memset(ret, 0, sizeof(int)*len);

	while (right < len) {

		if (mapT[s[right]] > 0) {
			count++;	
		}
		mapT[s[right]]--; 

		if (count == lenT) {
			ret[start] = left;
			start++;
		}
		if (right - left == lenT - 1) {
			// move left
			if (mapT[s[left]] >= 0) {
				count --;
			}

			mapT[s[left]]++; 
			left++;
		}

		right++;
	}

	*n = start;
	return ret;
}

// better one
bool leetcode567_checkInclusion(char* s, char* t)
{
	int left = 0, right = 0;
	int len = strlen(s);
	int lenT = strlen(t);
	int count = lenT;
    int mapS[256];

    if (len == 0) return 0;

    memset(mapS, 0, sizeof(int) * 256);
	for (int i = 0; i < lenT; i++) {
		mapS[t[i]]++;	
	}

	while (right < len) {

		if (mapS[s[right]] >= 1) {
			count--;
		}
		
		mapS[s[right]] --;

		if (count == 0)
			return true;

		right ++;

		if (right - left == lenT - 1) {
			mapS[s[left]] --;
			if (mapS[s[left]] >= 1)
				count++;

			left++;
		}
	}

	return false;
}

int main(int argc, char **argv)
{
    //char array[] = "cbaebabacd";
    //char t[] = "abc";
    char array[] = "abab";
    char t[] = "ab";
	int i = 0;
	int n = 0;

    int * result = leetcode438_findAnagrams(array, t, &n);
    printf("The anagrams\n");
	while (i < n) {
		printf("%d\t", result[i]);
		i++;
	}
    printf("\n");
	free(result);

    bool ret = leetcode567_checkInclusion(array, t);
    printf("%s %s check Inclusion %d\n", array, t, ret);
}


