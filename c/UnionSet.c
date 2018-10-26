#include<stdio.h>

typedef int ElementType;

/*并查集一般实现*/
typedef struct{
	ElementType data;
	int parent;
} SetType;

/*查找x所属集合*/
int find(SetType s[], int len, ElementType x){
	int i;
	for(i=0; i<len && s[i].data!=x; i++)	//找到节点内容为x的位置
		;
	if(i>=len) 		//没找到x
		return -1;
	for( ; s[i].parent >= 0; i = s[i].parent)	//找祖先
		;
	return i;
}

/*集合并运算 注意不能用union 这是关键字*/
void myUnion(SetType s[], int len, ElementType x1, ElementType x2){
	int root1,root2;
	root1 = find(s,len,x1);
	root2 = find(s,len,x2);
	if(root1 != root2)
		s[root2].parent = root1;
}

/*并查集的简化实现：
将N个元素映射到0-N-1 也就是映射成数组下标*/
typedef int SetName; //默认用根节点的下标作为集合名称
typedef int SimpleSetType;

/*简化的find*/
SetName simpleFind(SimpleSetType s[], ElementType x){
	for( ; s[x]>=0; s=s[x])	//向上找祖先
		;
	return x;			//用下标x代表集合名称
}

/*简化的union*/
void simpleUnion(SimpleSetType s[], SetName root1, SetName root2){
	if(root1 != root2)
		s[root2] = root1;
}

/*路径压缩版本的find*/
SetName finalFind(SimpleSetType s[], ElementType x){
	if(s[x]<0)			//找到集合根
		return x;
	else
		//1.找到父节点的根 2.将其赋值为x的根
		//这样下次再找x时只需要一步递归
		return s[x] = finalFind(s,s[x]);
	//上面的代码是尾递归，编译器会自动有化成循环
}

/*按秩归并的union*/
void finalUnion(SimpleSetType s[], SetName root1, SetName root2){
	if(s[root2] < s[root1]){	//root2集合更高
		s[root1] = root2;		//把root1指向root2
	}else{
		if(s[root1] == s[root2])	//如果两集合等高
			s[root1]--;
		s[root2] = root1;		//把root2指向root1
	}
}

//初始化并查集
void Initialization(SimpleSetType s[], int n){
	//s = malloc(n*sizeof(SimpleSetType));
	for(int i=0;i<n;i++)
		s[i] = -1;
}

//连接两个点
void Input_Connection(SimpleSetType s[]){
	ElementType u, v;
	SetName root1, root2;
	scanf("%d %d",&u,&v);
	root1 = finalFind(s,u-1);
	root2 = finalFind(s,v-1);
	if(root1 != root2)
		finalUnion(s,root1,root2);
}

//检查两个点是否连接
void Check_Connection(SimpleSetType s[]){
	ElementType u, v;
	SetName root1, root2;
	scanf("%d %d",&u,&v);
	root1 = finalFind(s,u-1);
	root2 = finalFind(s,v-1);
	if(root1 == root2)
		printf("yes\n");
	else
		printf("no\n");
}

//整个集合有多少个联通集合
void Check_Network(SimpleSetType s[], int n){
	int i,counter = 0;
	for(i=0; i<n; i++)
		if(s[i]<0)
			counter++;

		printf("整个网络有%d个联通集\n",counter);
}

int main(){
	int n;
	char in;
	printf("输入点数:");
	scanf("%d%*c",&n);
	SimpleSetType s[n];
	Initialization(s,n);

	printf("I 2 5：连接2和5\n");
	printf("C 2 5：检查2和5是否连接\n");
	printf("S：程序结束\n");
	do{
		scanf("%c",&in);
		switch(in){
			case 'I':
				Input_Connection(s);
				break;
			case 'C':
				Check_Connection(s);
				break;
			case 'S':
				Check_Network(s,n);
				break;
		}
		scanf("%*c");
	}while(in != 'S');

	return 0;
}

