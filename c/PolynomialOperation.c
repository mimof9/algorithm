#include<stdio.h>
#include<stdlib.h>

typedef struct PolyNode *Polynomial;
struct PolyNode{
    int coef;   //系数
    int expon;  //指数
    Polynomial link;
};

Polynomial ReadPoly();
void Attach(int c,int e,Polynomial *pRear);
Polynomial Add(Polynomial P1,Polynomial P2);
Polynomial Mult(Polynomial P1,Polynomial P2);
void PrintPoly(Polynomial P);


int main(){
    Polynomial P1,P2,PP,PS;

    P1 = ReadPoly();
    P2 = ReadPoly();

    PS = Add(P1,P2);
    printf("加法结果:");
    PrintPoly(PS);

    PP = Mult(P1,P2);
    printf("\n乘法结果:");
    PrintPoly(PP);

    return 0;
}

/*读多项式*/
Polynomial ReadPoly(){
    Polynomial P,Rear,t;
    int c,e,N;

    printf("请输入多项式项数:");
    scanf("%d",&N);
    //链表头空节点 方便简化Attach函数代码 不用判断Rear是否为NULL
    P = (Polynomial) malloc(sizeof(struct PolyNode));
    P->link = NULL;
    Rear = P;

    while(N--){
        printf("输入项(系数 指数):",N);
        scanf("%d %d",&c,&e);
        Attach(c,e,&Rear);
    }

    //删除链表头空节点
    t = P;
    P = P->link;
    free(t);

    return P;
}

/*向多项式中插入一个新的项*/
void Attach(int c,int e,Polynomial *pRear){
    //创建新节点
    Polynomial P;
    P = (Polynomial) malloc(sizeof(struct PolyNode));
    P->coef = c;
    P->expon = e;
    P->link = NULL;
    //将新节点插入
    (*pRear)->link = P;
    *pRear = P;
}

/*两个多项式相加*/
Polynomial Add(Polynomial P1,Polynomial P2){
    Polynomial t1,t2,P,Rear,t;

    t1 = P1;
    t2 = P2;

    //创建链表头空节点
    P = (Polynomial) malloc(sizeof(struct PolyNode));
    P->link = NULL;
    Rear = P;

    while(t1 && t2){
        if(t1->expon == t2->expon){
            int sum = t1->coef + t2->coef;
            Attach(sum,t1->expon,&Rear);
            t1 = t1->link;
            t2 = t2->link;
        }else if(t1->expon > t2->expon){
            Attach(t1->coef,t1->expon,&Rear);
            t1 = t1->link;
        }else{
            Attach(t2->coef,t2->expon,&Rear);
            t2 = t2->link;
        }
    }
    if(t1 != NULL){
        Rear->link = t1;
    }
    if(t2 != NULL){
        Rear->link = t2;
    }

    //删除链表头空节点
    t = P;
    P = P->link;
    free(t);

    return P;
}

/*两个多项式相乘*/
Polynomial Mult(Polynomial P1,Polynomial P2){
    Polynomial t1,t2,P,Rear,t;
    int c,e;

    if(!P1 || !P2)  //有一个为NULL 返回NULL
        return NULL;

    t1 = P1;
    t2 = P2;
    //创建链表头空节点
    P = (Polynomial) malloc(sizeof(struct PolyNode));
    P->link = NULL;
    Rear = P;

    //P1第一项乘P2 得到P
    while(t2){
        Attach(t1->coef*t2->coef,t1->expon+t2->expon,&Rear);
        t2 = t2->link;
    }
    t1 = t1->link;

    //逐项相乘
    while(t1){
        t2 = P2;
        Rear = P;   //在t2遍历一遍之前 不需要还原Rear 因为乘积指数一定变小   
        while(t2){
                c = t1->coef * t2->coef;
                e = t1->expon + t2->expon;

                /*将结果项插入有序序列中*/
                //找到插入位置 Rear后面
                while(Rear->link && Rear->link->expon>e)
                    Rear = Rear->link;
                //结果项和Rear下一项指数相等
                if(Rear->link && Rear->link->expon == e){
                    if(Rear->link->coef + c)    //系数和不为零 直接在Rear下一项上修改系数
                        Rear->link->coef += c;
                    else{   //系数和为0 删掉该项
                        t = Rear->link;
                        Rear->link = t->link;
                        free(t);
                    }
                }else{  //结果项指数大于Rear下一项指数 插在Rear后
                    t = (Polynomial) malloc(sizeof(struct PolyNode));
                    t->coef = c;
                    t->expon = e;
                    t->link = Rear->link;
                    Rear->link = t;
                    Rear = Rear->link;
                }
                t2 = t2->link;
        }
        t1 = t1->link;
    }

    //删除链表头空节点
    t = P;
    P = P->link;
    free(t);
    return P;
}

/*多项式输出*/
void PrintPoly(Polynomial P){
    int flag = 0;

    if(!P){
        printf("0 0\n");
        return;
    }

    while(P){
        //实现第一项前不输出空格 后面项前面都输出空格
        if(!flag)
            flag = 1;
        else
            printf(" ");
        printf("%d %d",P->coef,P->expon);

        P = P->link;
    }
}
