#include<stdio.h>
#include<stdlib.h>

/*单链表反转 给定一个单链表 对每k个节点进行反转*/

struct Node{
	char data;
	struct Node *next;
};

/*创建一个带头节点的空链表*/
struct Node * createList(){
	struct Node *head = (struct Node *) malloc(sizeof(struct Node));
	head->next = NULL;
	return head;
}

/*向链表头插入新节点*/
void insert(struct Node *head, char data){
	struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->next = head->next;
	head->next = newNode;
}

/*遍历链表*/
void print(struct Node *head){
	while(head->next){
		printf("%c ",head->next->data);
		head = head->next;
	}
	printf("\n");
}

/*逆转单链表前k个节点，返回第k个节点的指针(也就是新的第1个节点)*/
void reversal(struct Node *head, int k){
	struct Node *pre,*cur,*next;
	int i = 1;			

	pre = head->next;
	cur = pre->next;

	while(i<k){	//逆转k个节点 执行k-1次
		i++;

		next = cur->next; //记录下一个节点
		cur->next = pre;
		pre = cur;
		cur = next;
	}
	head->next->next = cur;		//把原来的第1个节点指向原来的第k+1个节点
	head->next = pre;			//把头节点指向新的链表的第1个节点(原来的第k个节点)
}

int main(){
	struct Node *head = createList();
	insert(head,'8');
	insert(head,'7');
	insert(head,'6');
	insert(head,'5');
	insert(head,'4');
	insert(head,'3');
	insert(head,'2');
	insert(head,'1');

	printf("链表原型：");
	print(head);

	int k;
	printf("输入逆转长度：");
	scanf("%d%*c",&k);
	printf("逆转链表：");

	//求出循环次数
	struct Node* tmp = head;
	int circleNum = 0;	
	int cnt = 0;
	while(tmp->next){
		cnt++;
		tmp = tmp->next;
		if(cnt == k){
			cnt = 0;
			circleNum++;
		}
	}

/*
	struct Node* tmp = head->next;
	reversal(head,k);
	struct Node* tmp1 = tmp->next;
	reversal(tmp,k);
	struct Node* tmp2 = tmp1->next;
	reversal(tmp1,k);
	reversal(tmp2,k);
*/
	/*把上面这段代码写成循环 加上次数判断*/
	struct Node* cur = head;
	struct Node* next;
	for(int i=0;i<circleNum-1;i++){
		next = cur->next;
		reversal(cur,k);
		cur = next;
	}
	reversal(next,k);

	print(head);

	return 0;
}