#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/*
可以看作一个动态规划的问题，

首先，如果第一位上是0，那么无法转码，返回0；
其次，每次转码，都可以看看第i位跟第i-1位的数字是否小于等于26，如果符合的话，我们在i-2位上解码；
	如果第i位不等于0的话，说明我们相当于在第i-1位上解码。
	如果两个都符合，相当于：dp[i] = dp[i-1] + dp[i-2];
*/
int numDecodings(char *s)
{
	int i, len;
	int * dp;
	int ret;

	if (s == NULL) return 0;
	
	len = strlen(s);
	if (s[0] == '0' && len == 1)
		return 0;

	dp = malloc(sizeof(int) * len);
	memset(dp, 0, sizeof(int) * len);
	
	dp[0] = (s[0] == '0') ? 0 : 1;
	if (s[0] > '0' && s[1] > '0') dp[1] += 1;
	if ((s[0] == '1' || s[0] == '2') && s[1] <= '6') dp[1] += 1;
	
	for (i = 2; i < len; i++) {
		if (s[i] != '0') 
			dp[i] += dp[i-1];

		if ((s[i-1] == '1' || s[i-1] == '2') && s[i] <= '6')
			dp[i] += dp[i-2];
	}

	ret = dp[len - 1];
	free(dp);
	return ret;
}

// Offer 46
int offer46_numDecodings(char *s)
{
	int i, len;
	int * dp;
	int ret;

	if (s == NULL) return 0;
	
	len = strlen(s);

	dp = malloc(sizeof(int) * len);
	memset(dp, 0, sizeof(int) * len);
	
	dp[0] = 1;
	dp[1] = 1;
	if ((s[0] == '1' || s[0] == '2') && s[1] <= '5') dp[1] += 1;
	
	for (i = 2; i < len; i++) {
		dp[i] += dp[i-1];

		if ((s[i-1] == '1' || s[i-1] == '2') && s[i] <= '5')
			dp[i] += dp[i-2];
	}

	ret = dp[len - 1];
	free(dp);
	return ret;
}

int main(int argc, char **argv)
{
	char s[] = "102268";
	int ret = numDecodings(s);

	printf("%s number decoding %d\n", s, ret);

	ret = offer46_numDecodings(s);
	printf("%s offer-46 number decoding %d\n", s, ret);
}
