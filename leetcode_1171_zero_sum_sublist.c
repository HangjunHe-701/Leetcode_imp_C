// build with single_list.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "single_list.h"


/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */

// 解法一
func removeZeroSumSublists(head *ListNode) *ListNode {
	// 计算累加和，和作为 key 存在 map 中，value 存那个节点的指针。如果字典中出现了重复的和，代表出现了和为 0 的段。
	sum, sumMap, cur := 0, make(map[int]*ListNode), head
	// 字典中增加 0 这个特殊值，是为了防止最终链表全部消除完
	sumMap[0] = nil
	for cur != nil {
		sum = sum + cur.Val
		if ptr, ok := sumMap[sum]; ok {
			// 在字典中找到了重复的和，代表 [ptr, tmp] 中间的是和为 0 的段，要删除的就是这一段。
			// 同时删除 map 中中间这一段的和
			if ptr != nil {
				iter := ptr.Next
				tmpSum := sum + iter.Val
				for tmpSum != sum {
					// 删除中间为 0 的那一段，tmpSum 不断的累加删除 map 中的和
					delete(sumMap, tmpSum)
					iter = iter.Next
					tmpSum = tmpSum + iter.Val
				}
				ptr.Next = cur.Next
			} else {
				head = cur.Next
				sumMap = make(map[int]*ListNode)
				sumMap[0] = nil
			}
		} else {
			sumMap[sum] = cur
		}
		cur = cur.Next
	}
	return head
}

int main(int argc, char **argv)
{
    Node *l1, *l2;
	int g[]= {0,3, 1, 4};
	int ret;
 
    l1 = CreateList(11);
	//l2->data = 9;
    ShowList(l1);
	free_list(l1);	
}
