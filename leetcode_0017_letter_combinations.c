#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/*
 * 算法思想：
 * 使用递归的算法思想，将求len的问题转化为求len-1的问题，当len==0时，实际是有1个NULL字符串作为结果的。
 * 当len==1时，如果s[0]为数字，则返回结果数ret_index不变，否则变为2倍，并分配相应的内存处理。
 *
 */

char* letterMap[] = {
		" ",    //0
		"",     //1
		"abc",  //2
		"def",  //3
		"ghi",  //4
		"jkl",  //5
		"mno",  //6
		"pqrs", //7
		"tuv",  //8
		"wxyz", //9
};

static void findCombinations(char *s, int index, char **ret, int* ret_index, char *tmp)
{
	char * p = letterMap[s[index] - '0'];
	int len = strlen(s);
	int i;

	if (index == strlen(s)) {
		ret[*ret_index] = strdup(tmp);
		(*ret_index) ++;
		return;
	}

	for (i = 0; i < strlen(p); i++) {
		tmp[index] = p[i];
		findCombinations(s, index+1, ret, ret_index, tmp);
	}

}

char ** letterCombinations(char * S, int* returnSize)
{
    int len = strlen(S);
	int ret_index = 0;
    char **ret = (char **)malloc(sizeof(char) * (1 << 18));
	char *temp;
	// failure not handled

    temp = (char*)malloc(sizeof(char) * (len+1));
    temp[len] = '\0';
    
    findCombinations(S, 0, ret, &ret_index, temp);
    
    *returnSize = ret_index;
    
    return ret;
    
}

int main(int argc, char **argv)
{
	char S[] = "23";
	int size = 0;
	char ** ret = NULL;

	ret = letterCombinations(S, &size); 
	for (int i = 0; i < size; i++) {
		printf("%d: %s\n", i+1, ret[i]);
		free(ret[i]);
	}
	free(ret);
}
