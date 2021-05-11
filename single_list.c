 #include <stdlib.h>
 #include <stdio.h>
 #include "single_list.h" 

 void free_list (Node * head) 
 {
	 Node * p = head;
	 Node * next;
		 
	 if (head == NULL) return;
 
	 while (p) {
		 next = p->next;
		 free (p);
		 p = next;
	 }
	 return;
 }
 
 //Create
 Node *CreateList(int n)
 {
     int i;
     Node *head,*p,*q;
	 Node *hit = NULL;
 
     head = NULL;
 
     for (i = 0; i < n; i++) {
        p = (Node*)malloc(sizeof(Node));
		if (!p) { 
			free_list(head);
			return NULL;
		}
#if 1
#if 1		
#if 1
		if (i%2 == 1)
			p->data = i;
		else
#endif
			p->data = i+1;
#else
		p->data = random() % 2;
#endif
#endif
#if 0 //palindrome
		if (i >= 5 )
			p->data = 9-i;
		else
			p->data = i+1;
#endif

		// has Cycle
		//if (i == 5) hit = p;

        if (head == NULL)
             head = p;
        else
             q->next = p;
         q = p;
     }
	 
     p->next = hit;
     return head;
 }

 //p不是最后一个结点, O(1)
void Delete_none_last_Node(Node * p)
{
	if(p == NULL || p->next == NULL)
		return;
	Node *temp_next = p->next;
	p->data = temp_next->data;
	p->next = temp_next->next;
	free(temp_next);
	temp_next = NULL;
	return;
}

 // find 最大 值的Node,	O(n)
 int find_max(Node *head)
 {
 	Node *p, *pre;
	int max;
	
 	if (head == NULL) return -1;

	pre = p = head;
	max = p->data;

	while (p) {
		if (p->data > max) {
			max = p->data;
		}
		pre = p;
		p = p->next;
	}
	return max;
 }

// 找到倒数N个Node
 int find_last_n_node (Node *head, int n)
{
	Node * p, *q;

	p = q = head;

	while (--n >= 0) {
		p = p->next;
	}

	while (p->next) {
		p = p->next;
		q = q->next;
	}

	return q->data;
}

Node *leetcode206_reverseList(Node *head) 
{
	Node *p, *next, *r;
	p = head;

	r = NULL;

	while (p) {
		next = p->next;
		p->next = r;
		r = p;
		p = next;
	}

	return r;
}

// 删除最小 值的Node,	O(n), 唯一
Node * Delete_Min(Node **phead)
{
	Node *head = *phead;
	Node *pre = head, *p = head;	//p 为工作指针，pre 指向其前驱
	Node *minpre = NULL, *minp = head;  //保存最小值结点及其前驱

	while (p) {
		if (p->data < minp->data){
			minp = p;	//找到比之前找到的最小值结点更小的结点
			minpre = pre;
		}
		pre = p;  //继续扫描下一个结点
		p = p->next;
	}

	if (minpre == NULL) {
		*phead = head->next;
	} else { 
		minpre->next = minp->next; 
	}

	free(minp);
	return head;
}



static Node * get_last_node(Node * head)
{
	Node * p = head;

	if (!head) return NULL;

	while (p && p->next) {
		p = p->next;
	}

	return p;
}

int get_list_length(Node * head)
{
	Node * p = head;
	int n = 0;

	while (p) {
		p = p->next;
		n++;
	}

	return n;
}

// Display
void ShowList(Node *head)
{
	Node *p = head;
	int count = 0;

	while (p) {
		printf("%d ", p->data);
		p = p->next;
		count ++;
		// aviod loop
		if (count == 99)
			break;
	}
	if (count == 0) {
		printf("Empty list\n");
		return;
	}
	printf("\n");
	printf("Total %d numbers\n", count);
}

Node * leetcode876_middleNode(Node *list)
{
	Node *fast = list, *slow = list; 
	int n;

	if (!list || !list->next)
		return list;
	
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}
#if 0
	//even
	if (fast == NULL)
		slow = slow->next;
#endif

	return slow;
}

// return middle node
Node * middleAndPrevNode(Node *list, Node **prev)
{
	Node *fast = list, *slow = list; 
	int n;

	if (!list || !list->next)
		return list;
	
	while (fast && fast->next) {
		*prev = slow;
		slow = slow->next;
		fast = fast->next->next;
	}

	return slow;
}

// create a loop
Node *CrossOfList(Node * plist1, Node * plist2)
{
	   Node *last1;

	   if (plist1 == NULL || plist2 == NULL) return NULL;

	   last1 = get_last_node(plist1);
	   last1->next = plist2;

	   //return leetcode141_hasCycle(plist1);
	   return NULL;
}

/*
	 * 面试题37：两个链表的第一个公共结点 题目：输入两个链表，找出他们的第一个公共结点。
	 * 
	 * 从定义可以看出，这是单向链表。如果有公共结点，之后他们的所有结点都是重合的，不可能分叉，拓扑形状像一个Y而不是X。
	 * 思路1：可以把两个链表的结点放入两个栈，这样两个链表的尾结点就是栈顶，接下来比较栈顶结点是否相同。
	 * 直到找到最后一个相同的结点。空间复杂度和时间复杂度都是O(m+n).
	 * 思路2：首先遍历两个链表得到它们的长度，得出哪个链表较长，长几个结点。第二次遍历的时候，
	 * 较长的链表先走若干步，接着同时遍历两个链表，找到第一个相同的结点就是第一个公共结点。
	 * 
	 * 首先定义一个返回链表长度的方法
	 */

Node *CrossOfList2(Node * head1, Node * head2)
{
	unsigned int n1, n2, diff;
	Node * p1, *p2;
	Node * lList, *sList;

	if (head1 == NULL || head2 == NULL) return NULL; 

	p1 = get_last_node(head1);
	n1 = get_list_length(head1);
	p2 = get_last_node(head2);
	n2 = get_list_length(head2);

	if (p1 != p2) {
		return NULL;
    }

	diff = (n1 > n2) ? (n1 - n2) : (n2 - n2);
	lList = (n1 > n2) ? head1 : head2;
	sList = (n1 > n2) ? head2 : head1;

	p1 = lList;
	while (diff-- == 0) {
		p1 = p1->next;
	}

	p2 = sList;
	while (p1 && p2 && p1 != p2) {
		p1 = p1->next;
		p2 = p2->next;
	}

	return p1;
}

