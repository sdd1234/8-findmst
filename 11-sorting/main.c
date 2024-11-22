#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100
int Insert_comapare = 0;
int bouble_move=0;

void print_list(int data[], int size) { //����Ʈ�Լ�
	for (int i = 0; i < size; i++) {
		printf("%d ", data[i]);
	}
}

void generateRandomData(int data[]) { //������ �����Լ� (0-999)
	for (int i = 0; i < SIZE; i++) {
		data[i]=rand() % 1000;
	}
}

void doSelectionSort(int data[]) { //��������
	printf("Selection Sort: ");
	printf("\n");
	int i, j, least, temp;
	for (int i = 0; i < SIZE - 1; i++) {
		least = i;

		for (j = i + 1; j < SIZE; j++) {
			if (data[least] > data[j]) 
				least = j;
		}
			temp = data[i];
			data[i] = data[least];
			data[least] = temp;
		if (i + 1 == 10 || i + 1 == 30
			|| i + 1 == 50 || i + 1 == 70
			|| i + 1 == 90 || i + 1 == 100) {
			printf("step %d: ", i + 1);
			print_list(data, SIZE);
			printf("\n");
		}

	}
}
void insertion_sort(int list[]) { //��������
	int i, j, key;
	for (i = 1; i < SIZE; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] > key; j--) {
			Insert_comapare++;
			list[j + 1] = list[j];
		}
		list[j + 1] = key;
	}
}
void doInsertionSort(int data[]) {//�������� ȣ�� 
	for (int i = 0; i < 20; i++) {
		generateRandomData(data);
		insertion_sort(data);
	}
		printf("Insert Sort Compare Average: %d", Insert_comapare / 20);
		printf("\n");
		printf("Insert Sort Result:");
		printf("\n");
		print_list(data, SIZE);
		printf("\n");
}

void BubbleSort(int data[]) {//��������
	int temp;
	int flag; //���� ���θ� �˱����� �÷���
		for (int i = SIZE - 1; i > 0; i--) {
			flag = 0;
			for (int j = 0; j < i; j++) {
				if (data[j] > data[j + 1]) {
					bouble_move+=3; //�̵�Ƚ���� 3�������ؾ���
					temp = data[j];
					data[j] = data[j + 1];
					data[j+1] = temp;
					flag = 1;
				}
			}
			if (flag == 0) break;
		}
	}

void doBubbleSort(int data[]) { //20��ȣ��
	for (int i = 0; i < 20; i++) {
		generateRandomData(data);
			BubbleSort(data);
	}
	printf("Bouble Sort Move Average: %d", bouble_move / 20);
	printf("\n");
	printf("Bouble Sort Result:");
	printf("\n");
	print_list(data, SIZE);
}



int main() {
	int randomData[SIZE];
	generateRandomData(randomData);
	doSelectionSort(randomData);
	doInsertionSort(randomData);
	doBubbleSort(randomData);
	return 0;
}