//삽입 삭제 테스트 코드
//트리 모양 확인은 preorder로 구현함
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int key;
	char item;
} element;

typedef struct node* treePointer;
typedef struct node
{
	element data;
	treePointer leftChild, rightChild;
};

treePointer modifiedSearch(treePointer root, int k);
void insert(treePointer* node, int k);
void delete(treePointer* node, int k);
void preorder(treePointer root);

int main()
{

	treePointer root = NULL;
	insert(&root, 3, 'a');
	
	insert(&root, 2, 'b');
	
	insert(&root, 5, 'c');

	
	/*
	insert(&root, 1, 'd');
	insert(&root, 4, 'e');
	insert(&root, 7, 'f');
	*/
	//preorder(root);

	preorder(root);

	delete(&root, 3);

	preorder(root);
}

treePointer modifiedSearch(treePointer node, int k)
{
	treePointer parent, result;
	if (!node) return NULL;//루트노드가 없으면 그냥 NULL 반환
	parent = node;
	result = parent;
	while (parent)
	{
		result = parent;
		if (k < parent->data.key)
			parent = parent->leftChild; //parent 보다 k값이 작을경우 왼족으로 이동
		else if (k > parent->data.key)
			parent = parent->rightChild; //parent보다 k값이 클경우 오른쪽으로 이동
		else
			return NULL; //겹칠경우 NULL 반환
	}
	return result;
}


void insert(treePointer* node, int k, char theItem)//트리의 루트노드, 넣을 키값과 아이템값을 받아서 삽입하는 함수
{
	treePointer ptr, temp = modifiedSearch(*node, k);
	if (temp || !(*node))//겹치는 키값이 없거나. 트리의 루트노드가 NULL이면(둘중하나만 충족되면)
	{
		//ptr이 가리키는 노드 하나 생성
		ptr = (treePointer)malloc(sizeof(*ptr));
		ptr->data.key = k;
		ptr->data.item = theItem;
		ptr->leftChild = ptr->rightChild = NULL;
		//노드에다가 키,아이템 넣고 양쪽링크는 NULL로 세팅
		if (*node)
		{//루트가 있는경우, 부모랑 비교해서 넣는다
			if (k < temp->data.key)
				temp->leftChild = ptr;
			else
				temp->rightChild = ptr;
		}
		else//루트가 없는경우
			*node = ptr;//ptr이 루트가 된다
	}
	printf("삽입완료\n");
}

void delete(treePointer* node, int k) {
	//트리를 뒤져서 키값 일치하는애 찾음
	treePointer parent,current, only_child, r_current, r_parent;
	parent = NULL;
	current = *node;
	while (current != NULL && current->data.key != k)
	{
		parent = current; 
		if (k < current->data.key)
			current = current->leftChild;
		else if(k < current->data.key)
			current = current->rightChild;
	}
	//키값이 없을경우 current는 NULL까지 도달함 => 함수종료
	if (!current)
	{
		printf("요청한 키값이 트리내에 없습니다.");
		return;
	}
	//찾은애가 자식이 0개인지 한개인지 두개인지에 따라 처리

	//0개일 경우
	if (current->leftChild == NULL && current->rightChild == NULL)
	{
		if (parent)//찾으려는 값이 트리 안에 존재할경우
		{
			//parent에서 current에 해당하는 주소를 NULL로 바꾼다(왼쪽 or 오른쪽)
			if (parent->leftChild == current)
				parent->leftChild = NULL;
			else
				parent->rightChild = NULL;
		}
		else //찾으려는 값이 루트 노드일경우
			*node = NULL;
	}
	//한개일 경우
	else if ((current->leftChild == NULL) || (current->rightChild == NULL))
	{
		//only_child 에다가 한개뿐인 자식 주소를 복사
		if (current->leftChild == NULL)
			only_child = current->leftChild;
		else
			only_child = current->rightChild;
		
		if (parent)// 찾으려는 값이 트리안에 존재할경우
		{//부모에서 지우려는 노드 주소에 only_child 주소로 바꿔쓴다
			if (parent->leftChild == current)
				parent->leftChild = only_child;
			else
				parent->rightChild = only_child;
		}
		else //삭제되는 노드가 루트노드일경우, only_child 노드가 루트로 바뀐다
			*node = only_child;
	}
	//두개
	else
	{
		//current의 오른쪽가지에서 가장 작은 값(가장 왼쪽 자식)을 찾는다
		r_parent = current;
		r_current = current->rightChild;
		while (r_current->leftChild != NULL)
		{
			r_parent = r_current;
			r_current = r_current->leftChild;
		}

		//r_current를 current 자리에 넣기 위해서 r_parent 와 r_current의 연결을 끊는다
		//r_parent 의 왼쪽/오른쪽에 따라서 연결을 끊는다
		if (r_parent->leftChild == r_current)
			r_parent->leftChild = r_current->rightChild;
		else
			r_parent->rightChild = r_current->rightChild;
			// 왼쪽 끝까지 내려왔지만 그 끝에 rightChild가 있을 수 있으므로 NULL이 아닌 rightChild를 대입

		//current 값을 r_current로 대체한다, 주소또한 그렇게 한다
		current->data.key = r_current->data.key;
		current = r_current;
	}
	free(current);
	printf("삭제완료\n");
}

void preorder(treePointer node)
{
	if (node)
	{
		printf("key: %d ", node->data.key);
		printf("data: %c \n", node->data.item);
		preorder(node->leftChild);
		preorder(node->rightChild);
	}
}
