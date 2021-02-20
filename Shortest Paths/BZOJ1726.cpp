#include<bits/stdc++.h>
using namespace std;
const int MAXR=100000+50;
const int MAXN=5000+50;
const int INF=0x7fffffff;
struct edge
{
	int to;
	int len;
};
vector<edge> E[MAXN];
int n,r,dis[MAXN],inque[MAXN],dis1[MAXN],dis2[MAXN];
int u[MAXR],v[MAXR],w[MAXR];

void addedge(int u,int v,int w)
{
	E[u].push_back((edge){v,w});
	E[v].push_back((edge){u,w});
}

void init()
{
	scanf("%d%d",&n,&r);
	for (int i=1;i<=r;i++)
	{
		scanf("%d%d%d",&u[i],&v[i],&w[i]);
		addedge(u[i],v[i],w[i]);
	}
}

void spfa(int S,int T)
{
	for (int i=1;i<=n;i++) inque[i]=0,dis[i]=INF;
	queue<int> que;
	que.push(S);
	inque[S]=1;dis[S]=0;
	while (!que.empty())
	{
		int head=que.front();que.pop();
		inque[head]=0;
		for (int i=0;i<E[head].size();i++)
		{
			int nowdis=dis[head]+E[head][i].len,to=E[head][i].to;
			if (nowdis<dis[to])
			{
				dis[to]=nowdis;
				if (!inque[to])
				{
					que.push(to);
					inque[to]=1;
				}
			}
		}
	}
}

void solve()
{
	spfa(1,n);
	for (int i=1;i<=n;i++) dis1[i]=dis[i];
	spfa(n,1);
	for (int i=1;i<=n;i++) dis2 [i]=dis[i];
	int mx=dis1[n],ans=INF;
	for (int i=1;i<=r;i++)
	{
		int now=dis1[u[i]]+dis2[v[i]]+w[i];
		if (now!=mx) ans=min(ans,now);
		now=dis1[v[i]]+dis2[u[i]]+w[i];
		if (now!=mx) ans=min(ans,now);
	}
	printf("%d",ans);
}

int main()
{
	init();
	solve();
	return 0;	
} 
