/* File Name: Lab03.c 

 * Author: ��â�� 

 * E-mail Address: leaping96@ajou.ac.kr 

 * Lab Number & Problem Number : L3_No3 

 * Description:
 stack�ڷᱸ���� move��� ����ü �迭�� �̿��Ͽ� 0�� 1�� �̷���� 6x6 �̷��� �Ա����� �ⱸ������ ��θ� ã�� ���α׷��̴�.

 * Last Changed: September 26, 2019 

*/

#include <stdio.h>
//���� ������ ���������� (5,5) �̹Ƿ� ���������� (5,5)�� ����
#define EXIT_ROWS  5
#define EXIT_COLS  5
//

//������ ������ 0 ���� 1�� ����
#define FALSE 0
#define TRUE 1


/*                     ���ǳ�Ʈ 23p~24p�� �ڵ� ����                          */
typedef struct {
	short int vert;
	short int horiz;
} offsets;
offsets move[8];
//


/*                    ���ǳ�Ʈ 25p�� �ڵ� ����                     */
#define MAX_STACK_SIZE 100
typedef struct {
	short int row;
	short int col;
	short int dir;
} element;
element stack[MAX_STACK_SIZE];
//


//�Լ� �����
void push(element);
element pop();
void path();


int maze[7][7] = //�̷� ���� �� �ʱ�ȭ
{ 1,1,1,1,1,1,1,
  1,0,0,1,1,0,1,
  1,1,1,0,0,1,1,
  1,1,1,0,1,1,1,
  1,1,0,1,0,1,1,
  1,0,1,1,0,0,1,
  1,1,1,1,1,1,1 };

int mark[7][7] = //��Ŀ ���� �� ��� 0���� �ʱ�ȭ
{ 0, };

int top;

int main()
{
	// W ���� ����
	move[0].vert = 0;
	move[0].horiz = -1;
	// SW ���� ����
	move[1].vert = 1;
	move[1].horiz = -1;
	// S ���� ����
	move[2].vert = 1;
	move[2].horiz = 0;
	// SE ���� ����
	move[3].vert = 1;
	move[3].horiz = 1;
	// E ���� ����
	move[4].vert = 0;
	move[4].horiz = 1;
	// NE ���� ����
	move[5].vert = -1;
	move[5].horiz = 1;
	// N ���� ����
	move[6].vert = -1;
	move[6].horiz = 0;
	// NW ���� ����
	move[7].vert = -1;
	move[7].horiz = -1;
	
	path(); 

	return 0;
}


/*  ���ǳ�Ʈ 8p�� push �Լ� ���� */
void push(element item)
{ 
	if (top == MAX_STACK_SIZE)
		printf("������ �� ���� ���̻� �߰��� �� �����ϴ�, \n");
	else
		stack[++top] = item;
}
//


/*  ���ǳ�Ʈ 9p�� pop �Լ� ���� */
element pop()
{
	if (top == -1)
		printf("������ �� ���̻� ���� �� �����ϴ�. \n");
	else
		return stack[top--];
}
//



/*						���ǳ�Ʈ 28p~30p �� Maze search Function �ڵ� ����						*/
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
		
		//������ �� ���� �ִ� ��ġ�� �����ϰ� �� ��ġ���� ��ΰ� �ִ��� Ȯ��
		position = pop();
		row = position.row;  col = position.col; dir = position.dir;
		while (dir <= 8 && !found) {
			
			//���� ��ġ���� ������ ������ ��� �����Ѵ�.
			next_row = row + move[dir].vert;
			next_col = col + move[dir].horiz;
			if (next_row == EXIT_ROWS && next_col == EXIT_COLS)
				
				//��ΰ� �߰ߵǾ� ������ �����ϰ� ���
				found = TRUE;
			else if (!maze[next_row][next_col]
				&& !mark[next_row][next_col]) {
				
	
			   //������ �� ��ġ�� ��ŷ�� �ȵǾ��ְ� �ո� ���̹Ƿ� ��ŷ�ϰ�, �б��� ������ ����
				mark[next_row][next_col] = 1;
				position.row = row;	 position.col = col;
				position.dir = ++dir;
				push(position);
				row = next_row;	 col = next_col;	 dir = 1;
			}
			else
				++dir; //���� �ȹ߰ߵǸ� dir �ϳ� �����ؼ� �ٸ����⵵ üũ
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