#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
using namespace std;
const int INF=1000000+5;
const int MAXN=1000+5;
struct edge
{
	int to,dis;
};
vector<edge> E[MAXN];
int n,p,k;
int inque[MAXN],dis[MAXN];

void addedge(int u,int v,int w)
{
	E[u].push_back((edge){v,w});
	E[v].push_back((edge){u,w});
}

void init()
{
	scanf("%d%d%d",&n,&p,&k);
	for (int i=1;i<=p;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		addedge(u,v,w);
	}
}

int check(int x)
{
	queue<int> que;
	memset(inque,0,sizeof(inque));
	memset(dis,0x7f,sizeof(dis));
	dis[1]=0,inque[1]=1;
	que.push(1);
	while (!que.empty())
	{
		int head=que.front();que.pop();
		inque[head]=0;
		for (int i=0;i<E[head].size();i++)
		{
			int nowlen,to=E[head][i].to;
			if (E[head][i].dis>x) nowlen=1;else nowlen=0;
			if (dis[head]+nowlen<dis[to])
			{
				dis[to]=dis[head]+nowlen;
				if (!inque[to])
				{
					que.push(to);
					inque[to]=1;	
				}
			}
		} 
	}
	if (dis[n]>k) return 0;else return 1;
}

void solve()
{
	int lb=0,ub=INF,ans=-1;
	while (lb<=ub)
	{
		int mid=(lb+ub)>>1;
		if (check(mid)) ub=mid-1,ans=mid;
			else lb=mid+1;
	}
	printf("%d\n",ans);
}

int main()
{
	init();
	solve();
	return 0;
}
