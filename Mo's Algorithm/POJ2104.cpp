#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAXN=100000+50;
const int MAXM=5000+50;
struct node 
{
	int l,r,k,pos,id,ans;
}q[MAXM];
bool cmp(node x,node y)
{
	return (x.pos==y.pos)?x.r<y.r:x.pos<y.pos;
}
bool cmpid(node x,node y)
{
	return (x.id<y.id);
}
struct discretize
{
	int num,pos;
	bool operator < (const discretize &x) const {return (num<x.num);}
}tmp[MAXN];
int n,m;
int a[MAXN],e[MAXN];
int ori[MAXN];//离散化后的i对应的原数字为ori[i] 

int lowbit(int x)
{
	return (x&(-x));
}

void modify(int p,int x)
{
	while (p<=n)
	{
		e[p]+=x;
		p+=lowbit(p);
	}
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

void init()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) 
	{
		scanf("%d",&tmp[i].num);
		tmp[i].pos=i;
	}
	sort(tmp+1,tmp+n+1);
	for (int i=1,j=0;i<=n;i++)
	{
		if (i==1 || tmp[i].num!=tmp[i-1].num) ++j,ori[j]=tmp[i].num;
		a[tmp[i].pos]=j;
	}
	int block=(int)sqrt(n);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&q[i].l,&q[i].r,&q[i].k);
		q[i].id=i;
		q[i].pos=(q[i].l-1)/block+1;
	}
	sort(q+1,q+m+1,cmp);
}

int binary_search(int k)
{
	int lb=0,ub=n;
	while (ub-lb>1)
	{
		int mid=(ub+lb)>>1;
		if (sum(mid)>=k) ub=mid;else lb=mid;//注意一下二分怎么写 
	}
	return ub;
} 

void solve()
{
	int l=1,r=0;
	memset(e,0,sizeof(e));
	for (int i=1;i<=m;i++)
	{
		while (l<q[i].l) modify(a[l],-1),l++;
		while (l>q[i].l) l--,modify(a[l],1);
		while (r<q[i].r) r++,modify(a[r],1);
		while (r>q[i].r) modify(a[r],-1),r--;
		q[i].ans=binary_search(q[i].k);
	}
	sort(q,q+m+1,cmpid);
	for (int i=1;i<=m;i++) printf("%d\n",ori[q[i].ans]);
}

int main()
{
	init();
	solve();
	return 0;	
} 
