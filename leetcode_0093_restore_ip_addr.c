#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

// DFS (deep forward searching) recursive
static int ret_index = 0;
void findRestoreIpAddresses(char *s, int index, char ** ret, int *ip_addr, int count)
{
	int temp;
	int len;

	// count and index both overflow
	if (count == 4) {
		if (index != strlen(s)) {
			// invalid
			return;
		}

		ret[ret_index] = malloc(16);
		len = sprintf(ret[ret_index], "%d.%d.%d.%d", ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3]);
		ret[ret_index][len] = '\0';
		
		ret_index ++;
		return;
	}

	// the first number
	ip_addr[count] = s[index] - '0';
	findRestoreIpAddresses(s, index+1, ret, ip_addr, count+1);	
	
	// two numbers
	ip_addr[count] = s[index] - '0';
	ip_addr[count] = ip_addr[count] * 10 + s[index+1] - '0';
	findRestoreIpAddresses(s, index+2, ret, ip_addr, count+1);	

	// three number
	temp = s[index] - '0';
	temp = temp * 10 + s[index+1] - '0';
	temp = temp * 10 + s[index+2] - '0';
	if (temp <= 255) {
		ip_addr[count] = temp;
		findRestoreIpAddresses(s, index+3, ret, ip_addr, count+1);
	}
}

char ** restoreIpAddresses(char* s, int *num)
{
	int i = 0;
	int ip_addr[4] = {0};

	if (s == NULL && s[0] == '0')
		return NULL;

	char** ret = malloc(sizeof(char *) * strlen(s));
	//int ret_index = 0;

	findRestoreIpAddresses(s, 0, ret, ip_addr, 0);
	*num = ret_index;
	return ret;
}

int main(int argc, char **argv)
{
	char array[] = "25525511135";
	char ** ret = NULL;
	int num = 0;

    ret = restoreIpAddresses(array, &num);
	for (int i = 0; i < num; i++) {
		printf("%d: %s\n", i+1, ret[i]);
		free(ret[i]);
	}
	free(ret);
}
