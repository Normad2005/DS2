#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int order, num;
    struct Node *next, *prev;
}Node;

typedef struct LinkedList{
    struct Node *head;
}LinkedList;

Node *createNode(int order, int num);
void insertNode(Node *node, Node *newNode);
void deleteNode(LinkedList *l, Node *deleted);
void printNode(LinkedList *l);
int gcd(int a, int b);

int ans[1000001];
int testcase = 0;
int main(){

    FILE *fin = fopen("testcase4.txt", "r");
    FILE *fout = fopen("output4.txt", "w");

    fscanf(fin, "%d", &testcase);
    while(testcase--){
        int m, input;
        int aid = 0;
        fscanf(fin, "%d", &m);
        fscanf(fin, "%d", &input);
        LinkedList *l = malloc(sizeof(LinkedList));
        l->head = createNode(1, input);
        l->head->next = l->head;
        l->head->prev = l->head;
        Node *pre = l->head;
        
        for(int i=1;i<m;i++){
            fscanf(fin, "%d", &input);
            Node *nd = createNode(i+1, input);
            insertNode(pre, nd);
            pre = nd;
        }
    
        int cnt = 0;
        while(m>2){
            int flag = 0;
            Node *cur = l->head->next;
            while(cur != l->head){
                if(gcd(cur->prev->num, cur->num) == gcd(cur->num, cur->next->num)){
                    if(gcd(cur->prev->num, cur->num) > 1){
                        flag = 1;
                        ans[aid++] = cur->next->order;
                        deleteNode(l, cur->next);
                        m--;
                        cnt++;
                    }
                }
                else{
                    cur = cur->next;
                }
            }
            if(gcd(cur->prev->num, cur->num) == gcd(cur->num, cur->next->num)){
                if(gcd(cur->prev->num, cur->num) > 1){
                    flag = 1;
                    ans[aid++] = cur->next->order;
                    deleteNode(l, cur->next);
                    m--;
                    cnt++;
                }
            }
            if(!flag || m <= 2){
                break;
            }
        }
    
        if(m == 2){
            ans[aid++] = l->head->next->order;
            deleteNode(l, l->head->next);
            cnt++;
        }
    
        fprintf(fout, "%d ", cnt);
        for(int i=0;i<aid;i++){
            fprintf(fout, "%d ", ans[i]);
        }fprintf(fout, "\n");
    
    }

    fclose(fin);
    fclose(fout);

    return 0;
}

Node *createNode(int order, int num){
    Node *node = malloc(sizeof(Node));
    if(node == NULL){
        printf("Memory allocation failed\n");
        return NULL;
    }
    node->order = order;
    node->num = num;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

void insertNode(Node *node, Node *newNode){
    newNode->prev = node;
    newNode->next = node->next;
    node->next->prev = newNode;
    node->next = newNode;
    return;
}

void deleteNode(LinkedList *l, Node *deleted){
    deleted->prev->next = deleted->next;
    deleted->next->prev = deleted->prev;
    if(deleted == l->head){
        l->head = l->head->next;
    }
    free(deleted);
}

void printNode(LinkedList *l){
    Node *cur = l->head;
    printf("%d:%d ", cur->order, cur->num);
    for(cur=l->head->next; cur!=l->head ;cur = cur->next){
        printf("%d:%d ", cur->order, cur->num);
    }printf("\n");
}

int gcd(int a, int b){
    int r = a%b;
    if(r == 0)
        return b;
    else
        return gcd(b, r);
}