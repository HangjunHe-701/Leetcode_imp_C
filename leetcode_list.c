 #include <stdlib.h>
 #include <stdio.h>
 #include "single_list.h" 

// recursive
Node *leetcode21_mergeTwoLinks(Node *l1, Node *l2)
{
	if (l1 == NULL) return l2;
	if (l2 == NULL) return l1;

	if (l1->data < l2->data) {
		l1->next = leetcode21_mergeTwoLinks(l1->next, l2);
		return l1;
	} 
	l2->next = leetcode21_mergeTwoLinks(l1, l2->next);
	return l2;
}


bool leetcode141_hasCycle(Node * head) 
{
	Node* slow = head, *fast = head;
	
 	while (fast && fast->next) {
		slow = slow->next;
 		fast = fast->next->next;
 		if (slow == fast)
 			return true;
 	}
	
 	return false;
}

Node * leetcode142_hasCycle2(Node * head) 
{
	Node * slow = head, *fast = head;
	
 	while (fast && fast->next) {
		slow = slow->next;
 		fast = fast->next->next;
 		if (slow == fast) {
 			break;
		}
 	}
	if (slow != fast)	
		return NULL;

	/* Cycle exists */
	slow = head;
	while (slow != fast) {
		slow = slow->next;
		fast = fast->next;
	}
	return slow;
}

// Delete nodes which value is x
Node * leetcode201_removeElements (Node * head, int x)
{
	Node *p, *prev = NULL, *remove;

	if (head == NULL) return NULL;

	p = head;

	while (p) {
		if (p->data == x) {
			if (prev == NULL) {
				head = p->next;	
			} else {
				prev->next = p->next;	
			}
			remove = p;
			p = p->next;
			free(remove);
			continue;
		}

		prev = p;
		p = p->next;
	}

	return head;
}
//
// use head
Node * leetcode201_removeElements2 (Node * head, int x)
{
	Node newHead;
	Node *p, *prev, *remove;

	if (head == NULL) return NULL;

	newHead.next = head;
	prev = &newHead;

	p = head;

	while (p) {
		if (p->data == x) {
			prev->next = p->next;	
			remove = p;
			p = p->next;
			free(remove);
			continue;
		}

		prev = p;
		p = p->next;
	}

	return newHead.next;
}

void main ()
{
    Node *l1, *l2, *ret;
 
    l1 = CreateList(9);
    l2 = CreateList(9);
    ShowList(l1);
    ShowList(l2);
	printf("has Cycle %d\n", leetcode141_hasCycle(l1));
	ret = leetcode142_hasCycle2(l1);
	printf("has Cycle %d\n", ret ? ret->data : 0);
	ShowList(l1);
	ret = leetcode201_removeElements2(l1, 5);
	ShowList(ret);
    free_list(ret);
    free_list(l2);
}
