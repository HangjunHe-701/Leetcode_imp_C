#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/*
这一题和第 438 题，第 3 题，第 76 题，第 567 题类似，用的思想都是"滑动窗口”。

这一题是滑动窗口的题目，在窗口滑动的过程中不断的包含字符串 T，直到完全包含字符串 T 的字符以后，
记下左右窗口的位置和窗口大小。每次都不断更新这个符合条件的窗口和窗口大小的最小值。最后输出结果即可。
 */
char* minWindow(char* s, char* t)
{
	int left = 0, right = -1;
	int len = strlen(s);
	int lenT = strlen(t);
	int min = 0;
	int count = 0;
    int mapS[256];
    int mapT[256];
	int start;
	char * ret = NULL;

    if (len == 0) return 0;

    memset(mapS, 0, sizeof(int) * 256);
    memset(mapT, 0, sizeof(int) * 256);
	for (int i = 0; i < lenT; i++) {
		mapT[t[i]]++;	
	}

	while (left < len - 1) {

        if (count < lenT) {
			// to get min need recursive the whole string
			if (right >= len -1) {
				goto out;
			}
            mapS[s[right+1]] ++;
			if (mapS[s[right+1]] <= mapT[s[right+1]]) {
				count++;
			}

            right ++;
        } else {
			if ((count == lenT) && (!min || right - left < min)) {
				min = right - left + 1;
				start = left;
			}

			mapS[s[left]] --;
			if (mapS[s[left]] < mapT[s[left]])
				count--;

            left ++;
        }
	}

out:
	if (min) {
		ret = malloc(min+1);
		memcpy(ret, &s[start], min);
		ret[min] = '\0';
		printf ("start %d, min %d, %d %d %d %d\n", start, min, '0', 'a', s[start], s[start] - 'a');	
	}	
	return ret;
}

int main(int argc, char **argv)
{
    //char array[] = "abcabcbb";
    char array[] = "ADOBECODEBANC";
    char t[] = "ABC";

    char * result = minWindow(array, t);
    printf("The min subString %s in %s is: %s\n", t, array, result);
	free(result);
}


