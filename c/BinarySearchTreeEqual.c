#include<stdio.h>
#include<stdlib.h>

/*给定两个序列，判断它们构成得二叉搜索树是否一样*/

/*三种思路：
1：两个序列都建成树，再判断两个树是否一致
2：直接比较两个序列
3：一个序列建成树，用另一个序列和该树比较
*/

typedef struct TreeNode *Tree;
struct TreeNode{
	int v;
	Tree left, right;
	int flag;	//标志是否被找过 初始为0 找过了设为1
};

/*3的具体思路：
按照序列的顺序，把每个节点在树中查找一边，
如果每次搜索经过的节点在序列前都出现过，则一致
否则，某次搜索中遇到序列前未出现的节点，则不一致*/

/*在树t中查找v*/
int check(Tree t, int v){
	if(t->flag){	//根节点查找过
		if(v < t->v)
			return check(t->left,v);
		else if(v > t->v)
			return check(t->right,v);
		else
			return 0;	//v出现了多次 我们认为不一致
	}else{
		if( v == t->v ){
			t->flag = 1;
			return 1;
		}else //根节点和v不同 结果为不一致
			return 0;
	}
}

/*构建二叉搜索树*/
Tree insert(Tree bst, int x){
	if(!bst){	//原树为空
		bst = malloc(sizeof(struct TreeNode));
		bst->v = x;
		bst->left = bst->right = NULL;
	}else //树不空 找要插入元素的位置
		if(x < bst->v)
			bst->left = insert(bst->left,x);
		else if(x > bst->v)
			bst->right = insert(bst->right,x);
		else ;	//如果x已经存在，什么都不做
	return bst;
}

/*先序遍历二叉树*/
void preOrderTraversal(Tree t){
	if(t){
		printf("%d ",t->v);
		preOrderTraversal(t->left);
		preOrderTraversal(t->right);
	}
}

/*重置树中各节点的flag标记*/
void resetT(Tree t){
	if(t->left)
		resetT(t->left);
	if(t->right)
		resetT(t->right);
	t->flag = 0;
}

/*释放树的控件*/
void freeTree(Tree t){
	if(t->left)
		freeTree(t->left);
	if(t->right)
		freeTree(t->right);
	free(t);
}

int main(){
	/*第一个序列写死：3 1 2 4 二叉搜索树如下
				3
			   / \
			  1   4	
			   \
			    2	
	*/
	Tree bst = insert(NULL,3);
	insert(bst,1);
	insert(bst,2);
	insert(bst,4);
	resetT(bst);
	//preOrderTraversal(bst);

	int flag = 1,v; //1代表一致 0代表不一致
	printf("输入4个节点，例如，3 2 1 4：\n");
	for(int i=0;i<4;i++){
		scanf("%d",&v);
		if(!check(bst,v)){
			flag = 0;
			printf("%d ",v);
		}
	}
	if(flag) printf("两个序列构成的二叉搜索树一致\n");
	else printf("两个序列构成的二叉搜索树不一致\n");

	free(bst);
	return 0;
}