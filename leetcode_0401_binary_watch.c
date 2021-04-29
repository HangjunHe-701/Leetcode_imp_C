#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

var (
	hour    = []string{"1", "2", "4", "8"}
	minute  = []string{"01", "02", "04", "08", "16", "32"}
	hourMap = map[int][]string{
		0: []string{"0"},
		1: []string{"1", "2", "4", "8"},
		2: []string{"3", "5", "9", "6", "10"},
		3: []string{"7", "11"},
	}
	minuteMap = map[int][]string{
		0: []string{"00"},
		1: []string{"01", "02", "04", "08", "16", "32"},
		2: []string{"03", "05", "09", "17", "33", "06", "10", "18", "34", "12", "20", "36", "24", "40", "48"},
		3: []string{"07", "11", "19", "35", "13", "21", "37", "25", "41", "49", "14", "22", "38", "26", "42", "50", "28", "44", "52", "56"},
		4: []string{"15", "23", "39", "27", "43", "51", "29", "45", "53", "57", "30", "46", "54", "58"},
		5: []string{"31", "47", "55", "59"},
	}
)

func readBinaryWatch(num int) []string {
	if num > 8 {
		return []string{}
	}
	res := []string{}
	for i := 0; i <= num; i++ {
		for j := 0; j < len(hourMap[i]); j++ {
			for k := 0; k < len(minuteMap[num-i]); k++ {
				res = append(res, hourMap[i][j]+":"+minuteMap[num-i][k])
			}
		}
	}
	return res
}
int main(int argc, char **argv)
{
	int n = 15;
	int ret; 

	ret = integarReplace(n);
	printf("The interger %d replace count %d\n", n, ret);
}
