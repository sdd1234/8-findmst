#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRAY_SIZE 100
int Copy[ARRAY_SIZE];
void CopyArray(int data[]) { //복사함수
    for (int i = 0; i < ARRAY_SIZE; i++) {
        Copy[i] = data[i];
    }

}
void PasteArray(int data[]) { //붙여넣기
    for (int i = 0; i < ARRAY_SIZE; i++) {
        data[i] = Copy[i];
    }
}

void generateRandomData(int data[]) { //랜덤값 생성함수 (0-999)
    for (int i = 0; i < ARRAY_SIZE; i++) {
        data[i] = rand() % 1000;
    }
}

void printArray(int list[], int size) { //프린트뒤에...
    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
        if (i + 1 == size) {
            printf("...");
        }
    }
    printf("\n");
    printf("\n");
}

void printArray2(int list[], int size) {//프린트 뒤에 ...없음
    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
    printf("\n");
}


int gap_insertion_sort(int list[], int first, int last, int gap, int* comparisonCount, int* moveCount) {
    int i, j, key;
    int temp = 0;
    for (i = first + gap; i <= last; i += gap) {
        key = list[i];
        for (j = i - gap; j >= first; j -= gap) {
            (*comparisonCount)++;
            if (list[j] > key) {
                temp = list[j + gap];
                list[j + gap] = list[j];
                list[j] = temp;

                (*moveCount)= (*moveCount)+3;
            }
            else {
                break;
            }
        }
       
    }

    return *comparisonCount;
}

void doShellSort(int list[], int gap_factor, int* comparisonCount, int* moveCount) { //쉘소트
    int i, gap;
    int totalComparisonCount = 0;
    int totalMoveCount = 0;
    int sortedArray[ARRAY_SIZE];

    for (int k = 0; k < 20; k++) {
        int tempComparisonCount = 0;
        int tempMoveCount = 0;

        CopyArray(list);
        for (gap = ARRAY_SIZE / gap_factor; gap > 0; gap /= gap_factor) {
            for (i = gap; i < ARRAY_SIZE; i++) {
                int temp = list[i];
                int j;
                for (j = i; j >= gap && list[j - gap] > temp; j -= gap) {
                    list[j] = list[j - gap];
                    tempComparisonCount++;
                    tempMoveCount++;
                }
                list[j] = temp;
                tempMoveCount++;
            }
            if (k == 0) { // 첫 번째 반복에서만 출력
                printf("Sorting with gap %d: ", gap);
                printf("\n");
                printArray(list, 20); // 0부터 19번째까지 출력
            }
        }
        totalComparisonCount += tempComparisonCount;
        totalMoveCount += tempMoveCount;

        if (k == 0) { // 첫 번째 반복에서 정렬된 배열 저장
            for (int j = 0; j < ARRAY_SIZE; j++) {
                sortedArray[j] = list[j];
            }
        }

        PasteArray(list);
    }

    *comparisonCount = totalComparisonCount / 20;
    *moveCount = totalMoveCount / 20;

    printf("Sorted shellArray (gap = %d)\n", gap_factor);
    printArray2(sortedArray, ARRAY_SIZE);
    printf("\n");
}


void doInsertionSort(int list[], int* comparisonCount, int* moveCount) {//삽입정렬
    int i, j, key;

    *comparisonCount = 0;
    *moveCount = 0;

    for (i = 1; i < ARRAY_SIZE; i++) {
        key = list[i];
        j = i - 1;
        while (j >= 0 && list[j] > key) {
            list[j + 1] = list[j];
            j = j - 1;
            (*comparisonCount)++;
            (*moveCount)++;
        }
        list[j + 1] = key;
        (*moveCount)++;
    }
    printf("Sorted insertionArray:");
    printf("\n");
    printArray2(list, ARRAY_SIZE);
}

int main() {
    int array[ARRAY_SIZE];
    int comparisonCount, moveCount;
    generateRandomData(array);

    // Shell Sort
    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &comparisonCount, &moveCount);
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    // Insertion Sort
    printf("Insertion Sort:\n");
    doInsertionSort(array, &comparisonCount, &moveCount);
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

    return 0;
}