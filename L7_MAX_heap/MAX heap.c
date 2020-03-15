/* File Name: L6_No_3_201723272_안창희.c
 * Author: 안창희
 * E-mail Address: leaping96@ajou.ac.kr
 * Lab Number & Problem Number : L6_No4
 * Description: visual studio 2019 , windows 10 home 에서실행, main에서 Heap에 대한 초기화을 마쳤으므로
				디버깅하지 않고 실행 만 클릭하면 실행된다.
 * Last Changed: November 1, 2019
*/

//강의노트 8P Implementation of Max Heap 참조
#define MAX_ELEMENTS 200 //maximum size of heap 1
#define HEAP_FULL(n) (n == MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)
#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int	key;
	//추가필드
}element;
element heap[MAX_ELEMENTS];
int n = 0;

//강의노트 9p Insertion 참조
void push(element item, int* n)
{
	int i;
	if (HEAP_FULL(*n)) {
		fprintf(stderr, "The heap is full");
		exit(EXIT_FAILURE);
	}
	i = ++(*n);
	while ((i != 1) && (item.key > heap[i / 2].key)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}

//강의노트 13,14p의 Deletion (1) & Deletion (2) 참조
element pop(int* n) //가장 높은 key값을 지닌 노드를 하나 삭제
{
	int parent, child;
	element item, temp;
	if (HEAP_EMPTY(*n)) {
		fprintf(stderr, "The heap is empty");
		exit(EXIT_FAILURE);
	}
	//가장 큰 키를 저장
	item = heap[1];
	//마지막 노드를 사용하여 힙 재구성
	temp = heap[(*n)--];
	parent = 1;
	child = 2;
	while (child <= *n) {
		//현 parent의 두 child중 큰 child를 찾는다
		if ((child < *n) && (heap[child].key < heap[child + 1].key))
			child++;
		//temp보다 child가 작거나 같게되면 반복중지
		if (temp.key >= heap[child].key) 
			break;
		//삭제된만큼 1레벨 모두 끌어올리기
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}

	heap[parent] = temp;
	return item;
}

//element 한개 생성하여 반환하는 함수
element Make_element(int key) {
	element* ptr;
	ptr = (element*)malloc(sizeof(element));
	ptr->key = key;
	return *ptr;
}

int main() {
	//주어진 순서대로 입력
	push(Make_element(12), &n);
	push(Make_element(9), &n);
	push(Make_element(32), &n);
	push(Make_element(14), &n);
	push(Make_element(16), &n);
	//내림차순으로 정렬하여 출력하는 파트
	element output[MAX_ELEMENTS];
	int out_num = n+1;
	for (int i = 0; i < out_num; i++) {
		output[i] = pop(&n);
		printf("%d ", output[i]);
	}
	return 0;
}
