#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXM=200+5;
const int MAXN=1000+50;
const ll INF=1e16;
struct node
{
	ll dis[MAXM][MAXM];
	
}f,result,origin;
int id[MAXN],cnt;
int n,t,s,e;
node operator * (node a,node b)
{
	node c;
	for (int i=1;i<=cnt;i++)
		for (int j=1;j<=cnt;j++) c.dis[i][j]=INF;
	for (int k=1;k<=cnt;k++)
		for (int i=1;i<=cnt;i++)
			for (int j=1;j<=cnt;j++)
				c.dis[i][j]=min(c.dis[i][j],a.dis[i][k]+b.dis[k][j]);
	return c;
}

int getnum(int x)
{
	if (id[x]==-1) 
	{
		id[x]=++cnt;
		return(cnt);
	}
	else return(id[x]);
}

void init()
{
	memset(id,-1,sizeof(id));
	cnt=0;
	scanf("%d%d%d%d",&n,&t,&s,&e);
	memset(f.dis,0,sizeof(f.dis));
	for (int i=1;i<=t;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&w,&u,&v);
		u=getnum(u);
		v=getnum(v);
		f.dis[u][v]=f.dis[v][u]=w;
	}
	for (int i=1;i<=cnt;i++)
		for (int j=1;j<=cnt;j++) if (!f.dis[i][j]) f.dis[i][j]=INF;
} 

void solve()
{
	int k=n-1;
	result=f,origin=f;
	while (k)
	{
		if (k&1) result=result*origin;
		k>>=1;
		origin=origin*origin;
	}
	printf("%lld",result.dis[id[s]][id[e]]); 
}

int main()
{
	init();
	solve();
	return 0;
}
