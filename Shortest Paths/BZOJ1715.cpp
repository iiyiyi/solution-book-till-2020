#include<bits/stdc++.h>
using namespace std;
struct edge
{
	int to,len;
};
const int MAXN=500+5;
vector<edge> E[MAXN];
int f,n,m,w;
int vis[MAXN],dis[MAXN],flag;

void addedge(int s,int e,int t)
{
	E[s].push_back((edge){e,t});
}

void init()
{
	scanf("%d%d%d",&n,&m,&w);
	for (int i=0;i<MAXN;i++) vector<edge>().swap(E[i]); 
	for (int i=1;i<=m;i++)
	{
		int s,e,t;
		scanf("%d%d%d",&s,&e,&t);
		addedge(s,e,t);
		addedge(e,s,t);
	}
	for (int i=1;i<=w;i++)
	{
		int s,e,t;
		scanf("%d%d%d",&s,&e,&t);
		addedge(s,e,-t);
	}
}

void spfa(int u)
{
	if (vis[u])
	{
		flag=1;
		return;
	}
	vis[u]=1;
	for (int i=0;i<E[u].size();i++)
	{
		int to=E[u][i].to,len=E[u][i].len;
		if (dis[to]>dis[u]+len)
		{
			dis[to]=dis[u]+len;
			spfa(to);
			if (flag) return;
		}
	}
	vis[u]=0;
}

void solve()
{
	memset(vis,0,sizeof(vis));
	flag=0;
	for (int i=1;i<=n;i++)
	{
		spfa(i);
		if (flag) break; 
	} 
	puts(flag?"YES":"NO");
}

int main()
{
	scanf("%d",&f);
	while (f--)
	{	
		init();
		solve();
	}

	return 0;
}

//1347136368
//ayaoyaolunar
