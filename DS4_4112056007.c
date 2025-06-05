#include <stdio.h>
#include <stdlib.h>

typedef struct Node* NodePtr;
typedef struct Node {
    int order, num;
    NodePtr next, prev;
}Node;

struct LinkedList {
    NodePtr head;
}Cards;

int* deleted;
int idx;

NodePtr newNode(int order, int num){
    NodePtr temp = malloc(sizeof(Node));
    temp->order = order;
    temp->num = num;
    temp->next = temp->prev = NULL;
    return temp;
}

void delNode(NodePtr node){
    deleted[idx++] = node->order;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
}

int GCD(int a, int b) {
	if (b) while((a %= b) && (b %= a));
	return a + b;
}

int main(){
    FILE *fin = fopen("testcase.txt", "r");
    freopen("fuck.txt", "w", stdout);

    int t, m, a, removed, preG, curG;
    NodePtr lastNode, temp, cur, prev;

    fscanf(fin, "%d", &t);
    while (t--){    
        fscanf(fin, "%d", &m);
        deleted = malloc(sizeof(int) * m);
        idx = 0;

        Cards.head = newNode(0, -1);
        lastNode = Cards.head;
        for (int i = 1; i <= m; i++){
            fscanf(fin, "%d", &a);
            temp = newNode(i, a);
            temp->prev = lastNode;
            lastNode->next = temp;
            lastNode = temp;
        }
        lastNode->next = Cards.head;
        Cards.head->prev = lastNode;

        removed = 2;
        preG = 0;
        cur = Cards.head->next->next;
        while (removed > 0 && cur->next->next != cur){
            removed -= 1;
            while (cur != Cards.head){
                prev = cur->prev == Cards.head ? cur->prev->prev : cur->prev;
                curG = GCD(prev->num, cur->num);
                if (curG == preG && curG > 1) {
                    cur = cur->next;
                    delNode(cur->prev);
                    removed = 1;
                }else {
                    cur = cur->next;
                    preG = curG;
                }
            }
            cur = cur->next;
        }

        printf("%d ", idx);
        for (int i = 0; i < idx; i++)
            printf("%d ", deleted[i]);
        putchar('\n');

        for (cur = Cards.head->next; cur != Cards.head; ){
            temp = cur;
            cur = cur->next;
            free(temp);
        }
        free(Cards.head);
        free(deleted);
    }

    fclose(fin);
    return 0;
}
