#include<bits/stdc++.h>
using namespace std;
const int MAXN=10000+50;
struct edge
{
	int to,len;
};
int n,m;
vector<edge> E[MAXN];
int vis[MAXN],dis[MAXN],flag;

void addedge(int u,int v,int w)
{
	E[u].push_back((edge){v,w});
}

void init()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int op,a,b,c;
		scanf("%d",&op);
		if (op==1)//a-b>=c
		{
			scanf("%d%d%d",&a,&b,&c);
			addedge(a,b,-c);
		}
		if (op==2)
		{
			scanf("%d%d%d",&a,&b,&c);
			addedge(b,a,c);
		}
		if (op==3)
		{
			scanf("%d%d",&a,&b);
			addedge(a,b,0);addedge(b,a,0);
		}
	}
}

void spfa(int fr)
{
	if (vis[fr])
	{
		flag=1;
		return;
	}
	vis[fr]=1;
	for (int i=0;i<E[fr].size();i++)
	{
		int to=E[fr][i].to,len=E[fr][i].len;
		if (dis[fr]+len<dis[to])
		{
			dis[to]=dis[fr]+len;
			spfa(to);
			if (flag) return;
		}
	}
	vis[fr]=0;
}

void solve()
{
	memset(vis,0,sizeof(vis));
	for (int i=1;i<=n;i++)
	{
		spfa(i);
		if (flag) break;
	}
	puts(flag?"No":"Yes");
}

int main()
{
	init();
	solve();
	return 0;
} 
