#include <stdio.h>
#define MAX_VERTICES 6
#define INF 1000

//초기값으로 사용할 그래프의 인접행렬 => 문제1의 그래프!!
int weight[MAX_VERTICES][MAX_VERTICES] = {
  {0,10,3,INF,20,INF},
  {INF,0,INF,INF,INF,30},
  {INF, 6, 0, 15, INF,INF},
  {INF,15,INF,0,6,INF},
  {INF,INF,INF,INF,0,3},
  {INF,INF,INF,INF,INF,0}
};

int distance[MAX_VERTICES][MAX_VERTICES];  


void allcosts(int cost[][MAX_VERTICES], int distance[][MAX_VERTICES], int n)
{
	int i, j, k;
    //distance 행렬을 주어진 그래프로 초기화
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			distance[i][j] = cost[i][j];
    
	for (k = 0; k < n; k++)//거쳐가는 노드
		for (i = 0; i < n; i++)//출발노드
			for (j = 0; j < n; j++)//도착노드
                //거쳐가는것이 한번에 가는것보다 더 비용이 적다면 갱신!
				if (distance[i][k] + distance[k][j] < distance[i][j]) {
					distance[i][j] = distance[i][k] + distance[k][j];
				}
}



int main() {

	allcosts(weight, distance, MAX_VERTICES);

	printf("플로이드 알고리즘으로 정렬된 인접행렬 출력 \n");
	for (int i = 0; i < MAX_VERTICES; i++) {
		for (int j = 0; j < MAX_VERTICES; j++) {
			printf("%5d ", distance[i][j]);
		}
		printf("\n");
	}


	return 0;
}