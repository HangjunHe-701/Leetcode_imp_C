#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>

/*
 * snprintf RETURN VALUE

    The functions snprintf() and vsnprintf() do not write more than size bytes (including the terminating null byte  ('\0')). 
	If the output was truncated due to this limit, then the return value is the number of characters (excluding the terminating null byte) which would have been written to the final string if enough space had been available.
	Thus, a return value of size or more means that the output was truncated. 
 */

char * reverseWords(char* s)
{
	int len = strlen(s);
	char *buf = malloc(len + 1);
	char *p = buf;
	int i = len - 1;
	int j;

	while (i > 0) {
		// remove extra blanks
		while (s[i] == ' ' && i > 0) {
			i--;
		}
		
		j = i;
		if (j == 0) return buf;

		while (s[i] != ' ' && i > 0) {
			i--;
		}

		if (i == 0) {	
			if (s[i] != ' ')
				snprintf(p, j-i+1+1, "%s", &s[i]);
			else  
				snprintf(p, j-i+1, "%s", &s[i+1]);
		} else {
			snprintf(p, j-i+1+1, "%s ", &s[i+1]);
			p += j - i + 1;
		}
	}

	return buf;
}

static void reverseString(char *s) 
{
	int i = 0, j = strlen(s) - 1;
	char ch;
printf("%s\n", s);
	while (j > i) {
		ch = s[i];
	    s[i] = s[j];	
		s[j] = ch;
		j--; i++;
	}
}

char * leetcode557_reverseWords(char* s)
{
	int i;
	int j = 0;
	char *p = s, *q;

	while (p) {
		q = strchr(p, ' ');
		// the last word
		if (q == NULL) {
			reverseString(p);
			return s;
		}

		*q = '\0';
		reverseString(p);
		*q = ' ';

		p = q + 1;
	}

	return s;
}

int main(int argc, char **argv)
{
    char array[] = " man    man, a   plan,  a canal: Panama ";
    //char array[] = "race a car";
	char * buf;

	buf = reverseWords(array);
    printf("The \"%s\" reverse to \"%s\"\n", array, buf);
    printf("The \"%s\" reverse to \"%s\"\n", buf, leetcode557_reverseWords(buf));
	free (buf);
}


