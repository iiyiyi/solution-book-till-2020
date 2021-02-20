#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define W 0
#define R 1
#define B 2
using namespace std;
const int MAXN=8000+50;
int n,m;
vector<int> E[MAXN*2];
int col[MAXN*2],ans[MAXN*2],cnt;

void addedge(int u,int v)
{
	E[u].push_back(v);
}

int dfs(int u)
{
	col[u]=R;
	col[u^1]=B;
	ans[++cnt]=u;
	for (int i=0;i<E[u].size();i++)
	{
		int v=E[u][i];
		if (col[v]==R) continue;
		if (col[v]==B || !dfs(v)) return 0;
	}
	return 1;
}

void init()
{
	for (int i=0;i<m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		u--;v--;
		addedge(u,v^1);
		addedge(v,u^1);
	}
}

int solve()
{
	memset(col,0,sizeof(col));
	for (int i=0;i<n*2;i++)
		if (!col[i])
		{
			cnt=0;
			if (!dfs(i))
			{
				for (int j=1;j<=cnt;j++) col[ans[j]]=col[ans[j]^1]=W;
				if (!dfs(i^1)) return 0;
			}
		}
	return 1;
}

int main()
{
	while (scanf("%d%d",&n,&m)!=EOF)
	{
		init();
		int flag=solve();
		if (!flag) puts("NIE"); 
			else for (int i=0;i<2*n;i++) if (col[i]==R) printf("%d\n",i+1);
	}
	return 0;
}
