#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector> 
#include<queue>
#define S 0
#define T n+2
using namespace std;
struct node
{
	int to,pos,cap,val;	
};
const int MAXM=10000+50;
const int MAXN=1000+50;
const int INF=0x7fffffff;
int n,m,a[MAXN],s[MAXM],t[MAXM],c[MAXM];
int pre[MAXN],preedge[MAXN];
vector<node> E[MAXN];

void addedge(int u,int v,int ca,int va)
{
	E[u].push_back((node){v,E[v].size(),ca,va});
	E[v].push_back((node){u,E[u].size()-1,0,-va});
}

int SPFA()
{
	queue<int> que;
	int vis[MAXN],dis[MAXN];
	memset(vis,0,sizeof(vis));
	memset(pre,-1,sizeof(pre));
	for (int i=S;i<=T;i++) dis[i]=INF;
	que.push(0);
	vis[0]=1;
	dis[0]=0;
	while (!que.empty())
	{
		int head=que.front();que.pop();
		vis[head]=0;
		for (int i=0;i<E[head].size();i++)
		{
			node &tmp=E[head][i];
			if (tmp.cap>0 && dis[tmp.to]>dis[head]+tmp.val)
			{
				dis[tmp.to]=dis[head]+tmp.val;
				pre[tmp.to]=head;
				preedge[tmp.to]=i;
				
				{
					que.push(tmp.to);
					vis[tmp.to]=0;
				}
			}
		}
	}
	if (dis[T]==INF) return 0;else return 1;
} 

int mcf()
{
	int flow=0;
	int ans=0;
	while (SPFA())
	{
		int f=INF;
		for (int i=T;pre[i]!=-1;i=pre[i])
		{
			node &tmp=E[pre[i]][preedge[i]];
			f=min(f,tmp.cap); 
		}
		for (int i=T;pre[i]!=-1;i=pre[i])
		{
			node &tmp=E[pre[i]][preedge[i]];
			tmp.cap-=f;
			E[tmp.to][tmp.pos].cap+=f;
			ans+=f*tmp.val;
		}
	}
	return ans;
}

void init()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=m;i++) scanf("%d%d%d",&s[i],&t[i],&c[i]);
}

void build()
{
	a[0]=a[n+1]=0;
	for (int i=1;i<=n+1;i++)
	{
		int c=a[i]-a[i-1];
		if (c>0) addedge(S,i,c,0);
		if (c<0) addedge(i,T,-c,0);
	}
	for (int i=1;i<=m;i++)
		addedge(s[i],t[i]+1,INF,c[i]);
	for (int i=1;i<=n;i++) addedge(i+1,i,INF,0);
}

int main()
{
	init();
	build();
	cout<<mcf()<<endl;
	return 0;
}
