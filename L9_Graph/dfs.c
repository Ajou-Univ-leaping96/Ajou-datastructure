/* File Name: L9_No_3_201723272_안창희.c
 * Author: 안창희
 * E-mail Address: leaping96@ajou.ac.kr
 * Lab Number & Problem Number : L9_No3
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

//검색을 위한 자료구조
int visited[MAX_VERTICES];
#define FALSE 0
#define TRUE 1

void dfs(int v, GraphType_MAT* M) {
	visited[v] = TRUE;
	for (int i = 0; i < M->n; i++) {
		if (i == 0) printf("%d \n", v);
		if (visited[i] != TRUE && M->adj_mat[v][i] == 1) {
			//printf(" %d -> %i\n", v, i);
			dfs(i, M);
		}
	}
}

int main() {
	/*
0101	0)	1 -> 3
0010	1)	2
1101	2)	0->1->3
1010	3)	0->2
*/
//행렬 생성
	GraphType_MAT M;
	M.n = 4;
	M.adj_mat[0][0] = 0; M.adj_mat[0][1] = 1; M.adj_mat[0][2] = 0; M.adj_mat[0][3] = 1;
	M.adj_mat[1][0] = 0; M.adj_mat[1][1] = 0; M.adj_mat[1][2] = 1; M.adj_mat[1][3] = 0;
	M.adj_mat[2][0] = 1; M.adj_mat[2][1] = 1; M.adj_mat[2][2] = 0; M.adj_mat[2][3] = 1;
	M.adj_mat[3][0] = 1; M.adj_mat[3][1] = 0; M.adj_mat[3][2] = 1; M.adj_mat[3][3] = 0;
	//깊이우선탐색
	dfs(0, &M);

	return 0;
}