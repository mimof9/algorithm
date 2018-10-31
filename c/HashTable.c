#include<stdio.h>
#include<stdlib.h>

/*散列表
	冲突解决方法
		开放地址法：线性探测，平方探测，再散列
		链地址法：
*/
typedef int ElementType;

//哈希函数
int Hash(int key, int size){
	return key%size;
}

typedef struct ListNode *Position,*List;
struct ListNode{
	ElementType Element;
	Position Next;
};

typedef struct HashTbl *HashTable;
struct HashTbl{
	int TableSize;
	List TheLists;
};

//查找
Position Find(ElementType Key, HashTable H){
	Position P;
	int Pos;

	Pos = Hash(Key,H->TableSize);	//哈希获取是那一个链表
	P = H->TheLists[Pos].Next;		//该链表头赋给P
	while(P!=NULL && P->Element!=Key)
		P = P->Next;
	return P;
}

//插入
void Insert(ElementType Key, HashTable H){
	Position P;
	int Pos;

	Pos = Hash(Key,H->TableSize);	//哈希获取是那一个链表
	P = H->TheLists[Pos].Next;		//该链表头赋给P
	
	List newNode = malloc(sizeof(struct ListNode));
	newNode->Element = Key;
	newNode->Next = NULL;

	if(P == NULL)
		H->TheLists[Pos].Next = newNode;
	else{	
		while(P->Next!=NULL)
			P = P->Next;
		P->Next = newNode;
	}
}

int main(){
	//初始化hash表我就手写了
	HashTable H;
	H = malloc(sizeof(struct HashTbl));
	H->TableSize = 13;	
	List tempLists = malloc(H->TableSize*sizeof(struct ListNode));
	for(int i=0;i<13;++i)
		tempLists[i].Next = NULL;
	H->TheLists = tempLists;

	Insert(10,H);
	Insert(100,H);
	Insert(10,H);
	Insert(100,H);
	Insert(10,H);
	Insert(1001,H);

	for(int i=0;i<13;++i){
		printf("%d: ",i);
		Position P = H->TheLists[i].Next;
		while(P){
			printf("->%d ",P->Element);
			P = P->Next;
		}
		printf("\n");
	}

	if(Find(10011,H))
		printf("%d ",Find(10011,H)->Element);
	else
		printf("没找到\n");

	return 0;
}