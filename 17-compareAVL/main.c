#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int compareCount = 0;
int searchCount = 0;

typedef struct Node {
	int key;
	struct Node* left, * right;
	int height;
} Node;

Node* createNode(int key) {//��� ����
	Node* nptr = (Node*)malloc(sizeof(Node));
	nptr->key = key;
	nptr->right = nptr->left = (Node*)NULL;
	nptr->height = 1;
	return nptr;
}

int getHeight(Node* nptr) { //����� ���� ��ȯ
	if (nptr == (Node*)NULL) return 0;
	else return nptr->height;
}

int getBalance(Node* nptr) { //����� ���� �μ� ��ȯ
	return getHeight(nptr->left) - getHeight(nptr->right);
}

Node* rotateRight(Node* y) { //���������� ȸ��
	Node* x = y->left;
	Node* T3 = x->right;

	x->right = y;
	y->left = T3;

	y->height = 1 + ((getHeight(y->left) > getHeight(y->right))
		? getHeight(y->left)
		: getHeight(y->right));

	x->height = 1 + ((getHeight(x->left) > getHeight(x->right))
		? getHeight(x->left)
		: getHeight(x->right));

	return x;
}

Node* rotateLeft(Node* y) { //�������� ȸ��
	Node* x = y->right;
	Node* T2 = x->left;

	x->left = y;
	y->right = T2;

	y->height = 1 + ((getHeight(y->left) > getHeight(y->right))
		? getHeight(y->left)
		: getHeight(y->right));

	x->height = 1 + ((getHeight(x->left) > getHeight(x->right))
		? getHeight(x->left)
		: getHeight(x->right));

	return x;
}

Node* insertNode(Node* root, int key) { //��� ����
	if (root == (Node*)NULL) return createNode(key);

	if (root->key > key)
		root->left = insertNode(root->left, key);
	else if (root->key < key)
		root->right = insertNode(root->right, key);
	else
		return root;

	root->height = 1 + ((getHeight(root->left) > getHeight(root->right))
		? getHeight(root->left)
		: getHeight(root->right));

	int balance = getBalance(root);

	if (balance >= 2) {
		if (getBalance(root->left) >= 0) return rotateRight(root);
		else 
		{
			root->left = rotateLeft(root->left);
			return rotateRight(root);
		}
	}
	else if (balance <= -2) {
		if (getBalance(root->right) < 0) return rotateLeft(root);
		else {
			root->right = rotateRight(root->right);
			return rotateLeft(root);
		}
	}
	else
		return root;
}
Node* minValueNode(Node* node) { //�ּҰ� ��� ��ȯ
	Node* current = node;
	while (current->left != NULL) 
		current = current->left;
	return current;
}

Node* deleteNode(Node* root, int key) { //��� ����
	if (root == NULL) return root; 
	if (key < root->key)                  
		root->left = deleteNode(root->left, key);
	else if (key > root->key)             
		root->right = deleteNode(root->right, key);
	else {                                
		if ((root->left == NULL) || (root->right == NULL)) { 
			Node* temp = root->left ? root->left : root->right;
			if (temp == NULL) {          
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;           
			free(temp);                  
		}
		else {                           
			Node* temp = minValueNode(root->right); 
			root->key = temp->key;      
			root->right = deleteNode(root->right, temp->key); 
		}
	}
	if (root == NULL) return root;   
	root->height = 1 + ((getHeight(root->left) > getHeight(root->right))
		? getHeight(root->left)
		: getHeight(root->right));

	int balance = getBalance(root);
	if (balance > 1 && getBalance(root->left) >= 0) 
		return rotateRight(root);
	if (balance > 1 && getBalance(root->left) < 0) { 
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	if (balance < -1 && getBalance(root->right) <= 0) 
		return rotateLeft(root);
	if (balance < -1 && getBalance(root->right) > 0) { 
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	return root; 
}
Node* searchNode(Node* root, int key) { //��� �˻�
	compareCount++; 
	if (root == NULL || root->key == key) {
		return root; 
	}
	compareCount++;
	if (root->key < key) 
		return searchNode(root->right, key);
	return searchNode(root->left, key); 
}

void freeTree(Node* root) { //free�Լ�
	if (root != NULL) {
		freeTree(root->left);  
		freeTree(root->right); 
		free(root);            
	}
}
void doAVLBatch(Node* root) {//AVLƮ�� 2000�� ����
	for (int i = 0; i < 2000; i++) {
		int A = rand() % 3; 
		int B = rand() % 1000; 
		if (A == 0) {
			root = insertNode(root, B); 
		}
		else if (A == 1) {
			root = deleteNode(root, B); 
		}
		else if (A == 2) {
			searchNode(root, B);       
			searchCount++;
		}
	}
}
void doBinaryBatch(Node* root) {//����Ʈ�� 2000�� ����
	for (int i = 0; i < 2000; i++) {
		int A = rand() % 3; 
		int B = rand() % 1000; 
		if (A == 0) {
			root = insertNode(root, B); 
		}
		else if (A == 1) {
			root = deleteNode(root, B); 
		}
		else if (A == 2) {
			searchNode(root, B);       
			searchCount++;
		}
	}
}

int main(int argc, char* argv[]) {
	Node* root = NULL;
	srand(time(NULL));
	float allCount = 0.0;
	// �������� ���õ� AVL�� ���� 2000ȸ Batch �۾��� �����Ѵ�.
	doAVLBatch(root);
	allCount = (float)compareCount / searchCount;
	printf("average AVL compare count: %.2f\n", allCount);
	// ������ȸ�ϸ� AVLƮ���� ��������� ��� �����͸� free
	freeTree(root);
	root = NULL;
	compareCount = searchCount = 0;
	// �������� ���õ� Binary Search Tree Batch�� �����Ѵ�.
	doBinaryBatch(root);
	allCount = (float)compareCount / searchCount;
	printf("average Bin compare count: %.2f\n", allCount);
	freeTree(root);
	return 0;
}