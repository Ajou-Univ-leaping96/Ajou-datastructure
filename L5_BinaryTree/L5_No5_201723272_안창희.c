/* File Name: Problem_5.c
 * Author: ��â��
 * E-mail Address: leaping96@ajou.ac.kr 
 * Lab Number & Problem Number : L5_No5
 * Description: ���α׷� ������ ������ ������
 * Last Changed: October 16, 2019
*/


#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode* treePointer; //�������� �־��� �ڵ� ����
typedef struct treeNode {
	int data; // �������� Ÿ�Կ� ���� ����
	treePointer leftChild, rightChild;
} treeNode;

void inorder(treePointer ptr) //�������� �־��� �ڵ� ����
{
	if (ptr) {
		inorder(ptr->leftChild);
		printf("%d ", ptr->data); // �������� Ÿ�Կ� ���� ���
		inorder(ptr->rightChild);
	}
	return;
}

void preorder(treePointer ptr) //�������� �־��� �ڵ� ����
{
	if (ptr) {
		printf("%d ", ptr->data); // �������� Ÿ�Կ� ���� ���
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
	return;
}

void postorder(treePointer ptr) //�������� �־��� �ڵ� ����
{
	if (ptr) {
		postorder(ptr->leftChild);
		postorder(ptr->rightChild);
		printf("%d ", ptr->data); // �������� Ÿ�Կ� ���� ���
	}
	return;
}

treePointer makeBT(int item, treePointer bt1, treePointer bt2) { //��������

	treePointer ptr;
	ptr =(treePointer*)malloc(sizeof(treeNode));
	ptr->data = item;
	ptr->leftChild = bt1;
	ptr->rightChild = bt2;
	return ptr;
}


int main() { //leaf���� ���ʴ�� root���� �����س����� �ڵ�, makeBT�� ����߰� ������ ������� ��ȸ�� ���
	treePointer ptr1,ptr2,ptr3,ptr4, root;
	ptr1 = makeBT(8, NULL, NULL);
	ptr2 = makeBT(5, ptr1, NULL);
	ptr1 = makeBT(4, NULL, NULL);
	
	ptr3 = makeBT(2, ptr1, ptr2);

	ptr1 = makeBT(6, NULL, NULL);
	ptr2 = makeBT(7, NULL, NULL);
	ptr4 = makeBT(3, ptr1, ptr2);
	ptr1 = makeBT(1, ptr3, ptr4);

	root = ptr1;
	inorder(root);
	printf("\n");
	preorder(root);
	printf("\n");
	postorder(root);

	return 0;
}