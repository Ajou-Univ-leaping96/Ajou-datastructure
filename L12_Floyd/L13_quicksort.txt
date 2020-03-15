#define _CRT_SECURE_NO_WARNINGS
//#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct st {
//최대 10글자 단어의 자료구조
	char key[10]; //단어
	char mean[10]; //의미
}element;

//문자열버전 quicksort 함수
void quicksort(element a[], int left, int right)
{
	int i, j; element temp;
	char pivot[10]; //피봇단어

	if (left < right) {
		i = left; j = right + 1; //i값은 왼쪽에서 부터 j값은 오른쪽에서 부터 탐색
		strcpy(pivot, a[left].key); //가장 왼쪽값을 피봇으로 설정
		do {
			do i++; //왼쪽에서부터 탐색하면서 pivot보다 알파벳 순서가 뒤인 i번째 원소를 찾을때까지 i증가
			while (strcmp(a[i].key, pivot) == -1);
			do j--; //오른쪽에서부터 탐색하면서 pivot보다 알파벳 순서가 앞인 j번째 원소를 찾을때까지 j감소
			while (strcmp(a[j].key, pivot) == 1);
			if (i < j) { //i와 j가 서로 증가/감소하여 엇갈리지 않은 상태이면 찾아낸 두 i와 j번째 원소를 SWAP
				strcpy(temp.key, a[i].key); strcpy(temp.mean, a[i].mean);
				strcpy(a[i].key, a[j].key); strcpy(a[i].mean, a[j].mean);
				strcpy(a[j].key, temp.key); strcpy(a[j].mean, temp.mean);
			}
		} while (i < j);//i와 j가 서로 증가/감소하여 엇갈릴때까지 반복

        //둘이 엇갈리게되어 반복문 빠져나오면 가장 왼쪽 값과 j번째 값을 SWAP => 피봇을 중앙에 배치
		strcpy(temp.key, a[left].key); strcpy(temp.mean, a[left].mean);
		strcpy(a[left].key, a[j].key); strcpy(a[left].mean, a[j].mean);
		strcpy(a[j].key, temp.key); strcpy(a[j].mean, temp.mean);
        //피봇이 중앙에 배치되고 왼쪽엔 피봇보다 알파벳순서가 빠른 단어, 오른쪽엔 늦은 단어로 정렬된다
        //이후 피봇을 중심으로 왼쪽 오른쪽을 나누어 반복
		quicksort(a, left, j - 1);
		quicksort(a, j + 1, right);
        //이 반복은 모든 원소들이 정렬될때까지 반복
	}
}

int main()
{
	element word_book[10]; //10개 단어

    //10개 단어의 뜻과 단어를 입력받는부분
	printf("10개 단어와 의미를 입력하시오");
	for (int i = 0; i < 10; i++)
	{
		//printf("%d번째 단어&뜻 : ", i + 1);
		scanf_s("%s", &word_book[i].key, sizeof(word_book[i].key));
		scanf_s("%s", &word_book[i].mean, sizeof(word_book[i].mean));
	}
	printf("\n");
	
    //입력받지 않고 하드코딩으로 구현한 경우
	/*
	strcpy(word_book[0].key, "banana"); strcpy(word_book[0].mean, "바나나");
	strcpy(word_book[1].key, "which"); strcpy(word_book[1].mean, "어느것");
	strcpy(word_book[2].key, "table"); strcpy(word_book[2].mean, "테이블");
	strcpy(word_book[3].key, "data"); strcpy(word_book[3].mean, "자료");
	strcpy(word_book[4].key, "structure"); strcpy(word_book[4].mean, "구조");
	strcpy(word_book[5].key, "melon"); strcpy(word_book[5].mean, "멜론");
	strcpy(word_book[6].key, "welcome"); strcpy(word_book[6].mean, "환영");
	strcpy(word_book[7].key, "hello"); strcpy(word_book[7].mean, "안녕");
	strcpy(word_book[8].key, "apple"); strcpy(word_book[8].mean, "사과");
	strcpy(word_book[9].key, "cat"); strcpy(word_book[9].mean, "고양이");
	*/

	quicksort(word_book, 0, 9); //10개 단어를 알파벳순으로 정렬
    //정렬된 10개 단어를 출력
	for (int i = 0; i < 10; i++)
	{
		printf("%s ", word_book[i].key);
		printf("%s ", word_book[i].mean);
		printf("\n");
	}
	return 0;
}