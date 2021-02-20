#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define S 0
#define T 2*n+1
using namespace std;
const int INF=0x7fffffff;
const int MAXN=(800+50)*2+1;
struct node
{
	int to,pos,cap,cost;
};
int n,m;
vector<node> E[MAXN];
int pre[MAXN],preedge[MAXN];

void addedge(int u,int v,int w,int cos)
{
	E[u].push_back((node){v,E[v].size(),w,cos});
	E[v].push_back((node){u,E[u].size()-1,0,-cos});
}

void init()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		int ai;
		scanf("%d",&ai);
		addedge(S,i+n,1,ai);
		addedge(S,i,1,0);
		addedge(i+n,T,1,0);
	}
	for (int i=0;i<m;i++)
	{
		int ui,vi,wi;
		scanf("%d%d%d",&ui,&vi,&wi);
		if (ui>vi) swap(ui,vi);
		addedge(ui,vi+n,1,wi);
	}
}

int spfa()
{
	queue<int> que;
	int vis[MAXN],in[MAXN],dis[MAXN];
	memset(in,0,sizeof(in));
	memset(pre,-1,sizeof(pre));
	for (int i=S;i<=T;i++) dis[i]=INF;
	que.push(S);
	vis[S]=1;
	dis[S]=0;
	while (!que.empty())
	{
		int head=que.front();que.pop();
		vis[head]=0;
		for (int i=0;i<E[head].size();i++)
		{
			node &tmp=E[head][i];
			if (tmp.cap>0 && dis[tmp.to]>dis[head]+tmp.cost)
			{
				dis[tmp.to]=dis[head]+tmp.cost;
				pre[tmp.to]=head;
				preedge[tmp.to]=i;
				if (!in[tmp.to])
				{
					que.push(tmp.to);
					in[tmp.to]=0;
				}
			}
		}
	}
	if (dis[T]==INF) return 0;else return 1;
	//和dinic不同，不能再tmp.to==T时直接返回，因为要找到最短路 
} 

void mcf()
{
	int ans=0;
	while (spfa())
	{
		int flow=INF; 
		for (int i=T;pre[i]!=-1;i=pre[i])
		{
			flow=min(flow,E[pre[i]][preedge[i]].cap);
		}
		for (int i=T;pre[i]!=-1;i=pre[i])
		{
			node& tmp=E[pre[i]][preedge[i]];
			tmp.cap-=flow;
			E[tmp.to][tmp.pos].cap+=flow;
			ans+=flow*tmp.cost;
		}
	}
	printf("%d",ans);
}

int main()
{
	init();
	mcf();
}
