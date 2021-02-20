#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000+5;
int n,m,ans,tmp;
int vis[MAXN];
vector<int> E[MAXN];

void dfs(int u,int T)
{
	for (int i=0;i<E[u].size();i++)
	{
		int v=E[u][i];
		if (vis[v]!=T)
		{
			tmp++;
			vis[v]=T;
			dfs(v,T);
		}
	}
}

void init()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		E[u].push_back(v);
	}
}

void solve()
{
	ans=0;
	memset(vis,0,sizeof(vis));
	for (int i=1;i<=n;i++)
	{
		tmp=0;
		dfs(i,i);
		ans+=tmp;
	}
	ans=(n-1)*n/2-ans;
	printf("%d\n",ans);
}

int main()
{
	init();
	solve();
	return 0;
} 
