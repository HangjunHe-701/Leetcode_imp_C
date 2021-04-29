
typedef enum {false=0, true=1} bool;
 
typedef struct node {
	int 		data;
	struct node	*next;
} Node;

typedef struct head {
     size_t 		size;
     struct node	*next; // first
} node_head;

Node *CreateList(int n);
void free_list (Node * head); 
void ShowList(Node *head);
int get_list_length(Node * head);
Node * leetcode206_reverseList(Node *head); 
Node * middleNode2(Node *list);
Node * middleAndPrevNode(Node *list, Node **prev);
Node * leetcode21_mergeTwoLinks(Node *l1, Node *l2);
Node * leetcode876_middleNode(Node *list);
bool leetcode141_hasCycle(Node * head); 
