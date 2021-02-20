#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include <utility>
#define S 0
#define T 2*(m-1)*(n-1)+1
using namespace std;
const int MAXN=1000000;
const int INF=0x7fffffff;
struct edge
{
	int fr,to,len;
};
int n,m,w;
vector<edge> E[MAXN];

void addedge(int u,int v,int w)
{
	//cout<<"!"<<u<<' '<<v<<' '<<w<<endl;
	E[u].push_back((edge){u,v,w});
	E[v].push_back((edge){v,u,w});
}

int dijkstra()
{
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > que;
	int dis[MAXN],vis[MAXN];
	memset(vis,0,sizeof(vis));
	for (int i=S+1;i<=T;i++) dis[i]=INF;
	dis[S]=0;
	que.push(make_pair<int,int>(0,S));
	while (!que.empty())
	{
		int head=que.top().second;que.pop();
		if (!vis[head])
		{
			vis[head]=1;
			for (int i=0;i<E[head].size();i++)
			{
				edge Edge=E[head][i];
				if (!vis[Edge.to] && dis[Edge.to]>dis[Edge.fr]+Edge.len)
				{
					dis[Edge.to]=dis[Edge.fr]+Edge.len;
					que.push(make_pair<int,int>(dis[Edge.to],Edge.to));
				}
			}
		}
	}
	return (dis[T]);
}

void init()
{
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++)	
		for (int j=0;j<m-1;j++)
		{
			scanf("%d",&w);
			if (i==0) addedge(2*(j+1),T,w);
				else if (i==n-1) addedge(S,(n-2)*(m-1)*2+2*j+1,w);
					else addedge((i-1)*(m-1)*2+2*j+1,i*(m-1)*2+2*j+2,w);
		}
	for (int i=0;i<n-1;i++)
		for (int j=0;j<m;j++)
		{
			scanf("%d",&w);
			if (j==0) addedge(S,i*2*(m-1)+1,w);
				else if (j==m-1) addedge((i+1)*2*(m-1),T,w);
					else addedge(i*2*(m-1)+j*2,i*2*(m-1)+2*j+1,w);
		}
	for (int i=0;i<(n-1);i++)
		for (int j=0;j<(m-1);j++) 
		{
			scanf("%d",&w);
			//cout<<i<<' '<<j<<' ';
			addedge(i*2*(m-1)+2*j+1,i*2*(m-1)+2*j+2,w);
		}
}

int main()
{
	init();
	cout<<dijkstra()<<endl;
	return 0;
}
