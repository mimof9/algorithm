#include<stdio.h>

/*栈 链式存储实现*/

typedef struct SNode *Stack;
struct SNode{
	char data;
	struct SNode *next;
};

/*创建一个栈(不含数据的头节点),返回其指针*/
Stack createStack(){
	Stack S;
	S = (Stack) malloc(sizeof(struct SNode));
	S->next = NULL;
	return S;
}

/*判断栈是否为空 空返回1 不空返回0*/
int isEmpty(Stack S){
	return (S->next == NULL);
}

/*压栈*/
void push(char data, Stack S){
	struct SNode *newNode;
	newNode = (struct SNode *) malloc(sizeof(struct SNode));
	newNode->data = data;
	//将新节点插入到链表第一个节点
	newNode->next = S->next;
	S->next = newNode;
}

/*弹栈*/
char pop(Stack S){
	struct SNode *topNode;	//保存要弹出的节点 便于释放空间
	char topElem;			//保存弹出节点的内容

	if( IsEmpty(S) ){
		printf("栈空");
		return NULL;
	}else{
		topNode = S->next;	//topNode保存链表第一个节点
		S->next = topNode->next; //删除链表第一个节点
		topElem = topNode->data;
		free(topNode);
		return topElem;
	}
}

int main(){
	Stack s = CreateStack();
	push('A',s);
	push('B',s);
	printf("%c",pop(s));
	printf("%c",pop(s));
    return 0;
}
