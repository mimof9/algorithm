#include<stdio.h>
#include<limits.h>

//建立邻接矩阵
#define vertex 6
#define edge 8

void buildAdjMatrix(int(*am)[vertex], int n,int(*a)[3]){
	for (int i = 0; i < n; ++i)
		am[a[i][0]-1][a[i][1]-1] = a[i][2];
}

/*图的最短路径*/

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

/*迪杰斯特拉算法*/
void Dijkstra(int(*am)[vertex], int source){
	int dist[vertex] = {0};
	for (int i = 0; i < vertex; ++i)
		if(am[source-1][i] != INT_MAX)
			dist[i] = am[source-1][i];
		else
			dist[i] = INT_MAX;
	int S[vertex] = {0};	//已确定最短路径点集合
	//0代表不在集合中，1代表在集合中

	//路径初始化
	S[source-1] = 1;
	int path[vertex] = {0};
	for(int w=0; w<vertex; ++w)
		if(am[source-1][w] != INT_MAX && w != source-1)
			path[w] = source;

	while(1){
		int v = getMinDist(dist, S);	//未收录定点中dist最小的节点v
		if(!v) break;		//v不存在
		S[v-1] = 1;
		for(int w=0; w<vertex; ++w)
			if(am[v-1][w]!=INT_MAX && S[w] == 0)	//v没有被访问过的邻接点
				if(dist[v-1]+am[v-1][w] < dist[w]){
					dist[w] = dist[v-1]+am[v-1][w];
					path[w] = v;		//存的原点到w+1的最短路径的w之前的节点v
				}
	}
	
	//输出source到所有点的最短路径
	for(int e=1;e<=vertex;e++){
		printf("从%d到%d反向路径(权重和%d)：", source,e,dist[e-1]);
		int v = e;				//v初始化为终点
		while(v){
			printf("%d ",v);
			v = path[v-1];
		}
		printf("\n");
	}

}

/*弗洛伊德算法*/
void Floyd(int(*am)[vertex], int D[vertex][vertex], int path[vertex][vertex]){
	int i,j,k;

	for(i=0;i<vertex;++i)
		for(j=0;j<vertex;++j){
			D[i][j] = am[i][j];		//D初始化为邻接矩阵
			path[i][j] = -1;		//路径初始化为-1不可达
		}

	for(k=0;k<vertex;++k)
		for(i=0;i<vertex;++i)
			for(j=0;j<vertex;++j)
				if(D[i][k]!=INT_MAX && D[k][j]!=INT_MAX)	//还是不严谨
					if(D[i][k]+D[k][j] < D[i][j]){
						D[i][j] = D[i][k]+D[k][j];
						path[i][j] = k+1;
					}
}

/*根据路径矩阵输出任意两点间的最短路径*/
void showPass(int path[vertex][vertex], int s, int e){
	/*用路径矩阵输出路径
		递归,方法很直观 
			path[i][j]=k的路径为,递归(i->k)的路径+k+递归(k->j)的路径
	*/

	if(path[s-1][e-1]!=-1){
		showPass(path,s,path[s-1][e-1]);
		printf("%d ",path[s-1][e-1]);
		showPass(path,path[s-1][e-1],e);
	}
}
void showPath(int path[vertex][vertex],int s,int e){
	printf("%d ",s);
	showPass(path,s,e);
	printf("%d\n", e);
}


int main(){
	//邻接矩阵
	int am[vertex][vertex];
	for (int i = 0; i < vertex; ++i)
		for(int j = 0; j < vertex; ++j)
			if(i!=j) am[i][j] = INT_MAX;
			else am[i][j] = 0;
	int a[edge][3] = {						
		{1,3,10},{1,5,30},{1,6,100},
		{2,3,5},
		{3,4,50},
		{4,6,10},
		{5,4,20},{5,6,60}
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

	//迪杰斯特拉算法
	printf("\n迪杰斯特拉算法求得的路径:\n");
	Dijkstra(am,1);

	//弗洛伊德算法
	
	int D[vertex][vertex],path[vertex][vertex];
	Floyd(am,D,path);
	printf("\n弗洛伊德算法求得的距离矩阵:\n");
	for (int i = 0; i < vertex; ++i){
		for(int j = 0; j<vertex;++j)
			printf("%10d ",D[i][j]);
		printf("\n");
	}
	printf("\n弗洛伊德算法求得的路径矩阵:\n");
	for (int i = 0; i < vertex; ++i){
		for(int j = 0; j<vertex;++j)
			printf("%3d ",path[i][j]);
		printf("\n");
	}
	printf("\n弗洛伊德算法求得的最短路径:\n");
	showPath(path,1,6);

	return 0;
}