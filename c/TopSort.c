#include<stdio.h>

/*拓扑排序
	给定AOV网络，找出可行的节点顺序。
	(AOV是activity on vertex)
*/

//队列节点
struct Node{
	int data;
	struct Node *next;
};

struct QNode{
	struct Node *rear;  //对尾
	struct Node *front; //队首
};

typedef struct QNode *Queue;

/*创建队列*/
Queue createQ(){
	Queue q = (Queue) malloc(sizeof(struct QNode));
	q->front = q->rear = NULL;
	return q;
}

/*判断队列是否为空 空返回1 不空返回0*/
int isEmpty(Queue ptrQ){
	return (ptrQ->front == NULL);
}

/*出队*/
int deleteQ(Queue ptrQ){
	struct Node *frontNode;
	int frontElem;

	if(ptrQ->front == NULL){	//若队列为空 返回-1
		printf("对列空");
		return -1;
	}
	frontNode = ptrQ->front;
	if(ptrQ->front == ptrQ->rear){	//若队列只有一个元素
		ptrQ->front = ptrQ->rear = NULL;
	}else{
		ptrQ->front = ptrQ->front->next;
	}
	frontElem = frontNode->data;
	free(frontNode);
	return frontElem;
}

/*入队*/
void addQ(int data, Queue ptrQ){
	struct Node *newNode;
	newNode = (struct Node *) malloc(sizeof(struct Node));
	
	newNode->data = data;
	newNode->next = NULL;

	if(ptrQ->front == NULL){	//如果队列为空
		ptrQ->front = ptrQ->rear = newNode;
	}else{
		ptrQ->rear->next = newNode;
		ptrQ->rear = newNode;
	}
}

//建立邻接矩阵
#define vertex 15
#define edge 14

void buildAdjMatrix(int(*am)[vertex], int n,int(*a)[2]){
	for (int i = 0; i < n; ++i)
		am[a[i][0]-1][a[i][1]-1] = 1;
}

/*输出那些没有前驱节点的点，然后把它从图中删除*/
void TopSort(int(*am)[vertex]){
	//没有前驱也就是入度为0
	int indegree[vertex] = {0};	//每个定点的入度 
	for(int w=0;w<vertex;++w)		//入度初始化
		for(int v=0;v<vertex;++v)
			if(am[v][w]==1)
				indegree[w]++;

	Queue q = createQ();
	for(int v=0; v<vertex; ++v)
		if(indegree[v]==0)
			addQ(v,q);

	int count = 0;

	while(!isEmpty(q)){
		int v = deleteQ(q);
		printf("%d ",v+1);
		count++;	//如果跳出循环后 count不等于节点总数 则有回路
		for(int w=0; w<vertex; ++w)
			if(am[v][w]==1)
				if(--indegree[w]==0)
					addQ(w,q);
	}

	if(count!=vertex)
		printf("\n有回路\n");
}

int main(){
	//邻接矩阵
	int am[vertex][vertex] = {0};
	int a[edge][2] = {						
		{1,3},
		{2,3},{2,13},
		{3,7},
		{4,5},
		{5,6},
		{6,15},
		{7,10},{7,11},{7,12},
		{8,9},
		{9,10},{9,11},
		{10,14},
	};
	buildAdjMatrix(am,edge,a);
	printf("图的邻接矩阵表示:\n");
	for (int i = 0; i < vertex; ++i)
	{
		for (int j = 0; j < vertex; ++j)
			printf("%d ", am[i][j]);
		printf("\n");
	}
	//邻接矩阵

	//拓扑排序
	printf("\n拓扑排序：");
	TopSort(am);
	printf("\n");
	
	return 0;
}