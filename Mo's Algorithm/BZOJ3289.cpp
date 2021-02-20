#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
struct node
{
    int num,pos;
    bool operator < (const node &x) const {return num<x.num;}
};
struct queries
{
    int l,r,pos,id,ans;
};
const int MAXN=50000+50;
int n,m,size[MAXN],e[MAXN];
node tmpsize[MAXN];
queries q[MAXN];
bool cmp(queries a,queries b)
{
    return (a.pos==b.pos)?a.r<b.r:a.pos<b.pos;
}
 
bool cmpid(queries a,queries b)
{
    return a.id<b.id;
}
 
int lowbit(int x)
{
    return (x&(-x));
}
 
int sum(int p)
{
    int ret=0;
    while (p>0)
    {
        ret+=e[p];
        p-=lowbit(p);
    } 
    return ret;
}
 
void modify(int p,int x)
{
    while (p<=n)
    {
        e[p]+=x;
        p+=lowbit(p);
    }
}
 
void init()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&tmpsize[i].num);
        tmpsize[i].pos=i;
    }
    sort(tmpsize+1,tmpsize+n+1);
    for (int i=1,j=0;i<=n;i++) 
    {
        if (i==1 || tmpsize[i].num!=tmpsize[i-1].num) j++;
        size[tmpsize[i].pos]=j;
    }
    scanf("%d",&m);
    int block=int(sqrt(n));
    for (int i=1;i<=m;i++)
    {
        scanf("%d%d",&q[i].l,&q[i].r);
        q[i].id=i;
        q[i].pos=(q[i].l-1)/block+1;
    }
    sort(q+1,q+m+1,cmp);
}
 
void query()
{
    memset(e,0,sizeof(e));
    int l=1,r=0,ans=0;
    for (int i=1;i<=m;i++)
    {
        while (l<q[i].l) modify(size[l],-1),ans-=sum(size[l]-1),l++;
        while (l>q[i].l) l--,modify(size[l],1),ans+=sum(size[l]-1);
        while (r>q[i].r) modify(size[r],-1),ans-=r-l-sum(size[r]),r--;
        while (r<q[i].r) r++,modify(size[r],1),ans+=r-l+1-sum(size[r]);
        q[i].ans=ans;
    }
    sort(q+1,q+m+1,cmpid);
    for (int i=1;i<=m;i++) printf("%d\n",q[i].ans);
}
 
int main()
{
    init();
    query();
    return 0;
}
