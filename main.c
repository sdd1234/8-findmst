#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100
#define INF 1000
int parent[MAX_VERTICES];	//부모노드 저장

struct Edge {
    int start, end, weight;
};

typedef struct GraphType {
    int n;
    struct Edge edges[2 * MAX_VERTICES];
} GraphType;

typedef struct {
    struct Edge* heap;
    int size;
    int capacity;
} MinHeap;

void set_init(int n) //초기화
{
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}

int set_find(int curr) //부모노드 찾기
{
    if (parent[curr] == -1)
        return curr; 			
    while (parent[curr] != -1) curr = parent[curr];
    return curr;
}

void set_union(int a, int b) //두 정점의 집합을 합침
{
    int root1 = set_find(a);	 
    int root2 = set_find(b);	
    if (root1 != root2) 	
    parent[root1] = root2;
}

void graph_init(GraphType* g) //그래프초기화
{   
    g->n = 0;
    for (int i = 0; i < 2 * MAX_VERTICES; i++) {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF;
    }
}

void insert_edge(GraphType* g, int start, int end, int w) //간선 추가
{
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = w;
    g->n++;
}

int compare(const void* a, const void* b) //간선 비교
{
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    return (x->weight - y->weight);
}

void QuickKruskal(GraphType* g) //퀵소트 기반 크루스칼
{
    int edge_accepted = 0;	
    int uset, vset;		
    struct Edge e;
    set_init(g->n);				
    qsort(g->edges, g->n, sizeof(struct Edge), compare);
    printf("Qucik Based Kruskal \n");
    int i = 0;
    while (edge_accepted < (g->n - 1) && i < g->n)	
    {
        e = g->edges[i];
        uset = set_find(e.start);		
        vset = set_find(e.end);		
        if (uset != vset) {			
            printf("Edge (%d,%d) select %d\n", e.start, e.end, e.weight);     
            edge_accepted++;
            set_union(uset, vset);	
        }
        i++;
    }
    printf("\n");
}

void initMinHeap(MinHeap* h, int capacity) { //힙 초기화
    h->heap = (struct Edge*)malloc(capacity * sizeof(struct Edge));
    h->size = 0;
    h->capacity = capacity;
}

void insert(MinHeap* h, struct Edge item) { //힙에 삽입
    int i = h->size++;
    while (i > 0 && item.weight < h->heap[(i - 1) / 2].weight) {
        h->heap[i] = h->heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    h->heap[i] = item;
}

struct Edge extractMin(MinHeap* h) { //힙에서 최소값 추출
    struct Edge minItem = h->heap[0];
    struct Edge lastItem = h->heap[--h->size];
    int i = 0, j = 1;
    while (j < h->size) {
        if (j < h->size - 1 && h->heap[j].weight > h->heap[j + 1].weight)
            j++;
        if (lastItem.weight <= h->heap[j].weight)
            break;
        h->heap[i] = h->heap[j];
        i = j;
        j = 2 * i + 1;
    }
    h->heap[i] = lastItem;
    return minItem;
}

void MinHeapKruskal(GraphType* g) { //힙 기반 크루스칼
    int edge_accepted = 0;
    int uset, vset;
    struct Edge e;
    MinHeap minHeap;
    set_init(g->n);
    initMinHeap(&minHeap, g->n);
    for (int i = 0; i < g->n; i++) {
        insert(&minHeap, g->edges[i]);
    }
    printf("MinHeap Based Kruskal \n");
    while (edge_accepted < (g->n - 1) && minHeap.size > 0) {
        e = extractMin(&minHeap);
        uset = set_find(e.start);
        vset = set_find(e.end);
        if (uset != vset) {
            printf("Edge (%d,%d) select %d\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);
        }
    }
    free(minHeap.heap);
}

void GenerateGraph(GraphType* g) { //그래프 생성
    insert_edge(g, 1, 2, 3);
    insert_edge(g, 1, 6, 11);
    insert_edge(g, 1, 7, 12);
    insert_edge(g, 2, 3, 5);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 6, 7);
    insert_edge(g, 2, 7, 8);
    insert_edge(g, 3, 4, 2);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 3, 8, 5);
    insert_edge(g, 4, 5, 13);
    insert_edge(g, 4, 8, 14);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 5, 9, 18);
    insert_edge(g, 5, 10, 17);
    insert_edge(g, 7, 8, 13);
    insert_edge(g, 8, 10, 15);
    insert_edge(g, 9, 10, 10);
}

int main(void)
{ 
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);
    GenerateGraph(g);
    QuickKruskal(g);
    MinHeapKruskal(g);
    free(g);
    return 0;
}