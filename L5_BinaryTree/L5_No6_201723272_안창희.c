/* File Name: Problem_6.c
 * Author: 안창희
 * E-mail Address: leaping96@ajou.ac.kr
 * Lab Number & Problem Number : L5_No6
 * Description: Main에서 makeBT로 주어진 식이 이진트리로 구현되어 있으며
 * postorder_CAL과, CAL 함수를 통해 후위 표기식의 계산을 수행하고 있다.
 * 사용자가 해야 할 것은 디버깅하지 않고 실행 버튼만 누르면된다. 
 * Last Changed: October 17, 2019
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100
int top=-1;
int stack[MAX_STACK_SIZE];
int result[30]; // 트리에서 추출한 전체식을 저장하는 배열
int res_num=0; //전체식의 항수를 저장하는 변수


//기본 자료 구조와 function 에서 발췌
typedef struct treeNode* treePointer;
typedef struct treeNode {
	char data; // 데이터의 타입에 따라 선언
	treePointer leftChild, rightChild;
} treeNode;



treePointer makeBT(char item, treePointer bt1, treePointer bt2) {
	/*	bt1 : 왼쪽 서브트리가 될 트리의 root를 가리키고 있다.
		item : 새로 만든 root node의 data로 넣을 값
		  bt2 : 오른쪽 서브트리가 될 트리의 root를 가리키고 있다.
		return 값: 새로 만들어진 root node의 주소 (즉, 만들어진 트리의 root 주소)
	*/
	/* 아래에 코드를 작성하시오. */
	treePointer ptr;
	ptr = (treePointer*)malloc(sizeof(treeNode));
	ptr->data = item;
	ptr->leftChild = bt1;
	ptr->rightChild = bt2;
	return ptr;
}

//활동지의 기본 자료 구조와 function에서 postorder 함수를 참조해서 변형함 
void postorder_CAL(treePointer ptr)
{
	if (ptr) {
		postorder_CAL(ptr->leftChild);
		postorder_CAL(ptr->rightChild);
		result[res_num] = ptr->data; //식을 저장하는 배열에다 각 항을 int헝으로 저장

		
		if (result[res_num] == 42 || result[res_num] == 43 || result[res_num] == 47 || result[res_num] == 45) {
			
			switch (result[res_num]) {
			case 42: printf("* "); break;
			case 43: printf("+ "); break;
			case 47: printf("/ "); break;
			case 45: printf("- "); break;
			default: break;
			}
		}
		else
			printf("%d ", result[res_num]);
		
		//printf("%d ", result[res_num]);
		res_num++; //항수를 1개 증가시킴
	}
	return;
}


/*  stack 강의노트 8p의 push 함수 참조 */
void push(int item)
{
	if (top == MAX_STACK_SIZE)
		printf("스택이 다 차서 더이상 추가할 수 없습니다, \n");
	else
		stack[++top] = item;
}
/*  stack 강의노트 9p의 pop 함수 참조 */
int pop()
{
	if (top == -1)
		printf("스택이 비어서 더이상 꺼낼 수 없습니다. \n");
	else
		return stack[top--];
}


// 전체식을  postorder로 읽은 후 int형 자료로 저장한 배열을 받아들여 계산하는 함수

// stack 강의노트 35p, 43p, 44p 45p의 eval()함수와 getToken함수의 알고리즘을 많이 참조함
int CAL(int* res)
{
	int op1, op2, value, i;

	int num;

	for (i = 0; i < res_num; i++)
	{
		num = res[i];

		if (num != 42 && num != 43 && num != 47 && num != 45)
		{
			value = num;
			push(value);
			continue;
		}

		op2 = pop();
		op1 = pop();

		switch (num) {
		case 42: value = op1 * op2; break;
		case 43: value = op1 + op2; break;
		case 47: value = op1 / op2; break;
		case 45: value = op1 - op2; break;
		default: exit(1); break;
		}

		push(value);
	}

	return pop();
}


int main() {
	treePointer ptr1, ptr2, ptr3, ptr4, root;
	ptr1 = makeBT(20, NULL, NULL);
	ptr2 = makeBT(15 , NULL, NULL);
	ptr3 = makeBT('-' , ptr1, ptr2);
	ptr1 = makeBT(7 , NULL, NULL);
	ptr2 = makeBT('*' , ptr3, ptr1);
	ptr3 = makeBT(5, NULL, NULL);
	ptr4 = makeBT(3 , NULL, NULL);
	ptr1 = makeBT('-' , ptr3, ptr4);
	ptr3 = makeBT(12 , NULL, NULL);
	ptr4 = makeBT('/' , ptr3, ptr1);
	ptr1 = makeBT('+' , ptr2, ptr4);
	root = ptr1;
	printf("후위표기식: \n");
	postorder_CAL(root);
	int output = CAL(result);
	printf("\n 결과:%d", output);
	return 0;
}