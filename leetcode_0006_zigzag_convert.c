#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#if 0
leetcode题目永远描述不清不楚，zigzag 转换是 将一个Z字倒过来横着 排列
如一串字符 abcdefg， 我们先从其索引来排，
如果行数是2字符串坐标变成zigzag的走法就是：

0 2 4 6
1 3 5 7


如果行数是3字符串坐标变成zigzag的走法就是：

 0     4      8
 1  3  5  7   9
 2     6      10 


如果行数是4字符串坐标变成zigzag的走法就是：

 0      6        12
 1   5  7    11  13
 2 4    8 10     14
 3      9        15 

如果行数是5字符串坐标变成zigzag的走法就是：

0        8           16
1      7 9        15 17
2    6   10     14   18
3  5     11  13      19
4        12          20

char * zigzag_convert(char* s, int rows)
{
	matrix, down, up := make([][]byte, numRows, numRows), 0, numRows-2
	for i := 0; i != len(s); {
		if down != numRows {
			matrix[down] = append(matrix[down], byte(s[i]))
			down++
			i++
		} else if up > 0 {
			matrix[up] = append(matrix[up], byte(s[i]))
			up--
			i++
		} else {
			up = numRows - 2
			down = 0
		}
	}
	solution := make([]byte, 0, len(s))
	for _, row := range matrix {
		for _, item := range row {
			solution = append(solution, item)
		}
	}
	return string(solution)
}
#endif

char * zigzag_convert(char* s, int rows)
{
	char **matrix;
	int down= 0, up = rows -2;
	int i, j=0, k=0;
	int col = strlen(s);

	matrix = malloc (sizeof(char*) * rows);
	for (i = 0; i < rows; i++) {
		matrix[i] = (char *)malloc(col * sizeof(char));
		memset(matrix[i], 0, col);
	}

	for (i = 0; i < strlen(s); ) {
		if (down < rows) {
			matrix[down][j] = s[i];
			down++;
			i++;
		} else if (up > 0) {
			j++;
			matrix[up][j] = s[i];
			up--;
			i++;
		} else {
			j ++;
			up = rows - 2;
			down = 0;
		}
	}

	for (i = 0; i < rows; i++) 
	for (j = 0; j < col; j++) {
		if (matrix[i][j]) {
			s[k++] = matrix[i][j];
		}
	}
	// free
	for (i = 0; i < rows; i++) {
		free(matrix[i]);
	}
	free(matrix);
	return s;
}

int main(int argc, char **argv)
{
    //char array[] = "cbbd";
    //char array[] = "babad";
    char array[] = "PAYPALISHIRING";

    printf("The String is: %s\n", array);
    char * result = zigzag_convert(array, 3);
    printf("The zigzag String is: %s\n", result);
}


