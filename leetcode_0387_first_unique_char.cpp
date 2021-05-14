#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <map>
using namespace std;

// Offer 50
int firstUniqueChar(char* s)
{
	int i;
	int ret = -1;
	int map[26] = {0};

	for (i = 0; i < strlen(s); i++) {
		map[s[i] - 'a'] ++;
	}

	for (i = 0; i < strlen(s); i++) {
		if (map[s[i] - 'a'] == 1) return i; 
	}

	return ret;
}

int firstUniqueCharMultimap(char* s)
{
	int i;
	int ret = strlen(s);
	multimap<char,int> map;
	multimap<char,int>::iterator it;

	for (i = 0; i < strlen(s); i++) {
		map.insert(pair<char,int>(s[i], i));
	}

	for (it = map.begin(); it!= map.end(); ++it) {
		if (map.count((*it).first) == 1 && (*it).second < ret) {
			ret = (*it).second;
		} 
	}

	return ret;
}

int main(int argc, char **argv)
{
    char array[] = "loveleetcode";

    printf("The \"%s\" first unique char index %d\n", array, firstUniqueChar(array));
    printf("The \"%s\" first unique char index multimap %d\n", array, firstUniqueCharMultimap(array));
}


