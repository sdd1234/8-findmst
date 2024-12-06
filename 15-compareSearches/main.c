#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000
int compareCount = 0;
#define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp)) //x와 y를바꾸는 temp함수
void generateRandomArray(int data[]) {//랜덤값생성함수
    for (int i = 0; i < SIZE; i++) {
        data[i] = rand() % 1000; 
    }
}

int binary_search(int array[], int key, int low, int high) {//이진탐색
    int middle;
    while (low <= high) {
        middle = (low + high) / 2; 
        compareCount++;           
        if (key == array[middle]) 
            return middle;
        else if (key > array[middle]) 
            low = middle + 1;
        else                          
            high = middle - 1;
    }
    return -1; 
}

void printArray(int* array) {//출력함수
    printf("Array Sorting Result:\n");

    for (int i = 0; i < 20; i++) 
        printf("%3d ", array[i]);
    printf("\n");

    for (int i = SIZE - 20; i < SIZE; i++) 
        printf("%3d ", array[i]);
    printf("\n");

}

int seq_search(int array[], int key) { //순차탐색
    for (int i = 0; i < SIZE; i++) {
        compareCount++; 
        if (array[i] == key) 
            return i;
    }
    printf("index에 존재하지않습니다 ");
    return -1; 
}
double getAverageLinearSearchCompareCount(int array[]) {// 순차탐색 100번수행해서 비교횟수 리턴 
    int totalCompareCount = 0;                          // 실수를 출력해야하므로 더블 사용
    for (int i = 0; i < 100; i++) { 
        int target = array[rand() % SIZE]; 
        compareCount = 0;                  
        seq_search(array, target);         
        totalCompareCount += compareCount; 
    }
    return (double)totalCompareCount / 100; 
}


int partition(int list[], int left, int right) {//파티션함수 피벗은 제일왼쪽으로 시작 
    int pivot, temp;
    int low, high;

    low = left;          
    high = right + 1;    
    pivot = list[left];  
    do {
        do {
            low++;                    
            compareCount++;          
        } while (low <= right && list[low] < pivot); 
        do {
            high--;                    
            compareCount++;          
        } while (high >= left && list[high] > pivot); 
        if (low < high) {             
            SWAP(list[low], list[high], temp);
        }
    } while (low < high);              

    SWAP(list[left], list[high], temp); 
    return high;                        
}


void doQuickSort(int list[], int left, int right) {//퀵소트함수 내부에서 파티션사용
    if (left < right) { 
        int q = partition(list, left, right); 
        doQuickSort(list, left, q - 1);       
        doQuickSort(list, q + 1, right);      
    }
}


void getQuickSortCompareCount(int array[]) { //퀵소트함수 비교횟수카운트위해 시작시 초기화
    compareCount = 0;                     
    doQuickSort(array, 0, SIZE - 1);      
}

double getAverageBinarySearchCompareCount(int array[]) { //퀵소트 100번시행 
    
    int totalCompareCount = 0; 

    for (int i = 0; i < 100; i++) { 
        int target = array[rand() % SIZE]; 
        compareCount = 0;                  
        binary_search(array, target, 0, SIZE - 1);
        totalCompareCount += compareCount; 
    }

    return (double)totalCompareCount / 100; 

}




int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];
    generateRandomArray(array);
    //평균값을 반환받기 위한 조치
    printf("Average Linear Search Compare Count: %.2f\n",
        getAverageLinearSearchCompareCount(array));
    //compareCount가 global variable이므로, 다음과 같이 구현
    //array에 대해서 직접 정렬하면 된다.
    getQuickSortCompareCount(array);
    printf("Quick Sort Compare Count: %d\n", compareCount);
    //정렬된 Array에 대해서 Binary Search 100회 수행 및 평균 비교횟수 출력
    printf("Average Binary Search Compare Count: %.2f\n\n",
        getAverageBinarySearchCompareCount(array));
    printArray(array);
    return 0;
}
