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
static char check_valid(char c)
{
    if ((c>='a' && c<='z'))  return 'a';
    if ((c>='A' && c<='Z'))  return 'A';
    return '0';
}
void rec(char *s, int len, int index, char **ret, int *ret_index)
{
    int j;
    
    if (index < 0) return;

    /* get index-1 result */
    rec (s, len, index-1, ret, ret_index);
    
    /* set current resut */
    if (check_valid(s[index]) == '0') {
        /* index位为数字，s中字符放到index位置即可 */
        for (j = 0; j < *ret_index; j++){
            ret[j][index] = s[index];
        }
        return;
    } else {
        /* index位为字母，总数变为两倍，先为新增加的分配内存，并复制index位置之前的字符串，
         * 在index位置放置相应的字符，即大小写即可。
         */
        for (j = 0; j < *ret_index; j++) {
            ret[j][index] = s[index];

            ret[(*ret_index)+j] = (char *)malloc(sizeof(char) *(len+1));    
			ret[(*ret_index)+j][len] = '\0';
            memcpy(ret[(*ret_index)+j], ret[j], index);
            ret[(*ret_index)+j][index] = (check_valid(s[index]) == 'a' ? (s[index]-'a'+'A') : (s[index]-'A'+'a'));
        }
        (*ret_index) *= 2;
    }
}

char ** letterCasePermutation(char * S, int* returnSize)
{
    int len = strlen(S);
    char **ret = (char **)malloc(sizeof(char) * (1 << 12));
	// failure not handled
    int ret_index = 1;
    
    ret[0] = (char*)malloc(sizeof(char) * (len+1));
    ret[0][len] = '\0';
    
    rec(S, len, len-1, ret, &ret_index);
    
    *returnSize = ret_index;
    
    return ret;
    
}

int main(int argc, char **argv)
{
	char S[] = "a1b2";
	int size = 0;
	char ** ret = NULL;

	ret = letterCasePermutation(S, &size); 
	for (int i = 0; i < size; i++) {
		printf("%d: %s\n", i+1, ret[i]);
		free(ret[i]);
	}
	free(ret);
}
