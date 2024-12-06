#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000
int compareCount = 0;
#define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp)) //x�� y���ٲٴ� temp�Լ�
void generateRandomArray(int data[]) {//�����������Լ�
    for (int i = 0; i < SIZE; i++) {
        data[i] = rand() % 1000; 
    }
}

int binary_search(int array[], int key, int low, int high) {//����Ž��
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

void printArray(int* array) {//����Լ�
    printf("Array Sorting Result:\n");

    for (int i = 0; i < 20; i++) 
        printf("%3d ", array[i]);
    printf("\n");

    for (int i = SIZE - 20; i < SIZE; i++) 
        printf("%3d ", array[i]);
    printf("\n");

}

int seq_search(int array[], int key) { //����Ž��
    for (int i = 0; i < SIZE; i++) {
        compareCount++; 
        if (array[i] == key) 
            return i;
    }
    printf("index�� ���������ʽ��ϴ� ");
    return -1; 
}
double getAverageLinearSearchCompareCount(int array[]) {// ����Ž�� 100�������ؼ� ��Ƚ�� ���� 
    int totalCompareCount = 0;                          // �Ǽ��� ����ؾ��ϹǷ� ���� ���
    for (int i = 0; i < 100; i++) { 
        int target = array[rand() % SIZE]; 
        compareCount = 0;                  
        seq_search(array, target);         
        totalCompareCount += compareCount; 
    }
    return (double)totalCompareCount / 100; 
}


int partition(int list[], int left, int right) {//��Ƽ���Լ� �ǹ��� ���Ͽ������� ���� 
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


void doQuickSort(int list[], int left, int right) {//����Ʈ�Լ� ���ο��� ��Ƽ�ǻ��
    if (left < right) { 
        int q = partition(list, left, right); 
        doQuickSort(list, left, q - 1);       
        doQuickSort(list, q + 1, right);      
    }
}


void getQuickSortCompareCount(int array[]) { //����Ʈ�Լ� ��Ƚ��ī��Ʈ���� ���۽� �ʱ�ȭ
    compareCount = 0;                     
    doQuickSort(array, 0, SIZE - 1);      
}

double getAverageBinarySearchCompareCount(int array[]) { //����Ʈ 100������ 
    
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
    //��հ��� ��ȯ�ޱ� ���� ��ġ
    printf("Average Linear Search Compare Count: %.2f\n",
        getAverageLinearSearchCompareCount(array));
    //compareCount�� global variable�̹Ƿ�, ������ ���� ����
    //array�� ���ؼ� ���� �����ϸ� �ȴ�.
    getQuickSortCompareCount(array);
    printf("Quick Sort Compare Count: %d\n", compareCount);
    //���ĵ� Array�� ���ؼ� Binary Search 100ȸ ���� �� ��� ��Ƚ�� ���
    printf("Average Binary Search Compare Count: %.2f\n\n",
        getAverageBinarySearchCompareCount(array));
    printArray(array);
    return 0;
}
