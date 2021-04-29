#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h" 

char* reverseString(char* s)
{
	int i = 0, j = strlen(s) - 1;
	char ch;

	while (j > i) {
		ch = s[j];
		s[j] = s[i];
		s[i] = ch;
		i++;j--;
	}
	return s;
}

static char* __reverseString(char* s, int k)
{
	int i = 0, j = k - 1;
	char ch;

	while (j > i) {
		ch = s[j];
		s[j] = s[i];
		s[i] = ch;
		i++;j--;
	}
	return s;
}

char* leetcode541_reverseString(char* s, int k)
{
	int i = 0, len = strlen(s);
	char ch;

	if (k == 1) return s;

	for (i = 0; i < len; i += 2*k) {
		if (len - i <= k) {
			__reverseString(&s[i], len - i);	
		} else {
			/* reverse k */	
			__reverseString(&s[i], k);
		}
	}

	return s;
}

char* leetcode541_reverseString2(char* s, int k)
{
	int i = 0, len = strlen(s);
	char ch;

	if (k == 1) return s;

	while (i < len) {
		if (len - i <= k) {
			__reverseString(&s[i], len - i);	
			break;
		}
		/* reverse k */	
		__reverseString(&s[i], k);
		i += k;

		if (len - i <= k)
			break;
		i += k;
	}

	return s;
}

static bool isVowel(char c)
{
	return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
			c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

char* leetcode345_reverseVowels(char* s)
{
	int i = 0, j = strlen(s) - 1;
	char ch;


	while (j > i) {

		while (!isVowel(s[j]) && j > i) j--;
		while (!isVowel(s[i]) && j > i) i++;

		if (j <= i) break;

		ch = s[j];
		s[j] = s[i];
		s[i] = ch;
		i++;j--;
	}

	return s;
}

int main(int argc, char **argv)
{
    char array[] = "abcdefog";
    char array2[] = "leetcode";
	int k = 2;

    printf("The \"%s\" reverse to ", array);
    printf("%s\n", reverseString(array));

    printf("The \"%s\" k %d reverse to:\n", array, k);
    printf("\t%s\n", leetcode541_reverseString(array, k));

    printf("The \"%s\" reverse vowels to:\n", array);
    printf("\t%s\n", leetcode345_reverseVowels(array));
}


