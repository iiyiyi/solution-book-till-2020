#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define lson l,m
#define rson m+1,r
using namespace std;
const int MAXN=500000+50;
int n,m,d,a[MAXN],hash[MAXN],tot;
int T[MAXN],L[MAXN<<5],R[MAXN<<5],sum[MAXN<<5];

int build(int l,int r)
{
	int rt=++tot;
	sum[rt]=0;
	if (l!=r)
	{
		int m=(l+r)>>1;
		L[rt]=build(lson);
		R[rt]=build(rson);
	}
	return rt;
}

int update(int pre,int l,int r,int x)
{
	int rt=++tot;
	L[rt]=L[pre],R[rt]=R[pre],sum[rt]=sum[pre]+1;
	if (l!=r)
	{
		int m=(l+r)>>1;
		if (x<=m) L[rt]=update(L[pre],lson,x);
			else R[rt]=update(R[pre],rson,x);
	}
	return rt;
}

int query(int lrt,int rrt,int l,int r,int k)
{
	if (l==r) return l;
	int m=(l+r)>>1;
	if (sum[L[rrt]]-sum[L[lrt]]>k) return query(L[lrt],L[rrt],lson,k);
	if (sum[R[rrt]]-sum[R[lrt]]>k) return query(R[lrt],R[rrt],rson,k);
	return 0; 
} 

void init()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]),hash[i]=a[i];
	sort(hash+1,hash+n+1);
	d=unique(hash+1,hash+n+1)-(hash+1);
	
	tot=0; 
	T[0]=build(1,d);
	for (int i=1;i<=n;i++)
	{
		int x=lower_bound(hash+1,hash+d+1,a[i])-hash;
		//注意离散化之后是从1开始，所以减去的是hash而不是hash+1 
		T[i]=update(T[i-1],1,d,x);
	}
}

void solve()
{
	for (int i=0;i<m;i++)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		int ans=query(T[l-1],T[r],1,d,(r-l+1)>>1);
		printf("%d\n",hash[ans]);
	}
}

int main()
{
	init();
	solve();
	return 0;	
} 
