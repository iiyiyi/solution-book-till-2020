#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define lson l,m
#define rson m+1,r
using namespace std;
const int MAXN=100000+50;
int sum[MAXN<<5],L[MAXN<<5],R[MAXN<<5];
int a[MAXN],hash[MAXN],T[MAXN],tot=0;
int m,n,d;

int build(int l,int r)
{
	int rt=++tot;
	sum[rt]=0;
	if (l<r)
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
		if (x<=m) L[rt]=update(L[rt],lson,x);
			else R[rt]=update(R[rt],rson,x);
	}
	return rt;
}

int query(int lrt,int rrt,int l,int r,int k)
{
	if (l==r) return l;
	int num=sum[L[rrt]]-sum[L[lrt]];
	
    int m=(l+r)>>1;
    if(num>=k)
        return query(L[lrt], L[rrt], lson, k);
    else
        return query(R[lrt], R[rrt], rson, k-num);
}

void init()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		hash[i]=a[i];
	}
	sort(hash+1,hash+n+1);
	d=unique(hash+1,hash+n+1)-hash-1;
	T[0]=build(1,n);
	for (int i=1;i<=n;i++)
	{
		int x=lower_bound(hash,hash+d,a[i])-hash;
		T[i]=update(T[i-1],1,d,x);
	} 
}

void solve()
{ 
	for (int i=0;i<m;i++)
	{
		int l,r,k;
		scanf("%d%d%d",&l,&r,&k);
		int x=query(T[l-1],T[r],1,d,k);
		printf("%d\n",hash[x]);
	}
}

int main()
{
	init();
	solve();
	return 0;
}
