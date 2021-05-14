#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/*
这一题和第 438 题，第 3 题，第 76 题，第 567 题类似，用的思想都是"滑动窗口”。

滑动窗口的右边界不断的右移，只要没有重复的字符，就持续向右扩大窗口边界。
一旦出现了重复字符，就需要缩小左边界，直到重复的字符移出了左边界，然后继续移动滑动窗口的右边界。
以此类推，每次移动需要计算当前长度，并判断是否需要更新最大长度，最终最大的值就是题目中的所求。
 */
int lengthOfLongestSubString(char* s, int * start)
{
	int left = 0, right = 0;
	int len = strlen(s);
	int longest = 0;
    char usedChar[256];

    if (len == 0) return 0;

    memset(usedChar, 0, sizeof(char) * 256);

	while (left < len - 1 && right < len - 1) {

        if (usedChar[s[right]] == 0) {
            usedChar[s[right]] ++;
            right ++;
            if (right - left > longest) {
                longest = right - left;
				*start = left; 
			}
        } else {
            usedChar[s[left]] --;
            left ++;
        }
	}

	return longest;
}

int main(int argc, char **argv)
{
    //char array[] = "abcabcbb";
    char array[] = "pwwkew";
    //char array[] = "bbbbbbbbb";
	int start;

    int result = lengthOfLongestSubString(array, &start);
    printf("The longest subString %s is: %d start_idx %d\n", array, result, start);
}


