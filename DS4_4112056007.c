#include<stdio.h>
#include<stdlib.h>
typedef enum{false, true} bool;

typedef struct Node{
	int order, num;
	struct Node *next, *prev;
}Node;

typedef struct LinkedList{
	struct Node *head;
}LinkedList;

Node *createNode(int order, int num){
	Node *n = (Node *)malloc(sizeof(Node));
	n->next = NULL;
	n->prev = NULL;
	n->order = order;
	n->num = num;
	return n;
}

void deleteNode(LinkedList *l, Node *deleted){
	deleted->prev->next = deleted->next;
	deleted->next->prev = deleted->prev;
	if(deleted == l->head)
		l->head = l->head->next;
}

int gcd(int a, int b){
	int r = a%b;
	if(!r)
		return b;
	else
		return gcd(b, r);
}

void insertNode(Node *node, Node *n){
	n->next = node->next;
	n->prev = node;
	node->next->prev = n;
	node->next = n;
}

FILE *fin, *fout;

void sol() {
    int ans[1000], ans_idx = 0;
    int n, a;
    fscanf(fin, "%d", &n);
    fscanf(fin, "%d", &a);

    LinkedList *l = (LinkedList *)malloc(sizeof(LinkedList));
    l->head = createNode(1, a);
    l->head->next = l->head;
    l->head->prev = l->head;

    Node *cur = l->head;
    for (int i = 2; i <= n; i++) {
        fscanf(fin, "%d", &a);
        Node *new_node = createNode(i, a);
        insertNode(cur, new_node);
        cur = cur->next;
    }
    
    cur = l->head;
    while (n > 1) {
        bool removed = false;
        Node *p = cur;
        int last_gcd = gcd(p->prev->num, p->num);
        int cnt = n; // 保證掃一圈最多 n 次

        while (cnt--) {
            Node *next = p->next;
            int new_gcd = gcd(p->num, next->num);
            if (new_gcd == last_gcd && new_gcd > 1) {
                ans[ans_idx++] = next->order;
                deleteNode(l, next);
                n--;
                removed = true;
                last_gcd = gcd(p->num, p->next->num);  // 更新下一對 GCD
                // p 不動，繼續比較
            } else {
                p = p->next;
                last_gcd = gcd(p->prev->num, p->num);
            }
        }
        if (!removed)
            break;
    }

    fprintf(fout, "%d", ans_idx);
    for (int i = 0; i < ans_idx; i++)
        fprintf(fout, " %d", ans[i]);
    fprintf(fout, "\n\n");
}

int main(){
	fin = fopen("testcase3.txt", "r");
	//fout = fopen("output3.txt", "w");
	int tc;
	fscanf(fin, "%d", &tc);
	while(tc--){
		sol();
	}
	return 0;
}
