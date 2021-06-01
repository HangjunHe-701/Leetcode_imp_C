#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum {false=0, true=1} bool;

// 实现功能sprintf(s, "%d", i);
char *my_itoa(int n, char *s)
{
	char *p = s;
		
	//负号处理
	if (n < 0) {
		*p++ = '-';
		n = -n;
	}

	int wei = 1;
	int in = n;
	while (in /= 10) {
		wei ++;
	}

	in = n;
	for (int i = wei-1; i >= 0; i --) {
		
		p[i] = (in % 10) + '0';
		in /= 10;
	}

	p[wei] = '\0';
	return s;
}

char * my_strstr(char *s1, char *s2)
{
	bool flag = true;
	char *ps1, *ps2;
	
	if (s1 == NULL || s2 == NULL) return NULL;

	ps1 = s1;
	
	while (*ps1 != '\0') {
		flag = true;
		ps2 = s2;
		char *tmp_ps1 = ps1;

		while (*ps2 != '\0') {
			if (*(tmp_ps1++) != *(ps2++)) {
				flag = false;
				break;
			}
		}

		if (flag)
			return ps1;
		ps1++;
	}
	
	return NULL;
}

// 转无符号关键，结束符判断
int my_strcmp ( const char * src,const char * dst)
{        
	int ret = 0 ;        
	while( ! (ret = *(unsigned char *)src - *(unsigned char *)dst) && *dst){                
		++src;++dst;
	}        
#if 0
	if ( ret < 0 )                
		ret = -1 ;        
	else if ( ret > 0 )                
		ret = 1 ;  
#endif
	return( ret );
}

char *my_strcpy(char *d, char *s)
{
    char *tmp = d;
    while((*d++ = *s++) != '\0');

    return tmp;
}

/*
算法思路：

1、把两个字符串分别以行和列组成一个二维矩阵。
2、比较二维矩阵中每个点对应行列字符中否相等，相等的话值设置为1，否则设置为0。
3、通过查找出值为1的最长对角线就能找到最长公共子串。
*/
char * common_string(char *str1, char *str2) 
{
	int maxLen = 0, maxEnd = 0;	
	int s1_len = strlen(str1);
	int s2_len = strlen(str2);
	int record[s1_len][s2_len];
	char *strbuf;
	
	for (int i = 0; i < s1_len; ++i) {
		
		for (int j = 0; j < s2_len; ++j) {
			
			if (str1[i] == str2[j]) {
				
				if (i == 0 || j == 0) {					
					record[i][j] = 1;				
				} else {					
					record[i][j] = record[i - 1][j - 1] + 1;				
				}			
			} else {				
				record[i][j] = 0;			
			} 
			
			if (record[i][j] > maxLen) {				
				maxLen = record[i][j];				
				maxEnd = i; //若记录i,则最后获取LCS时是取str1的子串			
			}		
		}	
	}

	strbuf = (char*)malloc(s1_len + 1);
	memcpy(strbuf, str1 + maxEnd - maxLen + 1, maxLen);
	strbuf[maxLen] = '\0';
	return strbuf;
}

// No extra space needed
char * common_string2(char *str1,char *str2)
{
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int i,j,k;
	int max = 0;
	int start = -1;
	char *strbuf = (char*)malloc(len1 + 1);
	 
	for (i = 0; i < len1; i++){
		for (j = 0; j < len2; j++){
			if (str1[i] == str2[j]){
				for (k = 0; (str1[i+k] == str2[j+k] && str1[i+k] != '\0'); k++);
				
				if (max < k){
					max = k;
					start = i;
				}
			}
		}
	}
	 
	if (start == -1){
		strbuf[0] = '\0';
	} else {
		memcpy(strbuf, str1 + start, max);
		strbuf[max] = '\0';
	}

	return strbuf;
}

// 连续字符的最大长度
int  length_of_a_char_string(char *str)
{
	char *p = str;
	char c = *p;
	int i;
	int max_cnt = 0, cnt = 0;

	while (*p != '\0') {
		
		if (c == *p)  {
			cnt ++;
			if (cnt > max_cnt) max_cnt = cnt;
		} else {
			c = *p;
			cnt = 1;
		}

		p++;
	}

	return max_cnt;
}

// 字符串reverse
char * exchange(char *str) 
{    
	char tmp;    
	int len, i, j;     
	len = strlen(str);
	
	for(i = 0, j = len-1; i != len/2; i++, j--) 
	{       
		tmp = str[i];       
		str[i] = str[j];       
		str[j] = tmp;    
	}  

	return str; 
}

int my_toupper (int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 'a' - 'A';

	return c;
}


static bool isContained(const char *str, char c)
{  
	if (str == NULL)  {	return false;  }  
	
	const char *p = str;  
	while (*p != '\0')  {	
		if (*p == c)	
		{	  
			return true;	
		}	
		p++;  
	}  
	return false;
}

char *my_strtok_r(char* string_org, const char* delim, char **save_ptr)
{
	char *str = NULL;			

	if (delim == NULL) {
		return NULL;
	}

	if (string_org == NULL && *save_ptr == NULL)
	{
		return NULL;
	}

#if 1
	//put demial into map, delete duplicated char
	const char *ctrl = delim;
	char map[255] = {0};  
	size_t len = 0;  
	while (*ctrl != '\0')  
	{	
		if (isContained(map, *ctrl))	
		{	  
			ctrl++; 
			continue;	
		}	
		map[len] = *ctrl;	
		len++;	
		ctrl++; 
	}
#else
	const char *map = demial;
#endif

	printf ("map %s\n", map);

	if (string_org == NULL) {
		str = *save_ptr;
	} else {
		str = string_org;
	}

	//first non demial
	while(*str != '\0')
	{
		if (isContained(map, *str))
		{
			str++;
			continue;
		}
		break;
	}
	if  (*str == '\0') {
		*save_ptr = NULL;
		return NULL;
	}

	string_org = str;    //first demail
	while (*str)  {	
		if (isContained(map, *str))	
		{	  
			*str++ = '\0'; 
			break;	
		}	
		str++; 
	} 
	*save_ptr = str; 
	return string_org;  
}
  			

char *my_strtok(char* string_org,const char* delim)
{
	  static char *last = NULL; //to keep remainning str
	  return my_strtok_r(string_org, delim, &last);

}


int main ()
{
	int s[] = {1, 2, 3, 4, 4, 5, 5, 6, 7, 8};
	int hit, k;
	

	printf ("\n A- a = %d hello %c\n", 'A' - 'a', my_toupper('a'));

	printf ("\nmy_strstr = %s", my_strstr("123hello77", "hello")); 

	char buffer[10];
	printf ("\nmy_itoa = %s", my_itoa(12345, buffer));


	char input_str[] = "11123hello77";
	printf ("\ncommon_string = %s", common_string(input_str, "a23hello"));
	printf ("\ncommon_string2 = %s", common_string2(input_str, "a23hello"));
	printf ("\nexchange= %s", exchange(input_str));
	printf ("\nlength_of_a_char_string %s = %d\n", input_str, length_of_a_char_string(input_str));


	char input[] = "asdfsasdadfas34";
	char *p = my_strtok(input, "asas");
	//printf ("my %s\n", strtok(input, ","));
	printf ("Token: %s\n", p);

	while ((p = my_strtok(NULL, "asas")))
		printf ("Token: %s\n", p);
	
	return 0;
}


