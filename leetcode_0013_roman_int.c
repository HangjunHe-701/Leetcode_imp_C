#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int char_to_num (char c) {
    if (c == 'M')
        return 1000;
    else if (c == 'D')
        return 500;
    else  if (c == 'C')
        return 100;
    else if (c == 'L')
        return 50;
    else  if (c == 'X')
        return 10; 
    else if (c == 'V')
        return 5;
    else  if (c == 'I')
        return 1;  
} 

int roman_int(char* s)
{
	int i = 0, prev = 0;
	int len = strlen(s);
	int sum = 0, temp;

    if (len == 0) return 0;

	while (s[i]) {

        temp = char_to_num(s[i]);
		if (temp <= prev) {
            sum += temp;
		} else {
            sum += temp;
            sum -= prev;
            sum -= prev;
        }
        prev = temp;
        i ++;
	}
	return sum;
}

int main(int argc, char **argv)
{
    //char array[] = "LVIII";
    char array[] = "MCMXCIV";

    int result = roman_int(array);
    printf("roman %s to integar is: %d a=%d A=%d\n", array, result, 'a', 'A');
}


