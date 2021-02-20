#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=500000+50;
int u[MAXN],h[MAXN],t[MAXN];
int dep[MAXN];
int tim;
int ans=0,preans=0,n,m;

int find(int x)
{
	while (x!=u[x])	x=u[x];
	return x;
}

void getdep(int x)
{
	if (u[x]==x) 
	{
		dep[x]=0;
		return;
	}
	else getdep(u[x]);
	dep[x]=dep[u[x]]+1;
}

int ask(int x,int y)
{
	int ret=-1;
	getdep(x);
	getdep(y);
	if (dep[x]<dep[y]) swap(x,y);
	while (dep[x]>dep[y])
	{
		ret=max(ret,t[x]);
		x=u[x];
	}
	while (x!=y)
	{
		ret=max(ret,max(t[x],t[y]));
		x=u[x];
		y=u[y];
	}
	return ret;
}

void mintime(int a,int b)
{
	int fa=find(a),fb=find(b);
	if (fa!=fb) ans=0;
		else ans=ask(a,b);
	printf("%d\n",ans);
	preans=ans;
}

void union_set(int a,int b)
{
	++tim;
	int fa=find(a),fb=find(b);
	if (fa!=fb)
	{ 
		if (h[fa]>h[fb])
		{
			t[fb]=tim;
			u[fb]=fa;
		}
		else
		{
			t[fa]=tim;
			u[fa]=fb;
			if (h[fa]==h[fb]) ++h[fb];
		}
	}
}

void init()
{
	memset(dep,0,sizeof(dep));
	for (int i=1;i<=n;i++)
		u[i]=i,h[i]=1;
} 

void solve()
{
	scanf("%d%d",&n,&m);
	tim=0;
	init();
	for (int i=0;i<m;i++)
	{
		int op,a,b;
		scanf("%d%d%d",&op,&a,&b);
		a^=preans;
		b^=preans;
		if (!op) union_set(a,b);
			else mintime(a,b);
	}
} 

int main()
{
	solve();
	return 0;
}
