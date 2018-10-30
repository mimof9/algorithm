#include<stdio.h>

typedef int ElementType;

/*排序 默认排整数从小到大的*/

//交换两个数的整数值
void Swap(ElementType *a, ElementType *b){
	ElementType temp = *a;
	*a = *b;
	*b = temp;
}

/*冒泡排序 稳定
最好情况，初始顺序：O(N)
最坏情况，初始逆序：O(N*N)

待排元素不仅可以放在数组里，在单链表里也没有问题
*/
void Bubble_Sort(ElementType A[], int N){
	int flag;
	for( int p=N-1; p>0; --p){	//需要N-1轮
		flag = 0;
		for( int i=0; i<p; ++i)
			if(A[i]>A[i+1]){
				Swap(&A[i],&A[i+1]);
				flag = 1;
			}
		if( flag == 0 )
			break;	/*一轮比较中没有交换 排序完成*/
	}
}

/*插入排序 稳定
最好情况，初始有序：O(N)
最坏情况，初始逆序：O(N*N)

T(N,I) N是元素个数 I是逆序对
I的平均值为N(N-1)/4 
因此插入排序，冒泡排序(基于交换相邻元素的算法)平均时间复杂度下界(最快)是O(N*N)

但是 如果序列基本有序时，它们就简单又高效
*/
void Insertion_Sort(ElementType A[], int N){
	for( int p=1; p<N; ++p){	//p是待排元素的第一个 也是已经排好的元素个数
		ElementType temp = A[p];		//因为需要交换时 会覆盖 因为需要保留
		int i;
		//从后向前和拍好元素比较 确定插入位置
		for( i=p; i>0 && A[i-1]>temp; --i){		
			A[i] = A[i-1];
		}
		A[i] = temp;
	}
}

/*希尔排序 不稳定
增量序列：D(m)>D(m-1)>...>D(1) = 1
D(k)-间隔有序序列，在执行D(k-1)-间隔排序后，仍然是D(k)-间隔有序的

原始增量序列 D(k)=D(k+1)/2： 增量元素不互质
	最坏情况 O(N*N)			小增量可能根本不起作用
Hibbard增量序列 D(k)=2^k-1:
	最坏情况 O(N^(3/2))
	猜想 平均 O(N^(5/4))
Sedgewick增量序列 {1,5,19,41,109,...}  用9*4^i-9*2^i+1或4^i-3*2^i+1
	猜想 最坏情况 O(N^(4/3))
	猜想 平均     O(N^(7/6))
*/
void Shell_Sort(ElementType A[], int N){
	for(int D=N/2; D>0; D/=2){		//增量序列 将间隔D的序列排有序
		//里面就是一个插入排序
		for( int p=D; p<N; ++p){	
			ElementType temp = A[p];
			int i;
			//不能写i>0 这里D!=1 i>0不等价i>=D
			for( i=p; i>=D && A[i-D]>temp; i-=D){		
				A[i] = A[i-D];
			}
			A[i] = temp;
		}
	}
}

//线性扫描找最小元素
int ScanForMin(ElementType A[], int s, int e){
	int min = A[s];
	int minI = s;
	for(int i=s+1; i<=e; ++i)
		if(A[i] < min){
			min = A[i];
			minI = i;
		}
	return minI;
}

/*选择排序 不稳定
	每次从待排序列中找到最小元素，交换到已排序列的最后。
	一次操作确定一个元素的最终位置。
	因此，如何提高查找最小元素的效率成了关键

	简单的线性扫描：O(N*N)
*/
void Selection_Sort(ElementType A[], int N){
	for( int i=0; i<N-1; ++i){
		int minI = ScanForMin(A, i, N-1);	//从A[i]到A[N-1]找出最小元素的位置
		Swap(&A[i],&A[minI]);	//将为排序部分的最小元换到有序部分的最后
	}
}

/*堆排序 不稳定
	思想，从小到大就建立大顶堆，每次将A[0]换到末尾，堆的规模减一。
	平均时间复杂度 O(NlogN) 比NlogN稍微要好一些
	尽管如此 实际效果不如用Sedgewick增量序列的希尔排序要好
*/
//调整算法 e为树的结尾序号从0开始
void PercDown(ElementType A[], int root, int e){
	ElementType temp = A[root];
	int i;
	for(i=root; 2*i+1<=e; ){	//有左孩子的时候
		int maxChild = 2*i+1;
		if(2*i+2 <= e && A[2*i+2]>A[2*i+1]) //有右孩子且右孩子比左孩子大
			maxChild = 2*i+2;
		if(temp<A[maxChild]){
			A[i] = A[maxChild];
			i = maxChild;
		}else
			break;
	}
	A[i] = temp;
}

void Heap_Sort(ElementType A[], int N){
	for( int i=(N-2)/2; i>=0; --i)	// (N-2)/2为第一个非叶节点序号
		PercDown(A,i,N-1);
	for( int i=N-1; i>0; --i){
		Swap(&A[0],&A[i]);
		PercDown(A,0,i-1);
	}
}

/*归并排序 稳定 需要O(N)空间
	思想：分治+归并 简单二分成左右，在把左右两个有序序列归并

	时间复杂度 O(NlogN) 平均和最坏都是这个
*/
//归并两个有序子列
void Merge(ElementType A[], ElementType TmpA[], int L, int R, int RightEnd){
	//两个子序列都放在A中且相邻 位置由L,R确定
	int LeftEnd = R-1;
	int tmp = L;	//临时数组初始位置
	int totalNum = RightEnd - L + 1;	//归并后一共多少个元素

	while( L<=LeftEnd && R<=RightEnd){
		if(A[L] <= A[R])
			TmpA[tmp++] = A[L++];
		else TmpA[tmp++] = A[R++];
	}
	while(L<=LeftEnd)					
		TmpA[tmp++] = A[L++];
	while(R<=RightEnd)
		TmpA[tmp++] = A[R++];

	for(int i=0; i<totalNum; ++i,RightEnd--)	//从后往前复制totalNum次
		A[RightEnd] = TmpA[RightEnd];
}
//递归算法
void MSort(ElementType A[], ElementType TmpA[], int L, int RightEnd){
	int center;
	if(L<RightEnd){	//不止一个元素时，才需要归并
		center = (L+RightEnd)/2;
		MSort(A,TmpA,L,center);
		MSort(A,TmpA,center+1,RightEnd);
		Merge(A,TmpA,L,center+1,RightEnd);
	}
}
//递归的统一接口
void Merge_Sort(ElementType A[], int N){
	ElementType *TmpA;
	TmpA = malloc(N*sizeof(ElementType));
	if(TmpA != NULL){
		MSort(A,TmpA,0,N-1);
		free(TmpA);
	}else
		printf("空间不足\n");
}

/*快速排序 不稳定 O(logN)
	思想: 分治 
		1.找主元pivot 取头，中，尾的中位数
		2.子集划分 ==pivot停下来交换
		3.小规模数据 小于阈值时，用插入排序

	最好情况：每次主元都正好取到中间，把问题二分 O(NlogN)
	最坏情况：每次主元都是最值，问题规模-1		O(N*N)
*/
//选主元函数
ElementType Median3(ElementType A[], int left, int right){
	int center = (left+right)/2;
	//将头，中，尾按顺序排序
	if(A[left] > A[center])
		Swap(&A[left],&A[center]);
	if(A[left] > A[right])
		Swap(&A[left],&A[right]);
	if(A[center] > A[right])
		Swap(&A[center],&A[right]);
	Swap(&A[center],&A[right-1]);	//把主元放在一边 方便后面编码
	return A[right-1];
}
#define Cutoff 2	//阈值	最小设为2 因为主元最少需要3个元素
void QuickSort(ElementType A[], int left, int right){
	if(Cutoff <= right-left){
		int pivot = Median3(A,left,right);
		int i = left;
		int j = right-1;
		for( ; ;){
			while(A[++i] < pivot){}		//这里就是==也停下来
			while(A[--j] > pivot){}
			if(i < j)
				Swap(&A[i],&A[j]);
			else break;
		}
		Swap(&A[i],&A[right-1]);
		QuickSort(A,left,i-1);
		QuickSort(A,i+1,right);
	}else{
		Insertion_Sort(A+left,right-left+1);
	}
}
//快排统一接口
void Quick_Sort(ElementType A[], int N){
	QuickSort(A,0,N-1);
}

/*表排序
	1.只排可以代表它们的整数
	2.物理排序：(如果需要的话)
		N个数字的排列由若干戈独立的换组成 大数据量交换可以在线性时间内完成
*/

/*以上全是基于比较进行的排序，最坏时间复杂度下界O(NlogN)
	也就是说哪怕最快的算法也能构造出最坏情况让他只能跑到NlogN
*/

/*桶排序 O(N)
	给4万个学生的成绩排名，乘积只有0-100的整数
	那么建101个桶，也就是101个链表
*/

/*基数排序 稳定 O(N) 空间O(B)桶空间 
	分配+收集
	基数个数就是桶的个数，由多少位就分配多少次
	然后用指针串起来进行收集
*/

int main(){

	ElementType A[10] = {-11,25,0,9,7,33,99,-3,0,100};
	
	//Bubble_Sort(A,10);
	//Insertion_Sort(A,10);
	Shell_Sort(A,10);
	//Selection_Sort(A,10);
	//Heap_Sort(A,10);
	//Merge_Sort(A,10);
	//Quick_Sort(A,10);

	for (int i = 0; i < 10; ++i)
		printf("%d ", A[i]);
	printf("\n");
	
	return 0;
}