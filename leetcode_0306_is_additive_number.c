#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h"

static int ret_index = 0;
static bool getsplitIntoFibonacci(char *s, int index, int ** ret, int * tmp, int tmp_index)
{
	int num = 0;
	int prevprev, prev;

	if (index == strlen(s)) {
		tmp[tmp_index] = 0;
		ret[ret_index] = malloc(sizeof(int) * strlen(s));
		memcpy(ret[ret_index], tmp, sizeof(int) * strlen(s));
		ret_index++;
		return true;
	}

	if (s[index] == '0')
		return false;

	prevprev = tmp[tmp_index - 2];
	prev = tmp[tmp_index - 1];
	while (index < strlen(s)) {
		num = num * 10 + s[index] - '0';
		if  (num  == prevprev + prev) {
			tmp[tmp_index] = num;
			return getsplitIntoFibonacci(s, index + 1, ret, tmp, tmp_index+1);
		} else if (num > prevprev + prev) {
			return false;
		}
		index ++;
	}

	return false;
}
int ** leetcode842_splitIntoFibonacci(char *s)
{
	int first = 0, second = 0;
	int firstEnd, secondEnd;
	char ch;
	int len = strlen(s);

	int ** ret = malloc(sizeof(int *) * len);
	int * temp = malloc(sizeof(int) * len);
	// failed

	if  (strlen(s) < 3) return false;

	for (firstEnd=1; firstEnd < strlen(s)/2; firstEnd++) {
		// 0 is valid, but 0x is invalid	
		if (s[0] == '0' && firstEnd > 1) break;

		first = first * 10 + s[firstEnd - 1] - '0';
		second = 0;

		for (secondEnd=firstEnd+1; MAX((secondEnd - firstEnd), firstEnd) <= (strlen(s)- secondEnd); secondEnd++) {

			if (s[firstEnd] == '0' && (secondEnd - firstEnd > 1)) break;

			second = second * 10 + s[secondEnd - 1] - '0';

			temp[0] = first;
			temp[1] = second;	   
			if (getsplitIntoFibonacci(s, secondEnd, ret, temp, 2) == true) {

			}
		}
	}

	free(temp);
	return ret;
}

static bool getAdditiveNumber(char *s, int first, int second, int index)
{
	int num = 0;

	if (index == strlen(s))
		return true;

	// the first char cound not be '0'
	if (s[index] == '0')
		return false;

	while (index < strlen(s)) {
		num = num * 10 + s[index] - '0';
		if  (num  == first + second) {
			return getAdditiveNumber (s, second, num, index + 1);
		} else if (num > first + second) {
			return false;
		}
		index ++;
	}

	return false;
}
bool isAdditiveNumber(char *s)
{
	int first = 0, second;
	int firstEnd, secondEnd;
	char ch;

	if  (strlen(s) < 3) return false;

	for (firstEnd=1; firstEnd < strlen(s)/2; firstEnd++) {
		// 0 is valid, but 0x is invalid	
		if (s[0] == '0' && firstEnd > 1) break;

		/*
		ch = s[firstEnd];
		s[firstEnd] = '\0';
		first = atoi(&s[0]);
		s[firstEnd] = ch;
		*/
		first = first * 10 + s[firstEnd-1] - '0';
		second = 0;

		// remainning numbers should more than first and second numbers
		for (secondEnd=firstEnd+1; MAX((secondEnd - firstEnd), firstEnd) <= (strlen(s)- secondEnd); secondEnd++) {

			if (s[firstEnd] == '0' && (secondEnd - firstEnd > 1)) break;
			/*
			ch = s[secondEnd];
			s[secondEnd] = '\0';
			second = atoi(&s[firstEnd]);
			s[secondEnd] = ch;
			*/
			second = second * 10 + s[secondEnd-1] - '0';

			if (getAdditiveNumber(s, first, second, secondEnd))
				return true;
		}
	}

	return false;
}
bool isAdditiveNumber2(char *s)
{
	int first = 0, second;
	int firstEnd, secondEnd;
	char ch;

	if  (strlen(s) < 3) return false;

	for (firstEnd=0; firstEnd < strlen(s)/2; firstEnd++) {
		// 0 is valid, but 0x is invalid	
		if (s[0] == '0' && firstEnd >= 1) break;

		first = first * 10 + s[firstEnd] - '0';
		second = 0;

		// remainning numbers should more than first and second numbers
		for (secondEnd=firstEnd+1; MAX((secondEnd - firstEnd), firstEnd) <= (strlen(s)- secondEnd); secondEnd++) {

			if (s[secondEnd] == '0' && (secondEnd - firstEnd > 1)) break;

			second = second * 10 + s[secondEnd] - '0';

			if (getAdditiveNumber(s, first, second, secondEnd+1))
				return true;
		}
	}

	return false;
}

static int fibonacci(int n)
{
	int Nminor2 = 1;
	int	Nminor1 = 2;
	int	N;

	for (int i = 2; i < n; i ++) {
		N = Nminor2 + Nminor1;
		// next round
		Nminor2 = Nminor1;
		Nminor1 = N;
	}
	return N;
}

int main(int argc, char **argv)
{
	//char s[] = "112358";
	char s[] = "199100199";
	int ** ret;

	// leetcode 306 test case
	printf("%s is additive number %d\n", s, isAdditiveNumber(s));
	printf("%s is additive number 2 %d\n", s, isAdditiveNumber2(s));

	ret = leetcode842_splitIntoFibonacci(s);
	for (int i = 0; i < ret_index;  i++) {
		printf("\n %d/%d list:\n", i+1, ret_index);
		int j = 0;
		while (ret[i][j]) {
			printf("%d\t", ret[i][j]);
			j ++;
		}
	}
	printf("\n");
	for (int i = 0; i < ret_index;  i++) {
		free(ret[i]);
	}
	free(ret);
}
