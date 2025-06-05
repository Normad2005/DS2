#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int digit;
    struct Node *next;
}Node;

Node *create_node(int value);
void reverse_list(Node *head);
Node *insert_node(Node *head, int n);
Node *multiple(Node *head, int n);


int main(){
    int n;
    FILE *fin = fopen("testcase1.txt", "r");
    FILE *fout = fopen("output1.txt", "w");
    while(fscanf(fin, "%d", &n) != EOF){
        Node *head = create_node(-1);
        int it;
        it = n;
        while(it>0){
            int a = it%10;
            it /= 10;
            head = insert_node(head, a);    
        }
    
        for(int i=n-1;i>1;i--){
            reverse_list(head);
            head = multiple(head, i);
            reverse_list(head);
        }
    
        Node *cur = head->next;
        fprintf(fout, "%d! = ", n);
        while(cur != NULL){
            fprintf(fout, "%d", cur->digit);
            cur = cur->next;
        }fprintf(fout, "\n");
    }
    
    fclose(fin);
    fclose(fout);
    
    return 0;
}

Node *create_node(int value){
    Node *new_node = malloc(sizeof(Node));
    if(new_node == NULL){
        printf("Memory allocation error\n");
        return NULL;
    }
    
    new_node->digit = value;
    new_node->next = NULL;
    return new_node;
}

Node *insert_node(Node *head, int n){
    Node *node = create_node(n);
    if(!node){
        printf("Error occured at insert_node\n");
        return NULL;
    }
    node->next = head->next;
    head->next = node;
    return head;
}

void reverse_list(Node *head) {
    Node *prev = NULL;
    Node *curr = head->next;
    Node *next = NULL;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    head->next = prev;
}

Node* multiple(Node *head, int n) {
    Node *result = create_node(-1); // dummy head for result
    Node *cur = head->next;
    int carry = 0;

    Node *tail = result;

    while (cur != NULL) {
        int mul = cur->digit * n + carry;
        int digit = mul % 10;
        carry = mul / 10;

        Node *new_node = create_node(digit);
        if (!new_node) {
            printf("Memory error in multiple\n");
            return NULL;
        }

        tail->next = new_node;
        tail = new_node;
        cur = cur->next;
    }
    while (carry > 0) {
        Node *new_node = create_node(carry % 10);
        if (!new_node) {
            printf("Memory error in multiple (carry)\n");
            return NULL;
        }
        tail->next = new_node;
        tail = new_node;
        carry /= 10;
    }

    return result;
}
