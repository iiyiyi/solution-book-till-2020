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
    int key;//�ýڵ��ֵ 
    int priority;//���ȼ�
    int size;//�ýڵ��Լ��������Ĵ�С
    int cnt;//��ǰֵ�����ֵĸ��� 
    int lsize()//�����������Ĵ�С 
    {
        if (lson==NULL) return 0;
            else return lson->size;
    }
    int rsize()//�����������Ĵ�С 
    {
        if (rson==NULL) return 0;
            else return rson->size;
    } 
    
    treap()
    {
        size=cnt=1;//�����ʼֵӦ����1������0 
        priority =rand();//����������ȼ�
        lson=rson=NULL; 
    }
}; 
treap* root=NULL;
int n;

void update(treap* &rt)//����Attention����Ҫд��*& 
{
/*��ת����еĲ�������size��С=cnt+������size+������size*/
    rt->size=rt->cnt;
    rt->size+=rt->lsize();
    rt->size+=rt->rsize(); 
} 

void RightRotate(treap* &rt)
{
/*��ͼģ��һ��:D*/ 
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
�����ǰ���ڵ��ǿյģ���ô�½�һ��ƽ������
�����ǰ��x�͸��ڵ����ֵ��Сһ������ֱ���ڸ��ڵ��ۼӸ�����
�����ǰxС�ڸ��ڵ����ֵ����ô�����������������ݺ������ߵ����ȼ����ڸ��ڵ㣬������
�����ǰxС�ڸ��ڵ����ֵ����ô�����������������ݺ�����ұߵ����ȼ����ڸ��ڵ㣬������
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
�����ǰ���ڵ��key����Ҫɾ�����Ǹ�ֵ
��1�������ǰ��ֵ�ĸ�������1����ֱ�Ӽ�ȥcnt��size���ɣ� 
��2������������ǿյģ��⽫���ڵ㱣�����ʱ���������ڵ�����������������ͷ�ԭ�����ڵ��ڴ棻 
��3��������Ϊ��ͬ�� 
��4�����������������Ϊ�գ��Ƚ����ߵ����ȼ���������������ȼ�������������֮������
�����ǰ���ڵ��key����Ҫɾ�����Ǹ�ֵ
��1�����x<key,��������������
��2�� ���������������� 
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
�����ǰ��key����Ҫѯ�ʵ�����ֱ�ӷ����������������Ĵ�С+1��
�����ǰ��key����Ҫѯ�ʵ�����������������ѯ���������� 
�����ǰ��keyС��Ҫѯ�ʵ������򷵻ص�����=����������С+��ǰ�ڵ����ĸ���+�����������е������� 
*/
    if (rt->key==x) return (rt->lsize()+1);
    if (x<rt->key) return (getrank(rt->lson,x));
    return (getrank(rt->rson,x)+rt->lsize()+rt->cnt);
}

int getnum(treap* &rt,int x)   
{
/*
�����Ҫѯ�ʵ��������ڵ�ǰ�ڵ�ķ�Χ(����������+1~����������+��ǰ�ڵ����ĸ���)����ֱ�ӷ��ص�ǰ��key
���Ҫѯ�ʵ�����������������ǰ��������ѯ������
���Ҫѯ�ʵ�����������������ǰ��������ѯ����������Ҫѯ�ʵ�����=����-�������Ĵ�С-��ǰ�ڵ��������ĸ��� 
*/ 
    if (rt->lsize()+1<=x && x<=rt->lsize()+rt->cnt) return rt->key;
    if (x<=rt->lsize()) return getnum(rt->lson,x);
    return getnum(rt->rson,x-rt->lsize()-rt->cnt);
}

int pre(treap* &rt,int x)
/*
�����ǰ�ڵ��ֵС��x����ȡ����ans�нϴ���Ǹ�������������������
�����ǰ�ڵ��ֵ���ڵ���x����������������� 
*/ 
{
    int ans=-INF;
    treap* tmp=rt;
    while (tmp)
    {
        if (tmp->key<x)
        /*���Σ��������ӳ����tmp->key���ֲ��ó���tmp->key...�´�ע��:D*/ 
        {
            ans=max(tmp->key,ans);
            tmp=tmp->rson;
        } 
        else tmp=tmp->lson;
    }
    return ans;
}

int suc(treap* &rt,int x)
/*��pre����*/
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