#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/*
构造一个 mask 遮罩，依次划过整个二进制字符串，每次滑动即取出遮罩遮住的 k 位二进制字符。
可以用 map 存储不同的二进制转换成的十进制数，最后判断 len(map) 是否等于 k 即可。
但是用 map 存比较慢，此处换成 bool 数组。先构造一个长度为 k 的数组，然后每次通过 mask 更新这个 bool 数组对应十进制的 bool 值，
并且记录剩余还缺几个二进制数。等剩余的等于 0 的时候，说明所有二进制字符串都出现了，直接输出 true，否则循环完以后输出 false。
*/
/*
 Constraints:
    1 <= s.length <= 5 * 10^5
    s consists of 0’s and 1’s only.
    1 <= k <= 20
*/
typedef enum {false=0, true=1} bool;

bool hasAllCodes(char *s, int k)
{
	int need = 1 << k;
	int mask = (1 << k) - 1;
	int sum = 0;
	bool * map = malloc(sizeof(bool) * need);
	memset(map, 0, sizeof(bool) * need);

	for (int i = 0; i < strlen(s); i ++) {
		sum = (sum << 1 | (s[i] - '0')) & mask;
		if (i >= k - 1) {
			if (map[sum] == false) {
				map[sum] = true;
				need--;
				if (need == 0)
					goto out;
			}
		}
	}

out:
	free(map);
	return need == 0;
}

int main(int argc, char **argv)
{
	//char s[] = "00110110";
	char s[] = "0000000001011100";
	int k = 4;
	printf ("%s has all code is %d\n", s, hasAllCodes(s, k));
}
