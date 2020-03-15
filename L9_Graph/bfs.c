/* File Name: L9_No_4_201723272_안창희.c
 * Author: 안창희
 * E-mail Address: leaping96@ajou.ac.kr
 * Lab Number & Problem Number : L9_No4
 * Description: visual studio 2019 , windows 10 home 에서실행, 디버깅하지 않고 실행 만 클릭하면 실행된다.
 * Last Changed: November 13, 2019
*/

#include <stdio.h>

//Adjacency Matrix를 위한 자료구조
#define MAX_VERTICES 50
typedef struct GraphType_MAT {
	int n; // 그래프 전체 vertex(정점)의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType_MAT;

//Adjacency List를 위한 자료구조
typedef struct node* nodePointer;
typedef struct node
{
	int vertex;
	struct GraphNode* link;
} GraphNode;

typedef struct GraphType_List {
	int n;// 그래프 전체의 vertex(정점)의 개수
	nodePointer adj_list[MAX_VERTICES];
} GraphType_List;

//검색을 위한 자료구조
#define FALSE 0
#define TRUE 1
short int visited[MAX_VERTICES];
nodePointer graph[MAX_VERTICES];

//BFS 탐색을 위한 queue 자료구조
typedef struct S_node* queuePointer;
typedef struct S_node{
	int vertex;
	queuePointer link;
};
queuePointer front, rear;



//﻿make_adjacency_list() 함수
GraphType_List* make_adjacency_list(GraphType_MAT* M) {
	GraphType_List L;
	nodePointer current = NULL;
	nodePointer previous = NULL;
	L.n = M->n;
	for (int i = 0; i < M->n; i++) {//1개 행당 j하나
		previous = NULL;
		for (int j = 0; j < M->n; j++) { //1개 열당 i하나


			if (M->adj_mat[i][j] == 1) { // j vertex에서 i 로 가는 edge가 있을경우
				//노드 1개 생성
				nodePointer ptr;
				ptr = (nodePointer)malloc(sizeof(GraphNode));

				if (!previous) {//행의 첫번째항일 경우 
					L.adj_list[i] = ptr; //리스트의 'j(행)' 번째 값이 이 노드를 가리키도록
					previous = ptr;
					//노드에다 edge 정보 입력
					previous->vertex = j;
					previous->link = NULL;
				}
				else { //첫번째 항이 아닐경우
					previous->link = ptr;//이전 노드가 이 노드를 가리키도록
					current = ptr;
					//노드에다 edge 정보 입력
					current->vertex = j;
					current->link = NULL;

					previous = previous->link;
				}
			}

		}
	}
	return &L;
}

//﻿print_adjacency_list() 함수
void print_adjacency_list(GraphType_List* L) {


	for (int i = 0; i < L->n; i++) {
		nodePointer temp;
		temp = L->adj_list[i];
		printf(" %d -> ", i);
		while (temp)
		{
			printf(" %d ", temp->vertex);
			temp = temp->link;
		}
		printf("\n");

		//		 1 3 / 2 / 0 1 3 / 0 2
	}

}

//교재코드 응용
void addq(int item) {
	queuePointer temp;
	temp = (queuePointer)malloc(sizeof(*temp));
	temp->vertex = item;
	temp->link = NULL;
	if (front) rear->link = temp;
	else front = temp;
	rear = temp;
}

//교재코드 응용
int deleteq() {
	queuePointer temp = front;
	int item;
	if (!temp) { printf("큐가 비었습니다\n"); return -1; }; 
	item = temp->vertex;
	front = temp->link;
	free(temp);
	return item;
}

//교재코드 응용
void bfs(int v)
{
	nodePointer w;
	front = rear = NULL;/* initialize queue */
	printf(" % 5d ", v);
	visited[v] = TRUE;
	addq(v); /* p.159, Chapter 4 */
	while (front) {
		v = deleteq(); /* p.160, Chapter 4 */
		for (w = graph[v]; w; w = w->link)
			if (!visited[w->vertex]) {
				printf(" % 5d ", w->vertex);
				addq(w->vertex);
				visited[w->vertex] = TRUE;
			} /* if */
	} /* while */
}



//﻿그래프 G1을 adjacency list로 변환하고 출력하는 프로그램
int main() {
	/*
0101	0)	1 -> 3
0010	1)	2
1101	2)	0->1->3
1010	3)	0->2
*/
	GraphType_MAT M;
	M.n = 4;
	M.adj_mat[0][0] = 0; M.adj_mat[0][1] = 1; M.adj_mat[0][2] = 0; M.adj_mat[0][3] = 1;
	M.adj_mat[1][0] = 0; M.adj_mat[1][1] = 0; M.adj_mat[1][2] = 1; M.adj_mat[1][3] = 0;
	M.adj_mat[2][0] = 1; M.adj_mat[2][1] = 1; M.adj_mat[2][2] = 0; M.adj_mat[2][3] = 1;
	M.adj_mat[3][0] = 1; M.adj_mat[3][1] = 0; M.adj_mat[3][2] = 1; M.adj_mat[3][3] = 0;

	GraphType_List L = *(make_adjacency_list(&M));

	//print_adjacency_list(&L);

	for (int i = 0; i < MAX_VERTICES; i++) {
		graph[i] = L.adj_list[i];
	}

	bfs(0);

	return 0;
}