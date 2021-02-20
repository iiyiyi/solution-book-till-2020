#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN=500000+50;
const int DEG=20;
vector<int> E[MAXN];
int start[MAXN],end[MAXN];
int n,num[MAXN],e[MAXN];
int anc[MAXN][DEG],dep[MAXN];
int cnt=0;

void addedge(int u,int v)
{
	E[u].push_back(v);
	E[v].push_back(u);
}

/*树状数组区间修改点查询部分*/ 
int lowbit(int x)
{
	return (x&(-x));
}

void modify(int x,int y,int delta)
{
	if (x<y) swap(x,y);
	x++;
	while (x<MAXN) e[x]^=delta,x+=lowbit(x); 
	while (y<MAXN) e[y]^=delta,y+=lowbit(y);
}

int query(int x)
{
	int ret=0;
	while(x) ret^=e[x],x-=lowbit(x);
	return ret;
}

/*dfs序部分及lca的初始化*/ 
void dfs(int u,int fa,int d)
{
	dep[u]=d;
	anc[u][0]=fa;
	start[u]=++cnt;
	for (int i=0;i<E[u].size();i++)
		if (E[u][i]!=fa) dfs(E[u][i],u,d+1);
	end[u]=cnt;
} 

/*lca部分*/ 
void getanc()
{
	for (int i=1;i<DEG;i++)
		for (int j=1;j<=n;j++)
			anc[j][i]=anc[anc[j][i-1]][i-1];
}

int swim(int u,int H)
{
	int i=0;
	while (H)
	{
		if (H&1) u=anc[u][i];
		i++;
		H>>=1;
	}
	return u;
}

int lca(int u,int v)
{
	if (dep[u]<dep[v]) swap(u,v);
	u=swim(u,dep[u]-dep[v]);
	if (u==v) return u;
	for (int i=DEG-1;i>=0;i--)
	{
		if (anc[u][i]!=anc[v][i])
		{
			u=anc[u][i];
			v=anc[v][i];
		}
	}
	return anc[u][0];
}

/*main*/ 
void init()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&num[i]);
	for (int i=0;i<n-1;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		addedge(u,v);
	}
	dfs(1,0,0);
	getanc(); 
	memset(e,0,sizeof(e));
	for (int i=1;i<=n;i++) modify(start[i],end[i],num[i]);
}

void solve()
{
	int q;
	scanf("%d",&q);
	for (int i=0;i<q;i++)
	{
		char c[2];int u,v;
		scanf("%s%d%d",c,&u,&v);
		if (c[0]=='Q')
		{
			int LCA=lca(u,v);
			int ans=query(start[u])^query(start[v])^num[LCA];
			if (ans) puts("Yes");else puts("No");
		}
		else 
		{
			modify(start[u],end[u],num[u]^v);
			num[u]=v;
		}
	}
}

int main()
{
	init();
	solve(); 
	return 0;
} 
