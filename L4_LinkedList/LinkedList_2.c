/* File Name: L4_NO6,7_201723272_안창희.c 
 * Author: 안창희 
 * E-mail Address: leaping96@ajou.ac.kr
 * Lab Number & Problem Number : L4_No6,7 
 * Description: 다항식을 표현하는 프로그램이며 padd와 derivate 함수의 구현을 수행했다.
 * Last Changed: October 3, 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MALLOC(p, s) \
	if (!((p) = malloc(s))) {\
		fprintf(stderr, "Insufficient memory");\
		exit(EXIT_FAILURE);\
	}

#define IS_FULL(ptr) (!(ptr))
#define MAX_POLYNOMIAL_SIZE 100
#define COMPARE(x,y) (((x)<(y)) ? -1:((x)==(y)) ? 0:1)
#define FALSE 0
#define TRUE 1

typedef struct polyNode* polyPointer;
typedef struct polyNode {
	int coef;
	int expon;
	polyPointer link;
}polyNode;

void attach(int coefficient, int exponent, polyPointer* ptr);//항 추가함수
polyPointer padd(polyPointer a, polyPointer b);//2개 식 덧셈함수
polyPointer derivative(polyPointer first);//1개식 미분함수
void printPolynomial(polyPointer first);//1개식 출력함수

void printPolynomial(polyPointer first)  

/* 주어진 코드 No6_Derivative_main-template.c  참조함 */

{
	polyPointer temp = first; //임시의 항 가리키는 포인터 생성
	for (; temp; temp = temp->link) {
		if (temp->expon == 0) //차수가 0일경우, 계수만 출력
			printf("%d", temp->coef);
		else
			printf("%dx^%d", temp->coef, temp->expon); //차수가 0이 아닐경우, 계수와 승수 출력
		if (temp->link != NULL) 
			printf("+"); //뒷항이 있을경우 +기호 추가
	}
	printf("\n");
}

void attach(int coefficient, int exponent, polyPointer* ptr) { //계수, 승수, 추가할 마지막항의 링크주소 ptr 받아서 항추가
	
	/* 교재의 프로그램 4.10을 참조함 */	
	
	polyPointer temp; 
	MALLOC(temp, sizeof(*temp)); // temp 항 생성해서 입력받은값 넣기
	temp->coef = coefficient; 
	temp->expon = exponent;
	(*ptr)->link = temp; //식의 가장 마지막항 과 temp항을 연결 => temp항이 마지막항으로 변경
	*ptr = temp; 
}
/*
강의노트를 바탕으로 padd를 구현하시오. 반환 값으로 두 다항식 a, b를 더한 다항식의 polyPointer를 반환한다.
 */
polyPointer padd(polyPointer a, polyPointer b) {

	/* 교재의 프로그램 4.9를 참조함 */
	
	polyPointer c, rear, temp;
	int sum;
	MALLOC(rear, sizeof(*rear));
	c = rear;
	while (a&&b)
		switch (COMPARE(a->expon, b->expon)) {
		case -1: /* a->expon < b->expon */
			attach(b->coef, b->expon, &rear);
			b = b->link; //b의 승수가 더 클경우 b항을 rear에 추가 && b는 다음항으로 이동
			break;
		case 0: /* a->expon = b->expon */
			sum = a->coef + b->coef;
			if (sum) attach(sum, a->expon, &rear);
		    a = a->link; b = b->link; break; //a와 b의 승이 같을경우 계수더해서 항을 rear에추가 && a와 b모두 다음항이동
		case 1: /* a->expon > b->expon */
			attach(a->coef, a->expon, &rear);
			a = a->link; //a의 승수가 더 클경우 a항을 rear에 추가 && a는 다음항으로 이동
		}
	/* 리스트 a와 리스트 b의 나머지를 복사  => 실제론 항이 더 많은식만 나머지가 복사되고 적은항은 NULL값을 참조해서 복사안됨 
	   => 왜 오류가 발생하지 않지??? */
	for (; a; a = a->link) attach(a->coef, a->expon, &rear);
	for (; b; b = b->link) attach(b->coef, b->expon, &rear);
	rear->link = NULL;
	/* 필요없는 초기 노드를 삭제 */
	temp = c; c = c->link; free(temp);
	return c;
}


/*
본 문제에서 구현해야할 함수이다. 반환 값으로 미분한 다항식의 polyPointer를 반환한다.
 */
polyPointer derivative(polyPointer first) {
	//padd 프로그램의 attach에 관한 구동방식을 참조,변형시켜 작성함
	polyPointer c, rear, temp;
	int mul;
	MALLOC(rear, sizeof(*rear));
	c = rear;
	while (first)
	{
		mul = (first->coef) * (first->expon);
		if (mul != 0) attach(mul, (first->expon) - 1, &rear);
		else  attach(0, 0, &rear);
		first = first->link;
	}
		rear->link = NULL;
		/* 필요없는 초기 노드를 삭제 */
		temp = c; c = c->link; free(temp);
		return c;

}


int main() {
	polyPointer aFront = NULL, bFront = NULL;;
	polyPointer lastA = NULL, lastB = NULL, sum_result = NULL;
	MALLOC(lastA, sizeof(*lastA));
	MALLOC(lastB, sizeof(*lastB));
	char poly1[MAX_POLYNOMIAL_SIZE] = "4x^4+5x^3+1";
	char poly2[MAX_POLYNOMIAL_SIZE] = "2x^5+3x^3+2";
	printf("Poly 1 = %s, Poly 2 =%s \n", poly1, poly2);

	// poly1과 poly2를 읽어서 linked list에 넣는 함수. 
	for (int i = 0; i < MAX_POLYNOMIAL_SIZE; i = i + 5) { //문자 5개당 1개항이다
		if (poly1[i + 2] == '\0') { //두칸뒤에 끝마침 기호가 있는지 확인 => 마지막 문자&&상수항이면
			attach((int)(poly1[i] - '0'), 0, &lastA); lastA->link = NULL;
			break; //승수0으로 설정해서 리스트(식)의 끝에다 추가 & 마지막항의 link를 NULL로 비워두기
		}
		else
			attach((int)(poly1[i] - '0'), (int)(poly1[i + 3] - '0'), &lastA); //상수항아니고 문자항이면 계수,승수 그대로 추가
		if (i == 0)
			aFront = lastA;//첫번째항일경우 aFront에 lastA값 넣어서 첫번째주소 기억해두기
	}
	for (int i = 0; i < MAX_POLYNOMIAL_SIZE; i = i + 5) {
		if (poly2[i + 2] == '\0') {
			attach((int)(poly2[i] - '0'), 0, &lastB); lastB->link = NULL;
			break;
		}
		else
			attach((int)(poly2[i] - '0'), (int)(poly2[i + 3] - '0'), &lastB);
		if (i == 0)
			bFront = lastB;
	}
	/* 이렇게 구현할 경우 두 식의 마지막항이 상수항이 아닐경우 오류가 발생!! => 예제의 허점인것 같다 */
	printf("Polynomial A = ");
	printPolynomial(aFront); //aFront부터 a식 모두출력
	printf("Polynomial B = ");
	printPolynomial(bFront);//bFrontqnxj b식 모두출력

	// padd를 한 후 해당 결과를 출력하는 코드
	sum_result = padd(aFront, bFront);
	printf("padd result = ");
	printPolynomial(sum_result);

	// derivative를 한 후에 해당 결과를 출력하는 코드
	polyPointer deriResult = NULL;
	deriResult = derivative(sum_result);
	printf("derivative result = "); 
	printPolynomial(deriResult);
	return 0;
}