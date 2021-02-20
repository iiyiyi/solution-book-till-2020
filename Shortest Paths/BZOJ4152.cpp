#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
typedef long long ll;
const ll INF=1e15;
const int MAXN=200000+50;
struct node
{
	int x,y,id;
}p[MAXN];
struct edge
{
	int to,len;
};
vector<edge> E[MAXN];
int n;
priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > > que;
ll dis[MAXN];int vis[MAXN];

bool cmpx(node a,node b){return (a.x<b.x);}
bool cmpy(node a,node b){return (a.y<b.y);}

void addedge(int u,int v,int w)
{
	E[u].push_back((edge){v,w});
	E[v].push_back((edge){u,w});
}

void init()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d%d",&p[i].x,&p[i].y),p[i].id=i;
	sort(p+1,p+n+1,cmpx);
	for (int i=1;i<n;i++) addedge(p[i].id,p[i+1].id,p[i+1].x-p[i].x);
	sort(p+1,p+n+1,cmpy);
	for (int i=1;i<n;i++) addedge(p[i].id,p[i+1].id,p[i+1].y-p[i].y);

}

void solve()
{			
	for (int i=1;i<=n;i++) vis[i]=0,dis[i]=INF;
	dis[1]=0;
	que.push(make_pair<ll,int>(0,1));
	while (!que.empty())
	{
		int head=que.top().second;que.pop();
		vis[head]=1;
		for (int i=0;i<E[head].size();i++)
		{
			edge now=E[head][i];
			if (!vis[now.to] && dis[now.to]>dis[head]+(ll)now.len)
			{
				dis[now.to]=dis[head]+(ll)now.len;
				que.push(make_pair<ll,int>(dis[now.to],now.to));
			}
		}
	}
	printf("%lld",dis[n]);
}

int main()
{
	init();
	solve();
	return 0;
}
