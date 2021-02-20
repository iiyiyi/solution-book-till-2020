#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
const int MAXN=100000+50;
vector<int> E[MAXN];
vector<int> tE[MAXN],rtE[MAXN];
stack<int> S;
int x[MAXN],y[MAXN];
int instack[MAXN],low[MAXN],dfn[MAXN],col[MAXN],size[MAXN],cnt,colcnt;
int dis[MAXN],rdis[MAXN],degree1[MAXN],degree2[MAXN];
int vis[MAXN];
int n,m;

void Topology1()
{
	memset(dis,0xef,sizeof(dis));//初始化为-INF 
	queue<int> que;
	dis[col[1]]=size[col[1]];
	for (int i=1;i<=colcnt;i++)
		if (!degree1[i]) que.push(i);
	while (!que.empty())
	{
		int now=que.front();que.pop();
		for (int i=0;i<tE[now].size();i++)
		{
			int to=tE[now][i];
			dis[to]=max(dis[to],dis[now]+size[to]);
			if (!--degree1[to]) que.push(to);
		}
	}
}

void Topology2()
{
	memset(rdis,0xef,sizeof(rdis));
	queue<int> que;
	rdis[col[1]]=size[col[1]];
	for (int i=1;i<=colcnt;i++)
		if (!degree2[i]) que.push(i);
	while (!que.empty())
	{
		int now=que.front();que.pop();
		for (int i=0;i<rtE[now].size();i++)
		{
			int to=rtE[now][i];
			rdis[to]=max(rdis[to],rdis[now]+size[to]);
			if (!--degree2[to]) que.push(to);
		}
	}
}


void tarjan(int u)
{
	dfn[u]=low[u]=++cnt;
	instack[u]=1;
	S.push(u);
	for (int i=0;i<E[u].size();i++)
	{
		int v=E[u][i];
		if (!instack[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
				
		}
		else if (instack[v]==1) low[u]=min(low[u],dfn[v]);
	}
	
	if (dfn[u]==low[u])
	{
		colcnt++;
		int x;
		do
		{
			x=S.top();
			col[x]=colcnt;
			instack[x]=2;
			size[colcnt]++;
			S.pop();
		}while (x!=u);
	}
}

void init()
{
	scanf("%d%d",&n,&m);
	for (int i=0;i<m;i++) 
	{
		scanf("%d%d",&x[i],&y[i]);
		E[x[i]].push_back(y[i]);
	}
	memset(instack,0,sizeof(instack));
	cnt=colcnt=0;
	for (int i=1;i<=n;i++)
		if (!instack[i]) tarjan(i);
	for (int i=0;i<m;i++)
	{
		if (col[x[i]]!=col[y[i]])
		{
			tE[col[x[i]]].push_back(col[y[i]]);
			degree1[col[y[i]]]++;
			rtE[col[y[i]]].push_back(col[x[i]]);
			degree2[col[x[i]]]++;
		}
	}
}

void solve()
{
	memset(dis,0,sizeof(dis));
	memset(rdis,0,sizeof(rdis));
	Topology1();
	Topology2();
	int ans=-1;
	for (int i=0;i<m;i++)
	{
		ans=max(ans,dis[col[x[i]]]+rdis[col[y[i]]]);//注意这里是col[x[i]]不要写成x[i]了 
		ans=max(ans,rdis[col[x[i]]]+dis[col[y[i]]]);
	}
	printf("%d",ans-size[1]);
}

int main()
{
	init();
	solve();
	return 0;
}
