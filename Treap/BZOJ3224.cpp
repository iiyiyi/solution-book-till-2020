#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int INF=0x7fffffff;
struct treap
{
    treap* lson;
    treap* rson;
    int key;//该节点的值 
    int priority;//优先级
    int size;//该节点以及其子树的大小
    int cnt;//当前值的数字的个数 
    int lsize()//返回左子树的大小 
    {
        if (lson==NULL) return 0;
            else return lson->size;
    }
    int rsize()//返回右子树的大小 
    {
        if (rson==NULL) return 0;
            else return rson->size;
    } 
    
    treap()
    {
        size=cnt=1;//这里初始值应该是1而不是0 
        priority =rand();//随机生成优先级
        lson=rson=NULL; 
    }
}; 
treap* root=NULL;
int n;

void update(treap* &rt)//【【Attention】】要写成*& 
{
/*旋转后进行的操作更新size大小=cnt+左子树size+右子树size*/
    rt->size=rt->cnt;
    rt->size+=rt->lsize();
    rt->size+=rt->rsize(); 
} 

void RightRotate(treap* &rt)
{
/*画图模拟一下:D*/ 
    treap* tmp=rt->lson;
    rt->lson=tmp->rson;
    tmp->rson=rt;
    update(rt);
    update(tmp);
    rt=tmp;
}

void LeftRotate(treap* &rt)
{
    treap* tmp=rt->rson;
    rt->rson=tmp->lson;
    tmp->lson=rt;
    update(rt);
    update(tmp);
    rt=tmp;
}

void insert(treap*&rt,int x)
{
/*
如果当前根节点是空的，那么新建一棵平衡树；
如果当前的x和根节点的数值大小一样，则直接在根节点累加个数；
如果当前x小于根节点的数值，那么向左子树搜索。回溯后如果左边的优先级大于根节点，则右旋
如果当前x小于根节点的数值，那么向右子树搜索。回溯后如果右边的优先级大于根节点，则左旋
*/ 
    if (rt==NULL)
    {
        rt=new treap;
        rt->key=x;
    } 
        else if (x==rt->key)
        {
            rt->size++;
            rt->cnt++;
        }
            else if (x<rt->key)
            {
                insert(rt->lson,x);
                if (rt->lson->priority>rt->priority) RightRotate(rt);
                update(rt);
            }
            else
            {
                insert(rt->rson,x);
                if (rt->rson->priority>rt->priority) LeftRotate(rt);
                update(rt);
            }
} 

void del(treap* &rt,int x)
{
/*
如果当前根节点的key就是要删除的那个值
（1）如果当前数值的个数大于1个，直接减去cnt和size即可； 
（2）如果左子树是空的，这将根节点保存给临时变量，根节点等于它的右子树，释放原来根节点内存； 
（3）右子树为空同理； 
（4）如果左右子树均不为空，比较两者的优先级。如果左子树优先级大则右旋，反之左旋。
如果当前根节点的key不是要删除的那个值
（1）如果x<key,则搜索左子树；
（2） 否则搜索右子树。 
*/ 
    if (x==rt->key)
    {
        if (rt->cnt>1)
        {
            rt->cnt--;
            rt->size--;
        }
        else if (rt->lson==NULL)
        {
            treap* tmp=rt;
            rt=rt->rson;
            delete tmp;
        }
        else if (rt->rson==NULL)
        {
            treap* tmp=rt;
            rt=rt->lson;
            delete tmp;
        }
        else
        {
            if (rt->lson->priority>rt->rson->priority)
            {
                RightRotate(rt);
                del(rt->rson,x);
            }
            else
            {
                LeftRotate(rt);
                del(rt->lson,x);
            }
        }
    }
    else
    {
        if (rt->key>x) del(rt->lson,x);
            else del(rt->rson,x);
    }
    if (rt!=NULL) update(rt);
}

int getrank(treap* &rt,int x)
{
/*
如果当前的key等于要询问的数，直接返回排名（左子树的大小+1）
如果当前的key大于要询问的数，进入左子树查询并返回排名 
如果当前的key小于要询问的树，则返回的排名=（左子树大小+当前节点数的个数+它在右子树中的排名） 
*/
    if (rt->key==x) return (rt->lsize()+1);
    if (x<rt->key) return (getrank(rt->lson,x));
    return (getrank(rt->rson,x)+rt->lsize()+rt->cnt);
}

int getnum(treap* &rt,int x)   
{
/*
如果需要询问的排名属于当前节点的范围(左子树个数+1~左子树个数+当前节点数的个数)，则直接返回当前的key
如果要询问的排名在左子树，则前往左子树询问排名
如果要询问的排名在右子树，则前往右子树询问排名，且要询问的排名=排名-左子树的大小-当前节点代表的数的个数 
*/ 
    if (rt->lsize()+1<=x && x<=rt->lsize()+rt->cnt) return rt->key;
    if (x<=rt->lsize()) return getnum(rt->lson,x);
    return getnum(rt->rson,x-rt->lsize()-rt->cnt);
}

int pre(treap* &rt,int x)
/*
如果当前节点的值小于x，则取它和ans中较大的那个，并继续搜索右子树
如果当前节点的值大于等于x，则继续搜索左子树 
*/ 
{
    int ans=-INF;
    treap* tmp=rt;
    while (tmp)
    {
        if (tmp->key<x)
        /*尴尬，这整个子程序的tmp->key都手残敲成了tmp->key...下次注意:D*/ 
        {
            ans=max(tmp->key,ans);
            tmp=tmp->rson;
        } 
        else tmp=tmp->lson;
    }
    return ans;
}

int suc(treap* &rt,int x)
/*与pre类似*/
{
    int ans=INF;
    treap* tmp=rt;
    while (tmp)
    {
        if (tmp->key>x)
        {
            ans=min(tmp->key,ans);
            tmp=tmp->lson;
        }
        else tmp=tmp->rson;
    }
    return ans;
}

void option()
{
    int opt,x;
    scanf("%d%d",&opt,&x);
    if (opt==1) insert(root,x);
    else if (opt==2) del(root,x);
    else if (opt==3) printf("%d\n",getrank(root,x));
    else if (opt==4) printf("%d\n",getnum(root,x));
    else if (opt==5) printf("%d\n",pre(root,x));
    else if (opt==6) printf("%d\n",suc(root,x));  
}

void release(treap* &rt)
{
    if (rt->lson) release(rt->lson);
    if (rt->rson) release(rt->rson);
    free(rt);
} 

int main()
{
    scanf("%d",&n);
    for (int i=0;i<n;i++) option(); 
    release(root);
    return 0;
}