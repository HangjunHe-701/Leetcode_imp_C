#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct node {
	int 		data;
	struct node	*next;
	struct node	*random;
} randomNode;

// Offer 35
randomNode *copyRandomList(randomNode *head)
{
    randomNode *newHead, *l1, *l2;

	if (head == NULL)
		return NULL;

    l1 = head; 
    // 节点后产生新节点   
    while (l1) {
        // 这一部分是经典的链表插入节点，new一个，新的后位指向旧的后位，
        // 旧的后位指向新节点，最后旧节点指向新的后位
        l2 = malloc(sizeof(randomNode));
		// failure not considered
        l2->random = NULL;
        l2->next = l1->next;
        l1->next = l2;
        l1 = l2->next;  //这一步也可以写为 l1=l1->next->next;
    }

    // 给新节点的random部分赋值
    for (l1 = head; l1; l1 = l1->next->next) {
        if (l1->random)
            l1->next->random = l1->random->next;
    }

	newHead = head->next;
    // 拆分
    for (l1 = head; l1; l1 = l1->next) {
        l2 = l1->next;
        l1->next = l2->next;
        if (l2->next)
            l2->next = l2->next->next;
    }
    return newHead;
}

int main(int argc, char **argv)
{
    randomNode *l1 = NULL, *ret;
 
    //l1 = CreateList(11);
    //ShowList(l1);
	ret = copyRandomList(l1);
	//ShowList(ret);
	//free_list(ret);	
}
