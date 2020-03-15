/* File Name: Lab03.c 

 * Author: 안창희 

 * E-mail Address: leaping96@ajou.ac.kr 

 * Lab Number & Problem Number : L3_No3 

 * Description:
 stack자료구조와 move라는 구조체 배열을 이용하여 0과 1로 이루어진 6x6 미로의 입구에서 출구까지의 경로를 찾는 프로그램이다.

 * Last Changed: September 26, 2019 

*/

#include <stdio.h>
//벽을 제외한 도착지점은 (5,5) 이므로 도착지점을 (5,5)로 설정
#define EXIT_ROWS  5
#define EXIT_COLS  5
//

//논리값을 거짓은 0 참은 1로 설정
#define FALSE 0
#define TRUE 1


/*                     강의노트 23p~24p의 코드 참조                          */
typedef struct {
	short int vert;
	short int horiz;
} offsets;
offsets move[8];
//


/*                    강의노트 25p의 코드 참조                     */
#define MAX_STACK_SIZE 100
typedef struct {
	short int row;
	short int col;
	short int dir;
} element;
element stack[MAX_STACK_SIZE];
//


//함수 선언부
void push(element);
element pop();
void path();


int maze[7][7] = //미로 선언 후 초기화
{ 1,1,1,1,1,1,1,
  1,0,0,1,1,0,1,
  1,1,1,0,0,1,1,
  1,1,1,0,1,1,1,
  1,1,0,1,0,1,1,
  1,0,1,1,0,0,1,
  1,1,1,1,1,1,1 };

int mark[7][7] = //마커 선언 후 모두 0으로 초기화
{ 0, };

int top;

int main()
{
	// W 방향 설정
	move[0].vert = 0;
	move[0].horiz = -1;
	// SW 방향 설정
	move[1].vert = 1;
	move[1].horiz = -1;
	// S 방향 설정
	move[2].vert = 1;
	move[2].horiz = 0;
	// SE 방향 설정
	move[3].vert = 1;
	move[3].horiz = 1;
	// E 방향 설정
	move[4].vert = 0;
	move[4].horiz = 1;
	// NE 방향 설정
	move[5].vert = -1;
	move[5].horiz = 1;
	// N 방향 설정
	move[6].vert = -1;
	move[6].horiz = 0;
	// NW 방향 설정
	move[7].vert = -1;
	move[7].horiz = -1;
	
	path(); 

	return 0;
}


/*  강의노트 8p의 push 함수 참조 */
void push(element item)
{ 
	if (top == MAX_STACK_SIZE)
		printf("스택이 다 차서 더이상 추가할 수 없습니다, \n");
	else
		stack[++top] = item;
}
//


/*  강의노트 9p의 pop 함수 참조 */
element pop()
{
	if (top == -1)
		printf("스택이 비어서 더이상 꺼낼 수 없습니다. \n");
	else
		return stack[top--];
}
//



/*						강의노트 28p~30p 의 Maze search Function 코드 참조						*/
void path() 
{
	int i;
	int row;
	int col;
	int next_row;
	int next_col, dir;
	int found = FALSE;
	element position;

	mark[1][1] = 1;
	top = 0;

	stack[0].row = 1;  stack[0].col = 1;  stack[0].dir = 1;

	while (top > -1 && !found) {
		
		//스택의 맨 위에 있는 위치를 제거하고 이 위치에서 경로가 있는지 확인
		position = pop();
		row = position.row;  col = position.col; dir = position.dir;
		while (dir <= 8 && !found) {
			
			//현재 위치에서 나머지 방향을 모두 점검한다.
			next_row = row + move[dir].vert;
			next_col = col + move[dir].horiz;
			if (next_row == EXIT_ROWS && next_col == EXIT_COLS)
				
				//경로가 발견되어 루프를 종료하고 출력
				found = TRUE;
			else if (!maze[next_row][next_col]
				&& !mark[next_row][next_col]) {
				
	
			   //다음에 갈 위치가 마킹도 안되어있고 뚫린 길이므로 마킹하고, 분기점 저장후 진행
				mark[next_row][next_col] = 1;
				position.row = row;	 position.col = col;
				position.dir = ++dir;
				push(position);
				row = next_row;	 col = next_col;	 dir = 1;
			}
			else
				++dir; //길이 안발견되면 dir 하나 증가해서 다른방향도 체크
		}
	}
	if (found)
	{
	
		printf("The path is: \n");
		printf(" row  col  \n");
		for (i = 0; i <= top; i++)
			printf("%2d%5d\n",stack[i].row, stack[i].col);
		printf("%2d%5d\n", row, col);
		printf("%2d%5d\n", EXIT_ROWS, EXIT_COLS);
		
	}
	else	printf("The maze does not have a path\n");
	

}