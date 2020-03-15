#include <stdio.h>

#define MAX_VERTEX 7
#define INF 999



int graph[MAX_VERTEX][MAX_VERTEX] = {

	  { 0, 10, 0, 55, 20, 0, 0},
	  { 10, 0, 15, 0, 0, 0, 0},
	  { 0, 15, 0, 30, 0, 0, 18},
	  { 55, 0, 0, 0,40, 0, 10},
	  { 20, 0, 0,40, 0, 15, 0},
	  { 0, 0, 0, 0, 15, 0,15},
	  { 0, 0, 18, 10, 0,15, 0},
};

int cost[MAX_VERTEX];  // 비용
int parent[MAX_VERTEX]; // 부모에대한 정보
int Q[MAX_VERTEX];
int Qcount;

//큐에 값 삽입
int Q_insert(int a)
{
	Q[a] = 0;
	Qcount++;
}

//큐에서 최솟값을 꺼내는 함수
int Q_minpop()
{
	int i;
	int min = INF;
	int saveindex = -1;
	for (i = 0; i < MAX_VERTEX; i++) {
		if (Q[i] == -1) continue;
		if (cost[i] < min) {
			saveindex = i;
			min = cost[i];
		}
	}
	if (saveindex == -1) return -1;
	Q[saveindex] = -1;
	Qcount--;
	return saveindex;
}

//큐가 비었는지 확인하는 함수
int Q_isempty()
{
	if (Qcount == 0) return 1;
	return 0;
}

//
int Q_chcost(int w, int newcost)
{
	cost[w] = newcost;
}

//프림 알고리즘대로 방문하는 노드를 출력하는 함수
void Prim(int start)
{
	int i, v, w;
	Qcount = 0;
	for (i = 0; i < MAX_VERTEX; i++) {
		cost[i] = INF;
		parent[i] = -1;
		Q_insert(i);
	}

	cost[start] = 0;
	for (; !Q_isempty();) {
		v = Q_minpop();
		printf(" %c\n", v + 'A');
		for (w = 0; w < MAX_VERTEX; w++) {
			if ((graph[v][w] != 0) && (cost[w] > graph[v][w])) {
				Q_chcost(w, graph[v][w]);
				parent[w] = v;
			}
		}
	}
}

main()
{
	Prim(0);// 0~6 번째 행렬 원소를 A~G vertex로 하여 A를 시작점
	return 0;
}
​