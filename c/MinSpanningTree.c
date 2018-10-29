#include<stdio.h>
#include<limits.h>

/*最小生成树*/

//建立邻接矩阵
#define vertex 7
#define edge 24

void buildAdjMatrix(int(*am)[vertex], int n,int(*a)[3]){
	for (int i = 0; i < n; ++i)
		am[a[i][0]-1][a[i][1]-1] = a[i][2];
}

//获取未收录定点中dist最小的节点
int getMinDist(int arr[], int S[]){
	int min = INT_MAX;
	int minIndex = -1;
	int i;
	for (i = 0; i < vertex; ++i)
		if(!S[i])			//未收录节点
			if(arr[i]<min){
				min = arr[i];
				minIndex = i;
			}
	return minIndex+1;	//如果不存在 则返回的时0
}

/*Prim算法
	和Dijkstra算法很像
*/
void Prim(int(*am)[vertex], int source){
	int dist[vertex] = {0};	//未收录到最小生成树中顶点 到最小生成树的距离
	for (int i = 0; i < vertex; ++i)
		if(am[source-1][i] != INT_MAX)
			dist[i] = am[source-1][i];
		else
			dist[i] = INT_MAX;
	int S[vertex] = {0};	//最小生成树节点集合
	//0代表不在集合中，1代表在集合中

	//生成树初始化
	//S[source-1] = 1;
	int parent[vertex] = {0};	//0代表没有父节点

	while(1){
		int v = getMinDist(dist, S);	//未收录顶点中dist最小的节点v
		if(!v) break;		//v不存在
		S[v-1] = 1;
		dist[v-1] = 0;	//鉴于这里实现的找到dist最小值的方法 这一步可以不要
		for(int w=0; w<vertex; ++w)
			if(am[v-1][w]!=INT_MAX && S[w] == 0)	//v没有被访问过的邻接点
				if(am[v-1][w] <= dist[w]){		//这里写上=好就不用自己去初始化parent
					dist[w] = am[v-1][w];
					parent[w] = v;		//点w+1的父节点是v
				}
	}

	//最小生成树保存在parent中
	for(int i=0;i<vertex;++i)
		printf("%d ", parent[i]);

}

/*Kruskal算法
	思想是将森林合并乘树
	在加入新边的时候需要判断是否构成回路：
	1.考虑边的两个定点是否都在边集中出现
	2.考虑使用并查集
	
*/


int main(){
	//邻接矩阵
	int am[vertex][vertex];
	for (int i = 0; i < vertex; ++i)
		for(int j = 0; j < vertex; ++j)
			if(i!=j) am[i][j] = INT_MAX;
			else am[i][j] = 0;
	int a[edge][3] = {						
		{1,2,2},{1,3,4},{1,4,1},
		{2,1,2},{2,4,3},{2,5,10},
		{3,1,4},{3,4,2},{3,6,5},
		{4,1,1},{4,2,3},{4,3,2},{4,5,7},{4,6,8},{4,7,4},
		{5,2,10},{5,4,7},{5,7,6},
		{6,3,5},{6,4,8},{6,7,1},
		{7,4,4},{7,5,6},{7,6,1}
	};
	buildAdjMatrix(am,edge,a);
	printf("图的邻接矩阵表示:\n");
	for (int i = 0; i < vertex; ++i){
		for (int j = 0; j < vertex; ++j){
			if(am[i][j] == INT_MAX)
				printf("∞ ");
			else
				printf("%d ", am[i][j]);
		}
		printf("\n");
	}

	//Prim算法
	Prim(am,1);

	return 0;
}