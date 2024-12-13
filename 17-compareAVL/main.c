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

Node* createNode(int key) {//노드 생성
	Node* nptr = (Node*)malloc(sizeof(Node));
	nptr->key = key;
	nptr->right = nptr->left = (Node*)NULL;
	nptr->height = 1;
	return nptr;
}

int getHeight(Node* nptr) { //노드의 높이 반환
	if (nptr == (Node*)NULL) return 0;
	else return nptr->height;
}

int getBalance(Node* nptr) { //노드의 균형 인수 반환
	return getHeight(nptr->left) - getHeight(nptr->right);
}

Node* rotateRight(Node* y) { //오른쪽으로 회전
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

Node* rotateLeft(Node* y) { //왼쪽으로 회전
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

Node* insertNode(Node* root, int key) { //노드 삽입
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
Node* minValueNode(Node* node) { //최소값 노드 반환
	Node* current = node;
	while (current->left != NULL) 
		current = current->left;
	return current;
}

Node* deleteNode(Node* root, int key) { //노드 삭제
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
Node* searchNode(Node* root, int key) { //노드 검색
	compareCount++; 
	if (root == NULL || root->key == key) {
		return root; 
	}
	compareCount++;
	if (root->key < key) 
		return searchNode(root->right, key);
	return searchNode(root->left, key); 
}

void freeTree(Node* root) { //free함수
	if (root != NULL) {
		freeTree(root->left);  
		freeTree(root->right); 
		free(root);            
	}
}
void doAVLBatch(Node* root) {//AVL트리 2000번 시행
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
void doBinaryBatch(Node* root) {//이진트리 2000번 시행
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
	// 과제에서 제시된 AVL에 대한 2000회 Batch 작업을 수행한다.
	doAVLBatch(root);
	allCount = (float)compareCount / searchCount;
	printf("average AVL compare count: %.2f\n", allCount);
	// 후위순회하며 AVL트리로 만들어졌던 모든 데이터를 free
	freeTree(root);
	root = NULL;
	compareCount = searchCount = 0;
	// 과제에서 제시된 Binary Search Tree Batch를 수행한다.
	doBinaryBatch(root);
	allCount = (float)compareCount / searchCount;
	printf("average Bin compare count: %.2f\n", allCount);
	freeTree(root);
	return 0;
}