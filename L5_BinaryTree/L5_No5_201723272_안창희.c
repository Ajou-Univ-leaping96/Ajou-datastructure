/* File Name: Problem_5.c
 * Author: 안창희
 * E-mail Address: leaping96@ajou.ac.kr 
 * Lab Number & Problem Number : L5_No5
 * Description: 프로그램 설명을 간단히 쓰세요
 * Last Changed: October 16, 2019
*/


#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode* treePointer; //문제에서 주어진 코드 참조
typedef struct treeNode {
	int data; // 데이터의 타입에 따라 선언
	treePointer leftChild, rightChild;
} treeNode;

void inorder(treePointer ptr) //문제에서 주어진 코드 참조
{
	if (ptr) {
		inorder(ptr->leftChild);
		printf("%d ", ptr->data); // 데이터의 타입에 따라 출력
		inorder(ptr->rightChild);
	}
	return;
}

void preorder(treePointer ptr) //문제에서 주어진 코드 참조
{
	if (ptr) {
		printf("%d ", ptr->data); // 데이터의 타입에 따라 출력
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
	return;
}

void postorder(treePointer ptr) //문제에서 주어진 코드 참조
{
	if (ptr) {
		postorder(ptr->leftChild);
		postorder(ptr->rightChild);
		printf("%d ", ptr->data); // 데이터의 타입에 따라 출력
	}
	return;
}

treePointer makeBT(int item, treePointer bt1, treePointer bt2) { //직접구현

	treePointer ptr;
	ptr =(treePointer*)malloc(sizeof(treeNode));
	ptr->data = item;
	ptr->leftChild = bt1;
	ptr->rightChild = bt2;
	return ptr;
}


int main() { //leaf부터 차례대로 root까지 구현해나가는 코드, makeBT를 사용했고 세가지 방법으로 순회후 출력
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