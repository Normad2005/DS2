#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {false, true} bool;

enum{down, up,
	front, back,
	left, right};

typedef struct Node{
	int z, x, y;
	char val;
	int visited;
	struct Node *neighbors[6];
	struct Node *next;
}Node;

Node *origin, *head, *tail;

Node *newNode(int z, int x, int y, char val){
	Node *n = (Node *)malloc(sizeof(Node));
	n->z = z;
	n->x = x;
	n->y = y;
	n->val = val;
	n->next = NULL;
	n->visited = 0;
	for(int i=0;i<6;i++)
		n->neighbors[i] = 0;
	return n;	 
} 

Node *find(int z, int x, int y){
	Node *temp = origin;
	while(y--) temp = temp->neighbors[right];
	while(x--) temp = temp->neighbors[back];
	while(z--) temp = temp->neighbors[up];
	return temp;
}

void enqueue(Node *node){
	if(tail) tail->next = node;
	tail = node;
	if(!head) head = tail;
}

Node *dequeue(){
	Node *temp = head;
	head = head->next;
	if(head == NULL) tail = NULL;
	return temp;
}

int isEmpty(){
	return !head;
}

int main(){
	FILE *fin = fopen("testcase69.txt", "r");
	//FILE *fout = fopen("eeoo.txt", "w");
	
	int h, r, c;
	char val;
	Node *temp, *start, *exit, *adj;
	while(fscanf(fin, "%d%d%d", &h, &r, &c) && (h||r||c)){
		head = tail = origin = NULL;
		for(int z=0;z<h;z++)
		for(int x=0;x<r;x++)
		for(int y=0;y<c;y++){
			do val = fgetc(fin);
			while(val != 'S' && val != 'E' && val != '#' && val != '.');
			
			temp = newNode(z, x, y, val);
			
			if(!(x||y||z)) origin = temp;
			if(temp->val == 'S') start = temp;
			else if(temp->val == 'E') exit = temp;
			
			if(z){
				adj = find(z-1, x, y);
				adj->neighbors[up] = temp;
				temp->neighbors[down] = adj;
			}
			if(x){
				adj = find(z, x-1, y);
				adj->neighbors[back] = temp;
				temp->neighbors[front] = adj;
			}
			if(y){
				adj = find(z, x, y-1);
				adj->neighbors[right] = temp;
				temp->neighbors[left] = adj;
			}
		}
		int found = 0;
		start->visited = 1;
		enqueue(start);
		while(!isEmpty()){
			temp = dequeue();
			if(temp->val == 'E'){
				printf("Escaped in %d step(s).\n", temp->visited-1);
				found = 1;
				break;
			}
			
			for(int i=0;i<6;i++){
				adj = temp->neighbors[i];
				if(adj == NULL || adj->visited || adj->val == '#') continue;
				adj->visited = temp->visited+1;
				enqueue(adj);
			}
		}
		
		if(!found)
			printf("Trapped!\n");
	}
	return 0;
}
