#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

/*哈夫曼树*/
typedef struct TreeNode *HuffmanTree;
struct TreeNode{
	int weight;
	HuffmanTree left, right;
};

/*最小堆*/
typedef struct TreeNode ElementType;				//关键字类型
const int MinData = INT_MIN;	//关键字最小值
typedef struct Heap *MinHeap;
struct Heap{
	ElementType *elements;	//存储堆元素的数组
	int capacity;			//数组最大容量
	int size;				//堆当前元素个数
};

/*堆满*/
int isFull(MinHeap mh){
	return mh->capacity == mh->size;
}

/*堆空*/
int isEmpty(MinHeap mh){
	return mh->size == 0;
}

/*最小堆建立*/
MinHeap createMinHeap(ElementType *elements, int size, int capacity){
	//一次性放进数组
	MinHeap mh = malloc(sizeof(struct Heap));
	mh->elements  = (struct TreeNode *) malloc( (capacity+1)*sizeof(ElementType) );
	for(int i=1; i<=size; i++)
		mh->elements[i] = elements[i-1];
	mh->size = size;
	mh->capacity = capacity;
	mh->elements[0].weight = MinData;
	
	//调整
	for(int i=mh->size/2; i>0; i--){
		int parent,child;
		ElementType temp = mh->elements[i];
		for(parent=i; parent*2<=mh->size; parent=child){
			child = parent*2;	//child先指向做孩子
			if( child<mh->size && //有右孩子
				mh->elements[child].weight > mh->elements[child+1].weight ) //右孩子比较小
				child++;
			/*child指向较小的孩子*/
			if( temp.weight <= mh->elements[child].weight )	//比孩子小
				break;
			else
				mh->elements[parent] = mh->elements[child];	//较小的孩子上去
		}
		mh->elements[parent] = temp;	

	}

	return mh;
}

/*最小堆的删除*/
ElementType delete(MinHeap mh){
	int parent, child;
	ElementType minKey, temp;
	if(isEmpty(mh)){
		printf("最小堆已为空\n");
		return;
	}

	minKey = mh->elements[1];
	temp = mh->elements[mh->size--];

	for(parent=1; parent*2<=mh->size; parent=child){
		child = parent*2;
		if( child<mh->size && 
			mh->elements[child].weight > mh->elements[child+1].weight)
			child++;
		if( temp.weight <= mh->elements[child].weight) break;
		else mh->elements[parent] = mh->elements[child];
	}
	mh->elements[parent] = temp;
	return minKey;
}

/*向最小堆中插入关键字k*/
void insert(MinHeap mh, ElementType *k){
	int i;
	if(isFull(mh)){
		printf("最小堆已满\n");
		return;
	}
	i = ++(mh->size);	//先把K查到数组最后的位置
	for( ; mh->elements[i/2].weight > k->weight ; i/=2)	//不断和其祖先比较 有哨兵
		mh->elements[i] = mh->elements[i/2];	//比k大就下沉
	mh->elements[i] = *k;
}

/*构造哈夫曼树*/
/*这里需要特别注意的就是 从堆中删除的两个节点 需要另开空间保存下来*/
HuffmanTree Huffman(MinHeap mh){
	HuffmanTree ht;
	struct TreeNode temp;
	HuffmanTree tempPtr;
	int k = mh->size;
	for(int i = 1; i < k; i++){	//做mh->size-1次合并
		//找到两最小权值从树中删除 合并成一个新权值插入树
		ht = malloc(sizeof(struct TreeNode));

		printf("---%d----\n",i);
		
		temp = delete(mh); 
		tempPtr = malloc(sizeof(struct TreeNode));
		tempPtr->weight = temp.weight;
		tempPtr->left = temp.left;
		tempPtr->right = temp.right;
		ht->left = tempPtr;

		temp = delete(mh); 
		tempPtr = malloc(sizeof(struct TreeNode));
		tempPtr->weight = temp.weight;
		tempPtr->left = temp.left;
		tempPtr->right = temp.right;
		ht->right = tempPtr;

		ht->weight = ht->left->weight + ht->right->weight;

		printf("%d %d %d \n", ht->left->weight,ht->right->weight,ht->weight);

		insert(mh,ht);
	}
	temp = delete(mh);
	tempPtr = malloc(sizeof(struct TreeNode));
	tempPtr->weight = temp.weight;
	tempPtr->left = temp.left;
	tempPtr->right = temp.right;
	ht = tempPtr;

	return ht;
}

/*先序遍历哈夫曼树*/
void preOrderTraversal(HuffmanTree ht){
	if(ht){
		if(!ht->left && !ht->right)
			printf("%d ",ht->weight);
		preOrderTraversal(ht->left);
		preOrderTraversal(ht->right);
	}
}

int main(){
	struct TreeNode ks[8] = {
		{33,NULL,NULL},
		{34,NULL,NULL},
		{0,NULL,NULL},
		{-102,NULL,NULL},
		{111,NULL,NULL},
		{7,NULL,NULL},
		{9,NULL,NULL},
		{8,NULL,NULL}
	};
	MinHeap mh = createMinHeap(ks,8,10);
	
	
	/*
	for(int i=0;i<8;i++)
		printf("%d ",delete(mh).weight);
	printf("\n");
	*/

	HuffmanTree ht = Huffman(mh);
	//printf("%d %d %d \n", ht,ht->left,ht->right);
	//printf("%d %d %d \n", ht->weight,ht->left->weight,ht->right->weight);
	preOrderTraversal(ht);

	return 0;
}