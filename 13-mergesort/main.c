#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100
int  comparisonCount = 0;
int moveCount = 0;
int rounds = 0;
int isFirst = 0;
int  totalCompares = 0;
int  totalDataMoves = 0;
int save[SIZE];

void generateRandomData(int data[]) { //랜덤값 생성함수 (0-999)
    for (int i = 0; i < SIZE; i++) {
        data[i] = rand() % 1000;
    }
}

void printArray(int list[], int size) {//출력
    for (int i = 0; i < size; i++) {
        printf("%3d ", list[i]);
    }
    printf("\n");
}

void merge(int list[], int left, int mid, int right) {//합병정렬함수
    int i, j, k, l;
    i = left; 
    j = mid + 1; 
    k = left; 
   
    while (i <= mid && j <= right) {
        comparisonCount++; 
        if (list[i] <= list[j]) {
            save[k++] = list[i++]; 
        }
        else {
            save[k++] = list[j++]; 
        }
        moveCount++; 
    }
    if (i > mid) {
        for (l = j; l <= right; l++) {
            save[k++] = list[l];
            moveCount++;
        }
    }
   
    else {
        for (l = i; l <= mid; l++) {
            save[k++] = list[l];
            moveCount++;
        }
    }
   
    for (l = left; l <= right; l++) {
        list[l] = save[l];
        moveCount++;
    }

    rounds++; 

    
    if (rounds % 10 == 0 && isFirst == 0) {
        for (int i = 0; i < 10; i++)
            printf("%3d ", list[i]);
        printf("| ");
        for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++)
            printf("%3d ", list[i]);
        printf("\n\n");
    }
}

void doMergeSort(int list[], int n) {//내부함수(반복)
    int curr_size;  
    int left_start; 
    for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
        for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = left_start + curr_size - 1;
            int right_end = (left_start + 2 * curr_size - 1 < n - 1) ? left_start + 2 * curr_size - 1 : n - 1;
            merge(list, left_start, mid, right_end);
        }
    }
}


int main() {
    int array[SIZE];  
    srand((unsigned int)time(NULL));  

    for (int i = 0; i < 20; i++) {  
        generateRandomData(array); 
        comparisonCount = 0;
        moveCount= 0;  

        if (i == 0) {  
            printf("Merge Sort Run\n");
            doMergeSort(array,SIZE);  

            printf("Result\n");
            printArray(array, SIZE); 
            isFirst++;  
        }
        else {
            doMergeSort(array,SIZE);  
        }

        totalCompares += comparisonCount;
        totalDataMoves += moveCount;
    }
    printf("\nAverage Comparisons: %.2f\n", totalCompares / 20.0);
    printf("Average Moves: %.2f\n", totalDataMoves / 20.0);

    return 0;
}
