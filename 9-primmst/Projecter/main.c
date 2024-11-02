#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L
typedef struct GraphType {
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

//���� ª���Ÿ��� ����ġ����
int FindPrimMST(int n) {
    int v = -1;
    for (int i = 0; i < n; i++) {
        if (!selected[i] && (v == -1 || distance[i] < distance[v])) {
            v = i;
        }
    }
    return v;
}

//�̴��Լ�
void graph_init(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->weight[i][j] = INF;
        }
        selected[i] = FALSE;
        distance[i] = INF;
    }
}
//���� ����� �Լ�
void prim(GraphType* g, int s) {
    int u, v;
    for (u = 0; u < g->n; u++)
    distance[u] = INF;
    distance[s] = 0;
    printf("Prim MST Algorithm\n");
    for (int i = 0; i < g->n; i++) {
        u = FindPrimMST(g->n);
        if (u == -1 || distance[u] == INF) return;
        selected[u] = TRUE;
        printf("���� %d �߰�\n", u + 1);  
        for (v = 0; v < g->n; v++) {
            if (g->weight[u][v] != INF && !selected[v] && g->weight[u][v] < distance[v]) {
                distance[v] = g->weight[u][v];
            }
        }
    }
}

void GenerateGraph(GraphType* g) { //�׷��� ���� �� ����ġ �Ҵ�
    g->n = 10; 
    int weights[10][10] = {
        {  0,   3, INF, INF, INF,  11,  12, INF, INF, INF }, 
        {  3,   0,   5,   4,   1,   7,   8, INF, INF, INF }, 
        {INF,   5,   0,   2, INF, INF,   6,   5, INF, INF }, 
        {INF,   4,   2,   0,   5, INF, INF,  14, INF,  16 },
        {INF,   1, INF,   5,   0,   9, INF, INF,  18,  17 }, 
        { 11,   7, INF, INF,   9,   0, INF, INF, INF, INF }, 
        { 12,   8,   6, INF, INF, INF,   0,  13, INF, INF }, 
        {INF, INF,   5,  14, INF, INF,  13,   0, INF,  15 }, 
        {INF, INF, INF, INF,  18, INF, INF, INF,   0,  10 }, 
        {INF, INF, INF,  16,  17, INF, INF,  15,  10,   0 }  
    };
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            g->weight[i][j] = weights[i][j];
        }
    }
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);  
    GenerateGraph(g);  
    prim(g, 0);  
    free(g);  
    return 0;
}