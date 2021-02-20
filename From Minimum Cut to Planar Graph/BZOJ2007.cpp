#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector> 
#include<queue>
#define S 0
#define T (n*n)+1
using namespace std;
typedef long long ll;
const int MAXN=550*550;
const ll INF=1000000000;
struct edge
{
	int fr,to,len;
};
vector<edge> E[MAXN];
int n;

void addedge(int u,int v,int w)
{
	E[u].push_back((edge){u,v,w});
}

int dijkstra()
{
	priority_queue<pair<ll,ll>,vector<pair<ll,ll> >,greater<pair<ll,ll> > > que;
	ll dis[MAXN],vis[MAXN];
	memset(vis,0,sizeof(vis));
	for (int i=S+1;i<=T;i++) dis[i]=INF;
	dis[S]=0;
	que.push(make_pair<ll,ll>(0,S));
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
					que.push(make_pair<ll,ll>(dis[Edge.to],Edge.to));
				}
			}
		}
	}
	return (dis[T]);
}


void init()
{
	scanf("%d",&n);
	int t;
	for (int i=1;i<=n+1;i++)
        for (int j=1;j<=n;j++)
		{
            scanf("%d",&t);
            if (i==1) addedge((i-1)*n+j,n*n+1,t);
				else if (i==n+1) addedge(0,(i-2)*n+j,t);
					else addedge((i-1)*n+j,(i-2)*n+j,t);
        }
        
    for (int i=1;i<=n;i++)
     	for (int j=0;j<=n;j++)
	 	{
        	scanf("%d",&t);
        	if (j==0) addedge(0,(i-1)*n+j+1,t);
				else if (j==n) addedge(i*n,n*n+1,t);
					else addedge((i-1)*n+j,(i-1)*n+j+1,t);
     }
     
    for (int i=1;i<=n+1;i++)
      for (int j=1;j<=n;j++)
	  {
        scanf("%d",&t);
        if (i==1) addedge(n*n+1,(i-1)*n+j,t);
		  	else if (i==n+1) addedge((n-1)*n+j,0,t);
		  		else addedge((i-2)*n+j,(i-1)*n+j,t);
      }     
      
    for (int i=1;i<=n;i++)
      for (int j=0;j<=n;j++)
	  {
        scanf("%d",&t);
        if (j==0) addedge((i-1)*n+j+1,0,t);
		  	else if (j==n) addedge(n*n+1,(i-1)*n+j,t);
			  	else addedge((i-1)*n+j+1,(i-1)*n+j,t);
      }  

}

int main()
{
	init();
	printf("%d\n",dijkstra());
	return 0;
} 
