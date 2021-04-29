#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h"

/*
用单调栈依次保存直方图的高度下标，
一旦出现高度比栈顶元素小的情况就取出栈顶元素，单独计算一下这个栈顶元素的矩形的高度。
然后停在这里(外层循环中的 i–，再 ++，就相当于停在这里了)，继续取出当前最大栈顶的前一个元素，即连续弹出 2 个最大的，以稍小的一个作为矩形的边，宽就是 2 计算面积…………
如果停在这里的下标代表的高度一直比栈里面的元素小，就一直弹出，取出最后一个比当前下标大的高度作为矩形的边。宽就是最后一个比当前下标大的高度和当前下标 i 的差值。
计算出面积以后不断的更新 maxArea 即可。
*/
int largestRectangleArea(int *heights, int n)
{
	int maxArea = 0, height, length;
	int * map;
	int i, tmp, map_index=0;

	map = malloc(sizeof(int) * n);
	memset(map, 0, sizeof(int)*n);

	// overflow range
	for (i = 0; i <= n; i++) {
		// the last operation
		if (i == n) {
			height = 0;
		} else {
			height = heights[i];
		}

		if (map_index == 0 || height >= heights[map[map_index-1]]) {
			map[map_index++] = i;
		} else {
			tmp = map[map_index-1];
			map_index--;
#if 0
			if (map_index == 0) {
				length = i;
			} else {
				length = i - 1 - map[map_index-1];
			}
#else
			length = i - tmp;
#endif
			maxArea = MAX(maxArea, heights[tmp]*length);
			// keep the position
			i--;
		}
	}

	return maxArea;
}

int main(int argc, char **argv)
{
	int array[] = {5,6,2,3};
	int n = sizeof(array)/sizeof(int);

	printf ("%d largest rectangle area %d\n", n, largestRectangleArea(array, n));
}
