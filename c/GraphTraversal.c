#include<stdio.h>

//建立邻接矩阵
#define vertex 10
#define edge 16

void buildAdjMatrix(int(*am)[vertex], int n,int(*a)[2]){
	for (int i = 0; i < n; ++i)
		am[a[i][0]-1][a[i][1]-1] = 1;
}

/*深度优先遍历*/
int visited[vertex];
void dfs(int(*am)[vertex], int v){
	printf("%d ", v);
	visited[v-1] = 1;				//节点v对应矩阵下标为v-1
	for(int i = 0; i < vertex; ++i)
	 	if( am[v-1][i] )					//节点v的每个邻接点i
	 		if( !visited[i] )
	 			dfs(am, i+1);		////矩阵下标i对应节点为i+1
}


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

/*广度优先遍历*/
void bfs(int(*am)[vertex], int v){
	Queue q = createQ();
	visited[v-1] = 1;
	addQ(v,q);
	while(!isEmpty(q)){
		int v = deleteQ(q);
		printf("%d ",v);
		for(int i=0; i<vertex; ++i)
			if( am[v-1][i] )
				if( !visited[i] ){
					visited[i] = 1;
					addQ(i+1,q);
				}
	}
}

int main(){
	//邻接矩阵
	int am[vertex][vertex] = {0};
	int a[edge][2] = {						
		{1,2},{1,6},{1,7},
		{2,1},{2,3},{2,4},
		{3,2},{3,4},
		{4,2},{4,3},{4,5},
		{5,4},
		{6,1},
		{7,1},
		{9,10},
		{10,9}
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

	//深度优先遍历
	for(int i = 0; i < vertex; ++i)
		visited[i] = 0;
	printf("深度优先遍历：");
	dfs(am, 1);
	printf("\n");

	//广度优先遍历
	for(int i = 0; i < vertex; ++i)
		visited[i] = 0;
	printf("广度度优先遍历：");
	bfs(am, 1);
	printf("\n");
	
	return 0;
}