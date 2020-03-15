void insert(treePointer *node, int k, iType theItem)
{
    /* if k is in the tree pointed at by node do nothing;
      otherwise add a new node with data = (k, theItem)
      You must define the proper type for iType */
    treePointer ptr, temp = modifiedSearch(*node, k);
    if (temp || !(*node))
    {
        /* k is not in the tree */
        MALLOC(ptr, sizeof (*ptr));
        ptr->data.key = k;
        ptr->data.item = theItem;
        ptr->leftChild = ptr->rightChild = NULL;
        if (*node)   // insert as child of temp
        {
            if (k < temp->data.key)
                temp->leftChild = ptr;
            else
                temp->rightChild = ptr;
        }
        else
            *node = ptr;
    }
}

treePointer modifiedSearch(treePointer node, int k)  
{

/* ① 아래에 modifiedSearch함수를 구현하는 적절한 코드를 작성하시오. */
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
	return result
}
