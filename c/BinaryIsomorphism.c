#include<stdio.h>

/*判断两个二叉树是否同构*/

#define MaxTree 10
#define ElementType char
#define Tree int
#define Null -1

struct TreeNode{
	ElementType Element;
	Tree Left;
	Tree Right;
}T1[MaxTree],T2[MaxTree];

/*建立二叉树*/
Tree BuildTree(struct TreeNode T[]){
	int i;
	char cl,cr;	//左右孩子在数组中的位置
	int N;	//树的节点总数
	Tree Root;

	printf("请输入树的节点总数:");
	scanf("%d",&N);
	
	if(N){
		int check[N]; //找到根节点的辅助数组
		for(i=0; i<N; i++)	//初始化辅组数组
			check[i] = 0;

		for(i=0; i<N; i++){
			scanf("%*c%c %c %c",&T[i].Element,&cl,&cr);	//%*c用于读取多余的回车符

			if(cl != '-'){
				T[i].Left = cl - '0';
				check[T[i].Left] = 1;
			}
			else T[i].Left = Null;

			if(cr != '-'){
				T[i].Right = cr - '0';
				check[T[i].Right] = 1;
			}
			else T[i].Right = Null;
		}
		//没有被指向的就是根节点
		for(i=0; i<N; i++)
			if(!check[i])
				break;
		Root = i;
	}
	return Root;
}

/*判断两颗二叉树是否同构 同构返回1 异构返回0*/
int Isomorphic(Tree R1, Tree R2){
	if( R1==Null && R2==Null )	//两棵树都空 同构
		return 1;
	if( (R1==Null && R2!=Null) || (R1!=Null && R2==Null) ) //仅一颗为空 异构
		return 0;
	if( T1[R1].Element != T2[R2].Element ) //树根的值不一样 异构
		return 0;
	if( (T1[R1].Left==Null) && (T2[R2].Left==Null) )	//都没有左子树 递归判断右子树
		return Isomorphic(T1[R1].Right,T2[R2].Right);
	if( ((T1[R1].Left!=Null) && (T2[R2].Left!=Null)) &&		//左孩子一样 判断
		(T1[T1[R1].Left].Element == T2[T2[R2].Left].Element) )
		return (Isomorphic(T1[R1].Left,T2[R2].Left) &&
				Isomorphic(T1[R1].Right,T2[R2].Right));
	else	//当左孩子不一样时 就需要左边和右边一样 右边和左边一样 同时成立
		return (Isomorphic(T1[R1].Left,T2[R2].Right) &&
				Isomorphic(T1[R1].Right,T2[R2].Left));

}

int main(){
	Tree R1,R2;

	R1 = BuildTree(T1);
	R2 = BuildTree(T2);

	if((Isomorphic(R1,R2)))
		printf("两颗二叉树同构\n");
	else
		printf("两颗二叉树异构\n");

	return 0;
}

/*
输入样例：
请输入树的节点总数:8				 A	
A 1 2							/ \
B 3 4						   /   \	
C 5 -						  B	    C
D - -						 / \   /
E 6 -						D   E G
G 7 -						   / / 	
F - -						  F H 
H - -
请输入树的节点总数:8
G - 4							  A
B 7 6							/   \
F - -						   C     B
A 5 1						  /     / \
H - -						 G     E   D
C 0 -						  \   /
D - -						   H F 
E 2 -
*/