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

 //p�������һ�����, O(1)
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

 // find ��� ֵ��Node,	O(n)
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

// �ҵ�����N��Node
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

// ɾ����С ֵ��Node,	O(n), Ψһ
Node * Delete_Min(Node **phead)
{
	Node *head = *phead;
	Node *pre = head, *p = head;	//p Ϊ����ָ�룬pre ָ����ǰ��
	Node *minpre = NULL, *minp = head;  //������Сֵ��㼰��ǰ��

	while (p) {
		if (p->data < minp->data){
			minp = p;	//�ҵ���֮ǰ�ҵ�����Сֵ����С�Ľ��
			minpre = pre;
		}
		pre = p;  //����ɨ����һ�����
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
	 * ������37����������ĵ�һ��������� ��Ŀ���������������ҳ����ǵĵ�һ��������㡣
	 * 
	 * �Ӷ�����Կ��������ǵ�����������й�����㣬֮�����ǵ����н�㶼���غϵģ������ֲܷ棬������״��һ��Y������X��
	 * ˼·1�����԰���������Ľ���������ջ���������������β������ջ�����������Ƚ�ջ������Ƿ���ͬ��
	 * ֱ���ҵ����һ����ͬ�Ľ�㡣�ռ临�ӶȺ�ʱ�临�Ӷȶ���O(m+n).
	 * ˼·2�����ȱ�����������õ����ǵĳ��ȣ��ó��ĸ�����ϳ�����������㡣�ڶ��α�����ʱ��
	 * �ϳ��������������ɲ�������ͬʱ�������������ҵ���һ����ͬ�Ľ����ǵ�һ��������㡣
	 * 
	 * ���ȶ���һ�����������ȵķ���
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

