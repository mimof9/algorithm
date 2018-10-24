#include<stdio.h>

/*队列 链式存储实现*/

//队列节点
struct Node{
	char data;
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
char deleteQ(Queue ptrQ){
	struct Node *frontNode;
	char frontElem;

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
void addQ(char data, Queue ptrQ){
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

int main(){
	Queue q = createQ();
	addQ('A',q);
	addQ('B',q);
	printf("%c",deleteQ(q));
	printf("%c",deleteQ(q));
    return 0;
}
