
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

//강의노트 46p Threaded Binary Tree Representation (1) 참조
typedef struct threadedTree* threadedPointer;
typedef struct threadedTree {
	short int leftThread; /* TRUE if leftChild is thread */
	threadedPointer leftChild;
	char data;
	threadedPointer rightChild;
	short int rightThread; /* TRUE if rightChild is thread */
}threadedTree;
//강의노트 51p Finding the Inorder Successor 참조
threadedPointer insucc(threadedPointer tree)
/* find the inorder successor of tree in a threaded binary tree */
{
	threadedPointer temp;
	temp = tree->rightChild;
	if (!tree->rightThread) { /* normal link */
		while (!temp->leftThread)
			temp = temp->leftChild;
	}
	return temp;
}
//활동지 NO2 문제에서 구현함
threadedPointer inpred(threadedPointer tree)
{
	threadedPointer temp;
	temp = tree->leftChild;
	if (!tree->leftThread) { /* normal link */
		while (!temp->rightThread)
			temp = temp->rightChild;
	}
	return temp;
}

//강의노트 54p Inserting a Node as a Right Child (3) 참조
//﻿s가 가리키는 노드의 right child로서 r이 가리키는 노드를 삽입
void insertRight(threadedPointer s, threadedPointer r)
/* insert r as the right child of s */
{
	threadedPointer temp;
	r->rightChild = s->rightChild;
	r->rightThread = s->rightThread;
	r->leftChild = s;
	r->leftThread = TRUE;
	s->rightChild = r;
	s->rightThread = FALSE;
	if (!r->rightThread) { //삽입한 노드가 leaf가 아니라면
		temp = insucc(r);
		temp->leftChild = r;
	}
}
//활동지 NO2 문제에서 구현함
//﻿s가 가리키는 노드의 left child로서 l 이 가리키는 노드를 삽입
void insertLeft(threadedPointer s, threadedPointer l)
/* insert r as the right child of s */
{
	threadedPointer temp;
	l->leftChild = s->leftChild;
	l->leftThread = s->leftThread;
	l->rightChild = s;
	l->rightThread = TRUE;
	s->leftChild = l;
	s->leftThread = FALSE;
	if (!l->leftThread) { //삽입한 노드가 leaf가 아니라면
		temp = inpred(l);
		temp->rightChild = l;
	}
}
//강의노트 50p Inorder Traversal of a Threaded Binary Tree 참조
void tinorder(threadedPointer tree)
{
	threadedPointer temp = tree;
	for (;;) {
		temp =insucc(temp);
		if (temp == tree) break;
		printf("%3c", temp -> data);
	}
}
threadedPointer MakeTree(char data) {
	threadedPointer temp;
	temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->data = data;
	temp->leftChild = 0;
	temp->leftThread = 0;
	temp->rightChild = 0;
	temp->rightThread = 0;
	return temp;
}

int main() {
	//head 노드와 root 노드를 초기화하는 과정
	threadedTree root;

	root.data = '\0';
	root.leftChild = NULL;
	root.leftThread = FALSE;
	root.rightChild = &root;
	root.rightThread = FALSE;
	
	threadedPointer node1 = MakeTree('D');
	root.leftChild = node1;
	node1->leftChild = &root;
	node1->leftThread = TRUE;
	node1->rightChild = &root;
	node1->rightThread = TRUE;
	
	//노드 추가
	threadedPointer node2 = MakeTree('B');
	insertLeft(node1, node2);
	threadedPointer node3 = MakeTree('E');
	insertRight(node1, node3);
	insertLeft(node2, MakeTree('A'));
	insertRight(node2, MakeTree('C'));
	insertLeft(node1, MakeTree('X'));
	insertRight(node1, MakeTree('Y'));
	//중위순회
    tinorder(&root);
	return 0;
}
