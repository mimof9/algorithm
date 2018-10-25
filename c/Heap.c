#include<stdio.h>
#include<stdlib.h>
#include <limits.h>

/*优先队列 - 堆
主要做两个操作：
1.向里面插入任意元素
2.从中取一个最值，并删除
*/

/*
实现：
1.用数组表示的完全二叉树
2.任一节点的关键字是其子树所有节点的最值
*/

/*最大堆实现*/
typedef int ElementType;				//关键字类型
const ElementType MaxData = INT_MAX;	//关键字最大值
typedef struct Heap *MaxHeap;
struct Heap{
	ElementType *elements;	//存储堆元素的数组
	int capacity;			//数组最大容量
	int size;				//堆当前元素个数
};

/*堆满*/
int isFull(MaxHeap mx){
	return mx->capacity == mx->size;
}

/*堆空*/
int isEmpty(MaxHeap mx){
	return mx->size == 0;
}

/*创建容量为capacity的大顶堆*/
MaxHeap create(int capacity){
	MaxHeap mx = malloc(sizeof(struct Heap));
	mx->elements  = malloc( (capacity+1)*sizeof(ElementType) );
	mx->size = 0;
	mx->capacity = capacity;
	mx->elements[0] = MaxData;	//定义哨兵 为大于堆中所有可能元素的值，便于以后更快操作
	return mx;
}

/*向最大堆中插入关键字k*/
void insert(MaxHeap mx, ElementType k){
	int i;
	if(isFull(mx)){
		printf("最大堆已满\n");
		return;
	}
	i = ++mx->size;	//先把K查到数组最后的位置
	for( ; mx->elements[i/2] < k ; i/=2)	//不断和其祖先比较 有哨兵
		mx->elements[i] = mx->elements[i/2];	//比k小就下沉
	mx->elements[i] = k;
}

/*最大堆的删除*/
ElementType delete(MaxHeap mx){
	int parent, child;
	ElementType maxKey, temp;	//maxkey保存返回的最大值，tmp保存最后一个值
	if(isEmpty(mx)){
		printf("最大对已为空\n");
		return;
	}

	/*先用最后一个元素替代素组的第一个元素，保证完全二叉树*/
	maxKey = mx->elements[1];
	temp = mx->elements[mx->size--];

	/*再从新树根开始，比较其和两个孩子节点的大小*/
	for(parent=1; parent*2<=mx->size; parent=child){//有左孩子就进循环
		child = parent*2;	//child先指向做孩子
		if( child<mx->size && //有右孩子
			mx->elements[child] < mx->elements[child+1]) //右孩子比较大
			child++;
		/*child指向较大的孩子*/
		if( temp >= mx->elements[child])	//比孩子大
			break;
		else
			mx->elements[parent] = mx->elements[child];	//较大的孩子上去
		//循环条件里的parent=child 表示parent下去 也就是交换了位置 继续循环
	}
	mx->elements[parent] = temp;

	return maxKey; 
}

/*堆的建立*/
/*O(n)的算法 调整过程复杂度为树中各节点的高度和
一次性放进数组：先按输入顺序放入数组
调整：再从第一个有孩子的节点(mx->size/2)开始向下调整，知道根节点 
*/
int main(){
	//建堆 一个一个插入进去 时间复杂度O(NlogN)
	printf("%s", "请输入堆中初始节点数(不超过10)：");
	int size;
	scanf("%d%*c",&size);

	MaxHeap mx = create(10);
	int k;
	for(int i=0;i<size;i++){
		printf("输入第%d个元素",i+1);
		scanf("%d",&k);
		insert(mx,k);
	}
	
	for(int i=0;i<size;i++)
		printf("%d ",delete(mx));
	printf("\n");

	return 0;
}
