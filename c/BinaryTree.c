#include<stdio.h>
#include<stdlib.h>

/*二叉树结构*/
struct TreeNode{
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
};

/*栈 链式存储实现*/
typedef struct SNode *Stack;
struct SNode{
    struct TreeNode *data;
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
void push(struct TreeNode *data, Stack S){
    struct SNode *newNode;
    newNode = (struct SNode *) malloc(sizeof(struct SNode));
    newNode->data = data;
    //将新节点插入到链表第一个节点
    newNode->next = S->next;
    S->next = newNode;
}

/*弹栈*/
struct TreeNode * pop(Stack S){
    struct SNode *topNode;  //保存要弹出的节点 便于释放空间
    struct TreeNode *topElem;           //保存弹出节点的内容

    if( isEmpty(S) ){
        printf("栈空");
        return NULL;
    }else{
        topNode = S->next;  //topNode保存链表第一个节点
        S->next = topNode->next; //删除链表第一个节点
        topElem = topNode->data;
        free(topNode);
        return topElem;
    }
}

/*访问栈顶元素*/
struct TreeNode * top(Stack S){
    struct TreeNode *topElem;   //保存弹出节点的内容

    if( isEmpty(S) ){
        printf("栈空");
        return NULL;
    }else{
        topElem = S->next->data;
        return topElem;
    }
}

/*队列 链式存储实现*/

//队列节点
struct Node{
    struct TreeNode *data;
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

/*出队*/
struct TreeNode * deleteQ(Queue ptrQ){
    struct Node *frontNode;
    struct TreeNode *frontElem;

    if(ptrQ->front == NULL){    //若队列为空 返回-1
        printf("对列空");
        return -1;
    }
    frontNode = ptrQ->front;
    if(ptrQ->front == ptrQ->rear){  //若队列只有一个元素
        ptrQ->front = ptrQ->rear = NULL;
    }else{
        ptrQ->front = ptrQ->front->next;
    }
    frontElem = frontNode->data;
    free(frontNode);
    return frontElem;
}

/*入队*/
void addQ(struct TreeNode * data, Queue ptrQ){
    struct Node *newNode;
    newNode = (struct Node *) malloc(sizeof(struct Node));
    
    newNode->data = data;
    newNode->next = NULL;

    if(ptrQ->front == NULL){    //如果队列为空
        ptrQ->front = ptrQ->rear = newNode;
    }else{
        ptrQ->rear->next = newNode;
        ptrQ->rear = newNode;
    }
}

/*三种遍历的路径是一样的，
每个几点都经过了三次
第一次是入栈，
第二次是访问完左子树，出现在栈顶，
第三次是访问完右子树，出现在栈顶*/

//先序遍历 递归
void PreOrderTraversal(struct TreeNode *bt){
    if(bt){
        printf("%c ",bt->data);
        PreOrderTraversal(bt->left);
        PreOrderTraversal(bt->right);
    }
}

//先序遍历 循环非递归
void PreOrderTraversal2(struct TreeNode *bt){
    struct TreeNode *now = bt;
    Stack stack = createStack();
    while(now || !isEmpty(stack)){
        while(now){   //一直向左，并将沿途节点压栈
            push(now,stack);
            printf("%c ",now->data);
            now = now->left;
        }
        if(!isEmpty(stack)){
            now = pop(stack);
            now = now->right;//我们在借助循环 用同样的方法遍历now的右子树
        }
   
    }
}

//中序遍历 递归
void InOrderTraversal(struct TreeNode *bt){
    if(bt){
        InOrderTraversal(bt->left);
        printf("%c ",bt->data);
        InOrderTraversal(bt->right);
    }
}

//中序遍历 循环非递归
void InOrderTraversal2(struct TreeNode *bt){
    struct TreeNode *now = bt;
    Stack stack = createStack();
    while(now || !isEmpty(stack)){
        while(now){   //一直向左，并将沿途节点压栈
            push(now,stack);
            now = now->left;
        }
        if(!isEmpty(stack)){
            now = pop(stack);
            printf("%c ", now->data);//这里now的左子树遍历完了
            now = now->right;//我们在借助循环 用同样的方法遍历now的右子树
        }
   
    }
}

//后序遍历 递归
void PostOrderTraversal(struct TreeNode *bt){
    if(bt){
        PostOrderTraversal(bt->left);
        PostOrderTraversal(bt->right);
        printf("%c ",bt->data);
    }
}

//后序遍历 循环非递归
void PostOrderTraversal2(struct TreeNode *bt){
    struct TreeNode *now = bt;      //当前节点
    struct TreeNode *pre = NULL;    //前一次访问的节点

    Stack stack = createStack();
    push(bt,stack);

    while(!isEmpty(stack)){
        now = top(stack);
        if((now->left==NULL && now->right==NULL) ||
            (pre!=NULL && (pre==now->left || pre==now->right))){    //左右孩子都被访问过了
            printf("%c ",now->data);
            pop(stack);
            pre=now;
        }else{
            if(now->right != NULL)
                push(now->right,stack);
            if(now->left != NULL)
                push(now->left,stack);
        }
    }
}

/*层次遍历*/
void LevelOrderTraversal(struct TreeNode *bt){
    Queue q;
    struct TreeNode *t;

    if(!bt)         //空树则返回
        return;

    q = createQ();
    addQ(bt, q);
    while(!isEmpty(q)){
        t = deleteQ(q);
        printf("%c ",t->data);
        if(t->left)
            addQ(t->left,q);
        if(t->right)
            addQ(t->right,q);
    }
}

int main(){
    /*先构造如下结构的二叉树
                          A
                         / \
                        /   \
                       B     C
                      / \   / \
                     D   F G   I
                        /   \
                       E     H
    */
    struct TreeNode a = {'A',NULL,NULL};
    struct TreeNode b = {'B',NULL,NULL};
    struct TreeNode c = {'C',NULL,NULL};
    struct TreeNode d = {'D',NULL,NULL};
    struct TreeNode e = {'E',NULL,NULL};
    struct TreeNode f = {'F',NULL,NULL};
    struct TreeNode g = {'G',NULL,NULL};
    struct TreeNode h = {'H',NULL,NULL};
    struct TreeNode i = {'I',NULL,NULL};

    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &f;
    c.left = &g;
    c.right = &i;
    f.left = &e;
    g.right = &h;

    struct TreeNode *root;
    root = &a;
    //root即为指向树根的指针

    printf("先序递归遍历：");
    PreOrderTraversal(root);
    printf("\n");
    printf("先序循环遍历：");
    PreOrderTraversal2(root);
    printf("\n");

    printf("中序递归遍历：");
    InOrderTraversal(root);
    printf("\n");
    printf("中序循环遍历：");
    InOrderTraversal2(root);
    printf("\n");

    printf("后序递归遍历：");
    PostOrderTraversal(root);
    printf("\n");
    printf("后序循环遍历：");
    PostOrderTraversal2(root);
    printf("\n");

    printf("层次遍历：");
    LevelOrderTraversal(root);
    printf("\n");

    return 0;
}
