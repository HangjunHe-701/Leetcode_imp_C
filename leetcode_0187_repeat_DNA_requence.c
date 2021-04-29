#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


char* findRepeatDnsRequence(char *buffer) 
{
	int len;
	char subString[11];
	char *p;

	if (buffer == NULL)
		return NULL;

	len = strlen(buffer);
	if (len <= 10) return NULL;

	subString[10] = '\0';
	for (int i = 0; i < len - 10; i++) {
		strncpy(subString, &buffer[i], 10);
		if (strstr(&buffer[10+i], subString))
			printf("hit subString %s\n", subString);
	}
	return buffer;
}

static int charMap(char c)
{
	if (c == 'A')
		return 0;
	else if (c == 'C')
		return 1;
	else if (c == 'G')
		return 2;
	else
		return 3;
}

// bitops
char* findRepeatDnsRequenceII(char *s) 
{
	int len, i;
	unsigned int *mp, cur = 0;

	if (s == NULL)
		return NULL;

	len = strlen(s);
	if (len <= 10) return NULL;

	mp = malloc(sizeof(int)*0xFFFFF);
	//failed not considered
	memset(mp, 0, sizeof(int)*0xFFFFF);

	for (i = 0; i < 9; i++) { // 前9位
		cur = cur<<2 | charMap(s[i]);
	}
	for (i = 9; i < len; i++) {
		cur = ((cur << 2) & 0xFFFFF) | charMap(s[i]);
		if (mp[cur] == 0) {
			mp[cur] = 1;
		} else if (mp[cur] == 1) { // >2，重复
			char tmp = s[i+1];
			mp[cur] = 2;
			s[i+1] = '\0';
			printf("hit subString %s\n", &s[i-9]);
			s[i+1] = tmp;
			//result = append(result, s[i-9:i+1])
		}
	}
	free(mp);
	return s;
}

int main(int argc, char **argv)
{
	char string[] = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"; 
	char *ret;

	//ret = findRepeatDnsRequence(string);
	ret = findRepeatDnsRequenceII(string);
	printf("The element is %s\n", ret);
}
