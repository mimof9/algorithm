#include<stdio.h>
#include<stdlib.h>

/*图的存储方式*/

/*邻接表*/
typedef struct AdjListNode *AdjList;
struct AdjListNode{
	int v;			//点本身
	AdjList adjNode;		//邻接在v上的点
};
//初始化一个有n个节点邻接表
AdjList initAdjListNode(int n){
	AdjList aj = malloc(n*sizeof(struct AdjListNode));
	for (int i = 0; i < n; ++i)
	{
		(aj+i)->v = i+1;			//节点为从1到N
		(aj+i)->adjNode = NULL;
	}
	return aj;
}
//创建一个新邻接表节点
AdjList createAdjListNode(int v){
	AdjList newNode = malloc(sizeof(struct AdjListNode));
	newNode->v = v;
	newNode->adjNode = NULL;

	return newNode;
}
//把一个邻接表节点连接在一个节点上
void addNodeToV(AdjList aj, int v, AdjList aln){
	AdjList temp = aj+v-1;
	while( temp->adjNode )
		temp = temp->adjNode;
	temp->adjNode = aln;
}
//建立邻接表上的连接
void buildConnect(AdjList aj, int n,int(*a)[2]){
	//n为边的数量 无向图乘2
	for (int i = 0; i < n; ++i)
		addNodeToV(aj,a[i][0],createAdjListNode(a[i][1]));
}

//建立邻接矩阵
const int vNum = 3;
void buildAdjMatrix(int(*am)[vNum], int n,int(*a)[2]){
	for (int i = 0; i < n; ++i)
		am[a[i][0]-1][a[i][1]-1] = 1;
}

int main(){

	int a[4][2] = {						//写出边
		{1,2},
		{2,1},{2,3},
		{3,2}
	};

	/*邻接矩阵*/
	int am[3][3]={0};
	buildAdjMatrix(am,4,a);

	for (int i = 0; i < vNum; ++i)
	{
		for (int j = 0; j < vNum; ++j)
			printf("%d ", am[i][j]);
		printf("\n");
	}


	//建立邻接表
	AdjList aj = initAdjListNode(vNum);	//创建邻接表
	buildConnect(aj,4,a);				//用边在邻接表中建立关系

	for(int i=0;i<vNum;i++){
		AdjList temp = aj+i;
		while(temp){
			printf("%d ",temp->v);
			temp = temp->adjNode;
		}
		printf("\n");
	}

	return 0;
}
