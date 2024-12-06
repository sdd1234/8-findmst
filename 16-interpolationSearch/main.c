#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000
int compareCount = 0;
#define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp)) //x�� y���ٲٴ� temp�Լ�

void generateRandomArray(int data[]) {//�����������Լ�
    for (int i = 0; i < SIZE; i++) {
        data[i] = rand() % 10000;
    }
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
double getAverageBinarySearchCompareCount(int array[]) { //����Ž�� 1000������ ���
    int totalCompareCount = 0; 
    for (int i = 0; i < 1000; i++) {
        int target = array[rand() % SIZE]; 
        compareCount = 0; 
        binary_search(array, target, 0, SIZE - 1);
        totalCompareCount += compareCount; 
    }
    return (double)totalCompareCount / 1000; 
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


void QuickSort(int list[], int left, int right) {//����Ʈ�Լ� ���ο��� ��Ƽ�ǻ��
    if (left < right) {
        int q = partition(list, left, right);
        QuickSort(list, left, q - 1);
        QuickSort(list, q + 1, right);
    }
}


double getAverageInterpolationSearchCompareCount(int array[]) {//����Ž�� 1000�� ���
    int totalCompareCount = 0; 
    for (int i = 0; i < 1000; i++) {
        int target = array[rand() % SIZE]; 
        compareCount = 0; 
        interpol_search(array, target, SIZE); 
        totalCompareCount += compareCount; 
    }
    return (double)totalCompareCount / 1000; 
}


int interpol_search(int array[], int key, int n) {//����Ž���Լ�
    int low, high, j;

    low = 0; 
    high = n - 1; 
    while ((array[high] >= key) && (key > array[low])) { 
        j = ((float)(key - array[low]) / (array[high] - array[low]) 
            * (high - low)) + low;
        compareCount++; 
        if (key > array[j]) {
            low = j + 1; 
        }
        else if (key < array[j]) {
            high = j - 1; 
        }
        else low = j; 
    }
    compareCount++; 
    if (array[low] == key) return(low);  
    else return -1;  
}



int main(int argc, char* argv[]) {
    srand(time(NULL)); 
    int array[SIZE]; 
    generateRandomArray(array); 
    QuickSort(array, 0, SIZE - 1); 
    printArray(array); 
    printf("Average Compare Count of Binary Search: %.2f\n",
        getAverageBinarySearchCompareCount(array));
    printf("Average Compare Count of Interpolation Search: %.2f\n",
        getAverageInterpolationSearchCompareCount(array));

    return 0;
}