#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100
int  comparisonCount = 0;
int moveCount = 0;
int rounds = 0;
int isFirst = 0;
double  totalComparisons = 0;
double  totalMoveCount = 0;
int save[SIZE];

void generateRandomArray(int data[]) { //랜덤값 생성함수 (0-999)
    for (int i = 0; i < SIZE; i++) {
        data[i] = rand() % 1000;
    }
}

void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
    moveCount += 3;
}

void printArray(int list[], int size) {//전체출력
    for (int i = 0; i < size; i++) {
        printf("%3d ", list[i]);
    }
    printf("\n");
}

int partition(int list[], int left, int right) {
    int pivot = list[right]; 
    int i = (left - 1);   

    for (int j = left; j <= right - 1; j++) {
        comparisonCount++;  
        if (list[j] < pivot) {
            i++;  
            swap(&list[i], &list[j]);  
        }
    }
    swap(&list[i + 1], &list[right]);  
    return (i + 1); 
}

void doQuickSort(int list[], int left, int right) {
    int stack[SIZE];  
    int top = -1;  
    stack[++top] = left;
    stack[++top] = right;

    while (top >= 0) {  
        right = stack[top--];  
        left = stack[top--];   
        int pi = partition(list, left, right);  
        // 매 10번째 라운드마다 출력
        if (rounds % 10 == 0 && isFirst == 0) {
            for (int i = 40; i < 60; i++) {
                printf("%d ", list[i]);
            }
            printf("\n\n");
        }
        rounds++; 
        if (pi - 1 > left) {
            stack[++top] = left;
            stack[++top] = pi - 1;
        }
        if (pi + 1 < right) {
            stack[++top] = pi + 1;
            stack[++top] = right;
        }
    }
}


int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];
    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;
        if (i == 0) {
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1);
            printf("Result\n");
            printArray(array, SIZE);
            isFirst++;
        }
        else {
            doQuickSort(array, 0, SIZE - 1);
        }
        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }
    printf("\nAverage Comparisons: %.2f\n", (double)totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", (double)totalMoveCount / 20.0);
    return 0;

}