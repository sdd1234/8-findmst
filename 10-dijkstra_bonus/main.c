#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 //무한대이지만 도달할수없는 큰값으로설정



typedef struct EdgeNode {
    int vertex;
    int weight;
    struct EdgeNode* next;
} EdgeNode;

typedef struct GraphType {
    int n;
    EdgeNode* adj_list[MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES]; 
int found[MAX_VERTICES];    

typedef struct {
    int vertex;
    int distance;
} HeapNode;

typedef struct {
    HeapNode heap[MAX_VERTICES];
    int size;
} MinHeap;
//초기화
void init_min_heap(MinHeap* h) {
    h->size = 0;
}
//민힙사용삽입
void insert_min_heap(MinHeap* h, int vertex, int distance) {
    int i = ++(h->size);
    while (i != 1 && distance < h->heap[i / 2].distance) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i].vertex = vertex;
    h->heap[i].distance = distance;
}

//삭제함수
HeapNode delete_min_heap(MinHeap* h) {
    int parent, child;
    HeapNode item, temp;
    item = h->heap[1];
    temp = h->heap[(h->size)--];
    parent = 1;
    child = 2;
    while (child <= h->size) {
        if (child < h->size && h->heap[child].distance > h->heap[child + 1].distance)
            child++;
        if (temp.distance <= h->heap[child].distance)
            break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

// 상태출력함수
void print_status(GraphType* g) {
    printf("distance: ");
    for (int i = 0; i < g->n; i++) {
        if (distance[i] == INF)
            printf("* ");
        else
            printf("%d ", distance[i]);
    }
    printf("\nfound: ");
    for (int i = 0; i < g->n; i++) {
        printf("%d ", found[i]);
    }
    printf("\n\n");
}

// 최단경로 함수
void shortest_path(GraphType* g, int start) {
    MinHeap h;
    init_min_heap(&h);
    int found_order[MAX_VERTICES];  
    int order_index = 0;            

    for (int i = 0; i < g->n; i++) { 
        distance[i] = INF;  
        found[i] = FALSE;
    }
    distance[start] = 0; 
    insert_min_heap(&h, start, 0);  
    print_status(g); 

    while (h.size > 0) {
        HeapNode node = delete_min_heap(&h);
        int u = node.vertex;

        if (found[u]) continue;
        found[u] = TRUE;
        found_order[order_index++] = u + 1; 

        EdgeNode* edge = g->adj_list[u];
        while (edge != NULL) {
            int v = edge->vertex;
            int weight = edge->weight;
            if (!found[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                insert_min_heap(&h, v, distance[v]);
            }
            edge = edge->next;
        }
        print_status(g); 
    }

    
    for (int i = 0; i < g->n; i++) {
        if (!found[i]) {
            found[i] = TRUE;
            found_order[order_index++] = i + 1;  
        }
    }
    print_status(g);

  
    printf("Found Order: ");
    for (int i = 0; i < order_index; i++) {
        printf("%d ", found_order[i]);
    }
    printf("\n");
}
//가중치생성함수
void GenerateGraph(GraphType* g) {
    g->n = 10; // 노드 수
    int weights[10][10] = {
        {0, 3, INF, INF, INF, 11, 12, INF, INF, INF},  
        {3, 0, 5, 4, 1, 7, 8, INF, INF, INF},         
        {INF, 5, 0, 2, INF, INF, 6, 5, INF, INF},     
        {INF, 4, 2, 0, 13, INF, INF, INF, INF, 16},    
        {INF, 1, INF, 13, 0, 9, INF, INF, 18, 17},    
        {11, 7, INF, INF, 9, 0, INF, INF, INF, INF},  
        {12, 8, 6, INF, INF, INF, 0, 13, INF, INF},   
        {INF, INF, 5, INF, INF, INF, 13, 0, INF, 15},  
        {INF, INF, INF, INF, 18, INF, INF, INF, 0, 10},
        {INF, INF, INF, 16, 17, INF, INF, 15, 10, 0}   
    };

    for (int i = 0; i < g->n; i++) {
        g->adj_list[i] = NULL;
        for (int j = 0; j < g->n; j++) {
            if (weights[i][j] != INF && weights[i][j] != 0) {
                EdgeNode* newNode = (EdgeNode*)malloc(sizeof(EdgeNode));
                newNode->vertex = j;
                newNode->weight = weights[i][j];
                newNode->next = g->adj_list[i];
                g->adj_list[i] = newNode;
            }
        }
    }
}

int main(void) {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    if (g == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        return 1;
    }
    GenerateGraph(g);
    shortest_path(g, 0);
    return 0;
}