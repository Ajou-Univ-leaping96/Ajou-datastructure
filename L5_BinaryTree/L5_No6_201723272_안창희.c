/* File Name: Problem_6.c
 * Author: ��â��
 * E-mail Address: leaping96@ajou.ac.kr
 * Lab Number & Problem Number : L5_No6
 * Description: Main���� makeBT�� �־��� ���� ����Ʈ���� �����Ǿ� ������
 * postorder_CAL��, CAL �Լ��� ���� ���� ǥ����� ����� �����ϰ� �ִ�.
 * ����ڰ� �ؾ� �� ���� ��������� �ʰ� ���� ��ư�� ������ȴ�. 
 * Last Changed: October 17, 2019
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100
int top=-1;
int stack[MAX_STACK_SIZE];
int result[30]; // Ʈ������ ������ ��ü���� �����ϴ� �迭
int res_num=0; //��ü���� �׼��� �����ϴ� ����


//�⺻ �ڷ� ������ function ���� ����
typedef struct treeNode* treePointer;
typedef struct treeNode {
	char data; // �������� Ÿ�Կ� ���� ����
	treePointer leftChild, rightChild;
} treeNode;



treePointer makeBT(char item, treePointer bt1, treePointer bt2) {
	/*	bt1 : ���� ����Ʈ���� �� Ʈ���� root�� ����Ű�� �ִ�.
		item : ���� ���� root node�� data�� ���� ��
		  bt2 : ������ ����Ʈ���� �� Ʈ���� root�� ����Ű�� �ִ�.
		return ��: ���� ������� root node�� �ּ� (��, ������� Ʈ���� root �ּ�)
	*/
	/* �Ʒ��� �ڵ带 �ۼ��Ͻÿ�. */
	treePointer ptr;
	ptr = (treePointer*)malloc(sizeof(treeNode));
	ptr->data = item;
	ptr->leftChild = bt1;
	ptr->rightChild = bt2;
	return ptr;
}

//Ȱ������ �⺻ �ڷ� ������ function���� postorder �Լ��� �����ؼ� ������ 
void postorder_CAL(treePointer ptr)
{
	if (ptr) {
		postorder_CAL(ptr->leftChild);
		postorder_CAL(ptr->rightChild);
		result[res_num] = ptr->data; //���� �����ϴ� �迭���� �� ���� int������ ����

		
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
		res_num++; //�׼��� 1�� ������Ŵ
	}
	return;
}


/*  stack ���ǳ�Ʈ 8p�� push �Լ� ���� */
void push(int item)
{
	if (top == MAX_STACK_SIZE)
		printf("������ �� ���� ���̻� �߰��� �� �����ϴ�, \n");
	else
		stack[++top] = item;
}
/*  stack ���ǳ�Ʈ 9p�� pop �Լ� ���� */
int pop()
{
	if (top == -1)
		printf("������ �� ���̻� ���� �� �����ϴ�. \n");
	else
		return stack[top--];
}


// ��ü����  postorder�� ���� �� int�� �ڷ�� ������ �迭�� �޾Ƶ鿩 ����ϴ� �Լ�

// stack ���ǳ�Ʈ 35p, 43p, 44p 45p�� eval()�Լ��� getToken�Լ��� �˰����� ���� ������
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
	printf("����ǥ���: \n");
	postorder_CAL(root);
	int output = CAL(result);
	printf("\n ���:%d", output);
	return 0;
}