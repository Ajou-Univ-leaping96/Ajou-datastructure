#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s) \
	if (!((p) = malloc(s))) {\
		fprintf(stderr, "Insufficient memory");\
		exit(EXIT_FAILURE);\
	}

typedef int element;
typedef struct listNode* listPointer;
typedef struct listNode {
	element data;
	listPointer link;
} listNode;

void insertData(listPointer* first, listPointer x, element item);
int is_empty(listPointer first);
listPointer find_inorder_pre_node(listPointer first, element item);
void insert_in_order(listPointer* first, element item);
void printList(listPointer first);
void newInsertData(listPointer* first, listPointer x, element item);

// No5 insert_in_order 함수 테스트 코드
void main()
{
	listPointer list1 = NULL;
	insert_in_order(&list1, 10);
	printList(list1);  // 교재 155 페이지 Program 4.4의 함수
	insert_in_order(&list1, 20);
	printList(list1);
	insert_in_order(&list1, 30);
	printList(list1);
	insert_in_order(&list1, 25);
	printList(list1);
	insert_in_order(&list1, 5);
	printList(list1);
	insert_in_order(&list1, 35);
	printList(list1);
	return;
}

void insertData(listPointer* first, listPointer x, element item)
{ /* insert a new node with data=(the value of item) into the chain, first, after the node, x */
	listPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = item;
	if (*first) {
		temp->link = x->link;
		x->link = temp;
	}
	else {
		temp->link = NULL;
		*first = temp;
	}
}


	int is_empty(listPointer first) { //비었으면 1 차있으면 0을 반환
		int result;
		if (first != NULL)
			result = 0;
		else
			result = 1;
		return result;
	}

	listPointer find_inorder_pre_node(listPointer first, element item) { // 첫번째주소와 넣을값을 입력받아서 들어갈주소 반환

		listPointer preNode;
		listPointer temp;
		MALLOC(temp, sizeof(*temp));
		temp->data = item;

	
			preNode = first;
			if (preNode->data > temp->data) {
				return NULL;
			}
		
			while (preNode) {
				if (preNode->link)
				{
					if (preNode->link->data > temp->data)
						return preNode;
					if (preNode->link->data < temp->data)
						preNode = preNode->link;
				}
				else if(preNode->data < temp->data)
					return preNode;
			}
	}

	void insert_in_order(listPointer* first, element item) { //first의 포인터의 포인터와 입력할 값을 넣으면 알아서 찾아넣어줌
		
		if (is_empty(*first) == 1) //비었으면
			insertData(first, *first, item);
		else //차있으면
			if (find_inorder_pre_node(*first, item) == NULL)
				newInsertData(first, *first,item);
			else
				insertData(first, find_inorder_pre_node(*first, item), item);
		printf("intsert 완료\n");
		return;
	}

	void printList(listPointer first) { //전체리스트 출력
		printf("The list contains:  ");
		for (; first; first = first->link)
			printf("%4d",first->data);
		printf("\n");
		return;
	}

	void newInsertData(listPointer* first, listPointer x, element item) //넣어야할 값이 가장 작을경우 맨앞에다 삽입
	{  /* 필요하다면, 아래에 코드 작성 */
		listPointer temp;
		MALLOC(temp, sizeof(*temp));

		temp->data = item;
		temp->link = *first;
		*first = temp;
	}

	void insert_in_order(listPointer* first, element item) {
	/*	first = 오름차순 linked list의 first node를 가리키고 있다. 
		item = 삽입하기 원하는 값
	*/
	/* 아래에 코드를 작성하시오. */
	
	    if (is_empty(*first) == 1) //비었으면
	          insertData(first, *first, item);
	    else //차있으면
  	        if (find_inorder_pre_node(*first, item) == NULL)
   	              newInsertData(first, *first,item);
    	      else
    	             insertData(first, find_inorder_pre_node(*first, item), item);
   	 printf("intsert 완료\n");
    	return;
	}