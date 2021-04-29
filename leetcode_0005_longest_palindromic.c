#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>
#include "misc.h"

// 解法一 Manacher's algorithm，时间复杂度 O(n)，空间复杂度 O(n)

// 解法二 滑动窗口，时间复杂度 O(n^2)，空间复杂度 O(1)
char * longest_palindromic_sub_string2(char* s)
{
	int left = 0, right = -1, pl = 0, pr = 0;
	int len = strlen(s);

	if (strlen(s) == 0) {
		return "";
	}

	while (left < len) {
		// 移动到相同字母的最右边（如果有相同字母）
		while (right+1 < len && s[left] == s[right+1]) {
			right++;
		}
		// 找到回文的边界
		while (left-1 >= 0 && right+1 < len && s[left-1] == s[right+1]) {
			left--;
			right++;
		}
		if (right-left > pr-pl) {
			pl = left;
			pr = right;	
		}
		// 重置到下一次寻找回文的中心
		left = (left+right)/2 + 1;
		right = left;
	}

	s[pr+1] = '\0';
	return &s[pl];
}

// 解法三 中心扩散法，时间复杂度 O(n^2)，空间复杂度 O(1)
// recursive
static char *getPalindromicSubStr(char *s, int i, int j, char * ret, char *tmp)
{
	if  (s[i] != s[j]) return ret;

	while (i >= 0 && j < strlen(s) && s[i] == s[j]) {
		i--; j++;
	}
	memcpy(tmp, &s[i+1], j - i + 1);
	tmp[j - i + 1] = '\0';
	
	if (strlen(tmp) > strlen(ret)) {
		strcpy(ret, tmp);
	}
	return ret;
}	

char * longest_palindromic_sub_string3(char* s)
{
	char * ret = strdup(s);
	char * tmp = strdup(s);
	// failure case not handled
	
	ret[0] = '\0';
	tmp[0] = '\0';
	for (int i = 0; i < strlen(s); i++) {
		ret = getPalindromicSubStr(s, i, i, ret, tmp);
		ret = getPalindromicSubStr(s, i, i+1, ret, tmp);
	}
	free(tmp);
	return ret;
}

static int getCountPalindromicSubStr(char *s, int i, int j)
{
	int count = 0;

	while (i >= 0 && j < strlen(s) && s[i] == s[j]) {
		count++;
		i--;j++;
	}
	return count;
}
int leetcode647_countPalindromicstring(char* s)
{
	char len = strlen(s);
	int  i, ret = 0;
	
	for (i = 0; i < strlen(s); i++) {
		ret += getCountPalindromicSubStr(s, i, i);
		ret += getCountPalindromicSubStr(s, i, i+1);
	}
	return ret;
}

static bool isChar(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}	
bool leetcode125_isPalindromic(char* s)
{
	int i = 0, j = strlen(s) - 1;

	while (j > i) {

		while (j > i && !isChar(tolower(s[i]))) i++;
		while (j > i && !isChar(tolower(s[j]))) j--;

		if (tolower(s[i]) != tolower(s[j]))
			return false;

		i++; j--;

	}
	return true;
}
int main(int argc, char **argv)
{
    //char array[] = "cbbd";
    //char array[] = "babad";
    char array[] = "bbbbbbbbb";
    char array2[] = "abc";

    char * result = longest_palindromic_sub_string2(array);
    printf("The longest palindromic subString 2 %s is: %s\n", array, result);

    result = longest_palindromic_sub_string3(array);
    printf("The longest palindromic subString 3 %s is: %s\n", array, result);
	free(result);

    int ret = leetcode647_countPalindromicstring(array2);
    printf("The total palindromic subString %s is: %d\n", array2, ret);

    char array3[] = "A man, a plan, a canal: Panama";
    //char array3[] = "race a car";

    printf("The \"%s\" is palindromic %d\n", array3, leetcode125_isPalindromic(array3));
}


