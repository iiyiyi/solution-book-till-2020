#include<bits/stdc++.h>
using namespace std;
const int MAXN=300000+50;
struct edge
{
	int to,len;
};
struct node
{
	int a,b,lca,dis;
}plan[MAXN];
int n,m;
vector<edge> E[MAXN];

void addedge(int u,int v,int w)
{
	E[u].push_back((edge){v,w});
	E[v].push_back((edge){u,w});
}

void init()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<n;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		addedge(u,v,w);
	}
	dfs1(1,0);
	dfs2();
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&plan[i].a,&plan[i].b);
		lca(i);
	}
}

int main()
{
	init();
	solve();
	return 0;
}
