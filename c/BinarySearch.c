#include<stdio.h>

struct StaticTable{
	int length;
	int Element[10];
};

/*二分查找*/
int BinarySearch(struct StaticTable *pSt, int key){
	int left,right,mid;

	left = 0;
	right = pSt->length-1;
	while(left <= right){
		mid = (left+right)/2;
		if(key < pSt->Element[mid])
			right = mid - 1;
		else if(key > pSt->Element[mid])
			left = mid + 1;
		else
			return mid;
	}
	return -1;	//查找失败 返回-1
}

int main(){
	struct StaticTable st = {8,{-11,0,1,2,4,9,22,382}}; //结构体里面声明的数组长度是10 这里初始化的时候只用了8，剩下两个的值默认是0
	struct StaticTable *pst;
	pst = &st;
	printf("%d",BinarySearch(pst, 4));
	return 0;
}
