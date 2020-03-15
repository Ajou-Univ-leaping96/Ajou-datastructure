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



//dfs를 위한 자료구조
#define FALSE 0
#define TRUE 1
short int visited[MAX_VERTICES];
nodePointer graph[MAX_VERTICES];

//BCC를 위한 자료구조 => 교재참조
#define MIN2(x,y) ((x) < (y) ? (x) : (y))
short int dfn[MAX_VERTICES];
short int low[MAX_VERTICES];
int num;

//스택을 위한 자료구조
#define MAX_STACK_SIZE 100 
int stack[MAX_STACK_SIZE][2];
int top = -1;



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



//스택의 push 함수
void push(int x, int y)

{
	stack[++top][0] = x;
	stack[top][1] = y;
}

//스택의 pop 함수
void pop(int* x, int* y)

{
	*x = stack[top][0];
	*y = stack[top--][1];
}



// 교재참조
void init()
{
	int i;
	for (i = 0; i < num; i++) {
		visited[i] = FALSE;
		dfn[i] = low[i] = -1;
	}
	num = 0;
}


void bicon(int u, int v) //교재참조
{
	nodePointer ptr;
	int w, x, y;
	dfn[u] = low[u] = num++; //root항의 dfn과 low에 num+1값 입력
	for (ptr = graph[u]; ptr; ptr = ptr->link) { //ptr에다 root항의 adjList 노드 주소 입력
		//주소값 유효할경우 다음노드로 넘어가 반복실행
		w = ptr->vertex; //w에다 첫항의 vertex 입력
		if (v != w && dfn[w] < dfn[u]) push(u, w); //w가 루트값이 아니고 dfn도 루트보다 작을경우 
		if (dfn[w] < 0) {
			bicon(w, u);
			low[u] = MIN2(low[u], low[w]);
			if (low[w] >= dfn[u]) {
				printf("New biconnected component : ");
				do {
					pop(&x, &y); printf(" < % d, % d>", x, y);
				} while (!((x == u) && (y == w)));
				printf("\n");
			}
		}
		else if (w != v) low[u] = MIN2(low[u], dfn[w]);
	}
}



void dfs(int v)
{
	nodePointer w;
	visited[v] = TRUE;
	printf(" % 5d", v);
	for (w = graph[v]; w; w = w->link) {
		if (!visited[w->vertex])
			dfs(w->vertex);
	}
}




int main() {
	//그래프를 나타낸 행렬
	GraphType_MAT M;
	M.n = 10;
	M.adj_mat[0][0] = 0; M.adj_mat[0][1] = 0; M.adj_mat[0][2] = 1; M.adj_mat[0][3] = 0; M.adj_mat[0][4] = 0; M.adj_mat[0][5] = 0; M.adj_mat[0][6] = 0; M.adj_mat[0][7] = 0; M.adj_mat[0][8] = 0; M.adj_mat[0][9] = 0;
	M.adj_mat[1][0] = 0; M.adj_mat[1][1] = 0; M.adj_mat[1][2] = 1; M.adj_mat[1][3] = 1; M.adj_mat[1][4] = 0; M.adj_mat[1][5] = 0; M.adj_mat[1][6] = 0; M.adj_mat[1][7] = 0; M.adj_mat[1][8] = 0; M.adj_mat[1][9] = 0;
	M.adj_mat[2][0] = 1; M.adj_mat[2][1] = 1; M.adj_mat[2][2] = 0; M.adj_mat[2][3] = 0; M.adj_mat[2][4] = 1; M.adj_mat[2][5] = 0; M.adj_mat[2][6] = 0; M.adj_mat[2][7] = 0; M.adj_mat[2][8] = 0; M.adj_mat[2][9] = 0;
	M.adj_mat[3][0] = 0; M.adj_mat[3][1] = 1; M.adj_mat[3][2] = 0; M.adj_mat[3][3] = 0; M.adj_mat[3][4] = 1; M.adj_mat[3][5] = 1; M.adj_mat[3][6] = 0; M.adj_mat[3][7] = 0; M.adj_mat[3][8] = 0; M.adj_mat[3][9] = 1;
	M.adj_mat[4][0] = 0; M.adj_mat[4][1] = 0; M.adj_mat[4][2] = 1; M.adj_mat[4][3] = 1; M.adj_mat[4][4] = 0; M.adj_mat[4][5] = 0; M.adj_mat[4][6] = 0; M.adj_mat[4][7] = 0; M.adj_mat[4][8] = 0; M.adj_mat[4][9] = 0;
	M.adj_mat[5][0] = 0; M.adj_mat[5][1] = 0; M.adj_mat[5][2] = 0; M.adj_mat[5][3] = 1; M.adj_mat[5][4] = 0; M.adj_mat[5][5] = 0; M.adj_mat[5][6] = 1; M.adj_mat[5][7] = 1; M.adj_mat[5][8] = 0; M.adj_mat[5][9] = 1;
	M.adj_mat[6][0] = 0; M.adj_mat[6][1] = 0; M.adj_mat[6][2] = 0; M.adj_mat[6][3] = 0; M.adj_mat[6][4] = 0; M.adj_mat[6][5] = 1; M.adj_mat[6][6] = 0; M.adj_mat[6][7] = 0; M.adj_mat[6][8] = 1; M.adj_mat[6][9] = 0;
	M.adj_mat[7][0] = 0; M.adj_mat[7][1] = 0; M.adj_mat[7][2] = 0; M.adj_mat[7][3] = 0; M.adj_mat[7][4] = 0; M