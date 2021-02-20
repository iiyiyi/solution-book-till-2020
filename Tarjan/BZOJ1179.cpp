#include<bits/stdc++.h>
using namespace std;
const int MAXN=500000+50;
struct edge
{
	int to,len;
};
int n,m,s,p,money[MAXN],bar[MAXN],u[MAXN],v[MAXN];
vector<int> E[MAXN];
vector<edge> rE[MAXN];
stack<int> S;
queue<int> que;
int instack[MAXN],low[MAXN],dfn[MAXN],sum[MAXN],col[MAXN],cnt,tot;
int dis[MAXN],inque[MAXN];

void addedge(int u,int v)
{
	E[u].push_back(v);
}

void addedge2(int u,int v,int w)
{
	rE[u].push_back((edge){v,w});
}

void tarjan(int x)
{
	dfn[x]=low[x]=++cnt;
	instack[x]=1;
	S.push(x);
	for (int i=0;i<E[x].size();i++)
	{
		int to=E[x][i];
		if (!instack[to])
		{
			tarjan(to);
			low[x]=min(low[x],low[to]); 
		}
		else if (instack[to]==1)
		{
			low[x]=min(low[x],dfn[to]);
		}
	}
	
	if (dfn[x]==low[x])
	{
		tot++;
		int tmp;
		do
		{
			tmp=S.top();S.pop();
			sum[tot]+=money[tmp];
			col[tmp]=tot;
			instack[tmp]=2;
		}while (tmp!=x);
	}
}

void spfa(int start)
{
	memset(inque,0,sizeof(inque));
	for (int i=1;i<=tot;i++) dis[i]=0;
	dis[start]=sum[start];
	inque[start]=1;
	que.push(start);
	while (!que.empty())
	{
		int head=que.front();que.pop();
		inque[head]=0;
		for (int i=0;i<rE[head].size();i++)
		{
			int to=rE[head][i].to,len=rE[head][i].len;
			if (dis[to]<dis[head]+len)
			{
				dis[to]=dis[head]+len;
				if (!inque[to])
				{
					inque[to]=1;
					que.push(to);
				}
			}
		}
	}
}

void rebuild()
{
	for (int i=1;i<=m;i++)
		if (col[u[i]]!=col[v[i]]) addedge2(col[u[i]],col[v[i]],sum[col[v[i]]]);
}

void init()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&u[i],&v[i]);
		addedge(u[i],v[i]);
	}
	for (int i=1;i<=n;i++) scanf("%d",&money[i]);
	memset(bar,0,sizeof(bar));
	scanf("%d%d",&s,&p);
	for (int i=1;i<=p;i++)
	{
		int nowp;
		scanf("%d",&nowp);
		bar[nowp]=1;
	}
} 

void solve()
{
	cnt=tot=0;
	memset(instack,0,sizeof(instack));
	for (int i=1;i<=n;i++)
		if (!instack[i]) tarjan(i);
	rebuild();
	spfa(col[s]);
	int ans=-1;
	for (int i=1;i<=n;i++)
		if (bar[i]) ans=max(ans,dis[col[i]]);
	printf("%d",ans);
}

int main()
{
	init();
	solve();
	return 0;
}
