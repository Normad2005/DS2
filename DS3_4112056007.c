#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int z, x, y;
    char val;
    bool visited;
    struct Node* neighbors[6];
    struct Node* next;
} Node;

Node* front = NULL;
Node* rear = NULL;

void enqueue(Node* n) {
    n->next = NULL;
    if (rear) {
        rear->next = n;
    } else {
        front = n;
    }
    rear = n;
}

Node* dequeue() {
    if (!front) return NULL;
    Node* temp = front;
    front = front->next;
    if (!front) rear = NULL;
    return temp;
}

bool isEmpty() {
    return front == NULL;
}

int zdir[6] = {1, -1, 0, 0, 0, 0};
int xdir[6] = {0, 0, 1, -1, 0, 0};
int ydir[6] = {0, 0, 0, 0, 1, -1};
Node* nodes[32][32][32];

int main(){
    FILE *fin = fopen("testcase3.txt", "r");
    FILE *fout = fopen("output3.txt", "w");
    int hei, row, col;

    while(fscanf(fin, "%d %d %d", &hei, &row, &col)==3 && (hei||row||col)){
        fgetc(fin);

        Node* start = NULL;
        Node* end = NULL;

        for(int h=0;h<hei;h++){
            for(int r=0;r<row;r++){
                for(int c=0;c<col;c++){
                    char ch;
                    fscanf(fin, " %c", &ch); 
                    Node* n = (Node*)malloc(sizeof(Node));
                    n->z = h;
                    n->x = r;
                    n->y = c;
                    n->val = ch;
                    n->visited = false;
                    for (int i = 0; i < 6; i++) n->neighbors[i] = NULL;
                    n->next = NULL;
                    nodes[h][r][c] = n;
                    if(ch=='S') start = n;
                    if(ch=='E') end = n;
                }
                fgetc(fin);
            }
            fgetc(fin);
        }

        for(int h=0;h<hei;h++){
            for(int r=0;r<row;r++){
                for(int c=0;c<col;c++){
                    if(nodes[h][r][c]->val!='#'){
                        for(int dir=0;dir<6;dir++){
                            int nh = h+zdir[dir];
                            int nr = r+xdir[dir];
                            int nc = c+ydir[dir];
                            if(nh>=0 && nh<hei && nr>=0 && nr<row && nc>=0 && nc<col) {
                                if(nodes[nh][nr][nc]->val!='#') {
                                    nodes[h][r][c]->neighbors[dir] = nodes[nh][nr][nc];
                                }
                            }
                        }
                    }
                }
            }
        }

        // BFS
        int cnt = 0;
        bool flag = false;
        front = rear = NULL;
        start->visited = true;
        enqueue(start);
        while(!isEmpty()){
            int size = 0;
            Node* ptr = front;
            while(ptr){
                size++;
                ptr = ptr->next;
            }

            for(int i=0;i<size;i++){
                Node* cur = dequeue();
                if(cur==end) {
                    flag = true;
                    break;
                }
                for(int d=0;d<6;d++){
                    Node* nb = cur->neighbors[d];
                    if (nb && !nb->visited) {
                        nb->visited = true;
                        enqueue(nb);
                    }
                }
            }

            if(flag) break;
            cnt++;
        }

        if(flag){
            fprintf(fout, "Escaped in %d step(s).\n", cnt);
        }
        else{
            fprintf(fout, "Trapped!\n");
        }

        for (int h=0; h<hei;h++){
            for (int r=0;r<row;r++){
                for (int c=0;c<col;c++){
                    free(nodes[h][r][c]);
                }
            }
        }
    }
    fclose(fin);
    fclose(fout);
    return 0;
}
