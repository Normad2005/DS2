#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct  MemberNode{
    int id;
    struct MemberNode *next;
}MemberNode;

typedef struct TeamNode{
    int teamID;
    MemberNode *front;
    MemberNode *rear;
    struct TeamNode *next;
}TeamNode;

TeamNode *create_TeamNode(int teamID);
MemberNode *create_MemberNode(int id);
TeamNode *enqueue(TeamNode *team, int id);
MemberNode *dequeue(TeamNode *team);

// void print_all_teams(TeamNode *head) {
//     TeamNode *curTeam = head->next;
//     printf("=== ALL DATA ===\n");
//     while (curTeam != NULL) {
//         printf("Team %d: ", curTeam->teamID);
//         MemberNode *curMember = curTeam->front;
//         while (curMember != NULL) {
//             printf("%d ", curMember->id);
//             curMember = curMember->next;
//         }
//         printf("\n");
//         curTeam = curTeam->next;
//     }
//     printf("================================\n");
// }

int arr[1000000];

int main(){
    FILE *fin = fopen("testcase2.txt", "r");
    FILE *fout = fopen("output2.txt", "w");
    int n, tc = 1;
    while(1){
        fscanf(fin, "%d", &n);
        if(!n)
            break;
        for(int i=0;i<n;i++){
            int num, p;
            fscanf(fin, "%d", &num);
            for(int j=0;j<num;j++){
                fscanf(fin, "%d", &p);
                arr[p] = i;
            }
        }
        TeamNode *head = create_TeamNode(-1);
        char s[15];
        fprintf(fout, "Case #%d\n", tc++);
        while(1){
            fscanf(fin, "%s", s);
            if(!strcmp(s, "CLOSE")){
                break;
            }
            if(!strcmp(s, "ARRIVE")){
                int a;
                int f = 0;
                fscanf(fin, "%d", &a);
                int t=arr[a];
                TeamNode *cur = head;
                while(cur->next != NULL){
                    if(cur->next->teamID == t){
                        f = 1;
                        enqueue(cur->next, a);
                        break;
                    }
                    cur = cur->next;
                }
                if(!f){
                    cur->next = create_TeamNode(arr[a]);
                    cur = cur->next;
                    enqueue(cur, a);
                }
            }
            if(!strcmp(s, "SERVE")){
                TeamNode *cur = head->next;
                MemberNode *a = dequeue(cur);
                fprintf(fout, "%d\n", a->id);
                if (cur->front == NULL) {
                    // 從 linked list 中移除 cur
                    TeamNode *prev = head;
                    while (prev->next != cur) prev = prev->next;
                    prev->next = cur->next;
                    free(cur);
                }
            }
        }
        fprintf(fout, "\n");
    }

    fclose(fin);
    fclose(fout);

    return 0;
}

TeamNode *create_TeamNode(int teamID){
    TeamNode *new_node = malloc(sizeof(TeamNode));
    if(!new_node){
        printf("Error occured in create_TeamNode\n");
        return NULL;
    }
    new_node->front = NULL;
    new_node->rear = NULL;
    new_node->next = NULL;
    new_node->teamID = teamID;
    return new_node;
}
MemberNode *create_MemberNode(int id){
    MemberNode *m = malloc(sizeof(MemberNode));
    if(!m){
        printf("Error occured in create_memberNode\n");
        return NULL;
    }
    m->id = id;
    m->next = NULL;
    return m;
}
TeamNode *enqueue(TeamNode *team, int value){
    MemberNode *m = create_MemberNode(value);
    if(!m){
        printf("Error in enqueue\n");
        return team;
    }
    if(team->front == NULL && team->rear == NULL){
        team->front = m;
        team->rear = m;       
    }
    else{
        team->rear->next = m;
        team->rear = m;
    }
    return team;
}
MemberNode *dequeue(TeamNode *team){
    if(team->front == NULL){
        printf("Error in dequeue\n");
        return NULL;
    }
    MemberNode *m = team->front;
    team->front = team->front->next;
    return m;
}