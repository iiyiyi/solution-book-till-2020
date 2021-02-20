#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lson l,m
#define rson m+1,r
const int MAXN=325754;
using namespace std;
int T[MAXN],v[MAXN],h[MAXN],L[MAXN],R[MAXN];
int cnt,m,n;

int build(int l,int r)
{
	int rt=++cnt;
	if (l==r) v[rt]=l;
	else
	{
		int m=(l+r)>>1;
		L[rt]=build(lson);
		R[rt]=build(rson);
	}
	return rt;
}

int query(int rt,int x,int l,int r)
{
	if (l==r) return rt;
	int m=(l+r)>>1;
	if (x<=m) return query(L[rt],x,lson);
		else return query(R[rt],x,rson);
}

int find(int rt,int x)
{
	int p=query(rt,x,1,n);
	if (x==v[p]) return p;
		else return find(rt,v[p]);
}

void update(int rt,int x,int l,int r)
{
	if (l==r)
	{
		h[rt]++;
		return;
	}
	int m=(l+r)>>1;
	if (x<=m) update(L[rt],x,lson);
		else update(R[rt],x,rson);
}

int modify(int pre,int x,int y,int l,int r)
{
	int rt=++cnt;
	if (l==r)
	{
		v[rt]=y;
		h[rt]=h[pre];//不要忘了秩 
		return rt;
	}
	L[rt]=L[pre],R[rt]=R[pre];
	int m=(l+r)>>1;
	if (x<=m) L[rt]=modify(L[pre],x,y,lson);
		else R[rt]=modify(R[pre],x,y,rson);
	return rt;
}

void union_set(int fa,int fb,int i)
{
	if (h[fa]>h[fb]) swap(fa,fb);
	T[i]=modify(T[i-1],v[fa],v[fb],1,n);//注意这里是v[fa]而不是fa 
	if (h[fa]==h[fb]) update(T[i],v[fb],1,n);
}

void init()
{
	cnt=0;
	scanf("%d%d",&n,&m);
	T[0]=build(1,n);
}

void solve()
{
	for (int i=1;i<=m;i++)
	{
		int op,a,b;
		scanf("%d",&op);
		if (op==1)
		{
			scanf("%d%d",&a,&b);
			T[i]=T[i-1];
			int fa=find(T[i],a),fb=find(T[i],b);
			if (v[fa]!=v[fb]) union_set(fa,fb,i);
		}
		if (op==2)
		{
			scanf("%d",&a);
			T[i]=T[a];
		}
		if (op==3)
		{
			scanf("%d%d",&a,&b);
			T[i]=T[i-1];
			int fa=find(T[i],a),fb=find(T[i],b);
			if (v[fa]==v[fb]) puts("1");else puts("0");
		}
	}
}

int main()
{
	init();
	solve(); 
	return 0;
}
