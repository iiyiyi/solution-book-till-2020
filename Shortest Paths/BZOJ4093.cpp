#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXK=200+5;
const int MAXN=20000+50;
const ll INF=1e12;
struct node
{
	int to,dis;
};
vector<node> E[MAXN];
int n,m,k,q;
ll d[MAXK][MAXK],dis[MAXK][MAXN];
int id[MAXN],num[MAXN];

void addedge(int u,int v,int w)
{
	E[u].push_back((node){v,w}); 
}

void init()
{
	scanf("%d%d%d%d",&n,&m,&k,&q);
	memset(id,0,sizeof(id));

	for (int i=1;i<=m;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		addedge(u,v,w);
	}
	for (int i=1;i<=k;i++)
	{
		int x;
		scanf("%d",&x);
		id[x]=i,num[i]=x;
	}
}

void prep()
{		
	for (int i=1;i<=k;i++)
		for (int j=1;j<=k;j++)
			d[i][j]=INF;
	for (int i=1;i<=k;i++) d[i][i]=0;
	for (int i=1;i<=k;i++)
	{
		int u=num[i];
		for (int j=E[u].size()-1;j>=0;j--)
		{
			int v=E[u][j].to;
			if (id[v]) d[i][id[v]]=min(d[i][id[v]],(ll)E[u][j].dis);
				else
				{
					for (int _k=E[v].size()-1;_k>=0;_k--)
					{
						int vto=E[v][_k].to;
						if (id[vto] && vto!=num[i]) d[id[u]][id[vto]]=min(d[id[u]][id[vto]],(ll)E[u][j].dis+(ll)E[v][_k].dis);
					}
				}
		}
	}	
	
	for (int _k=1;_k<=k;_k++)
		for (int i=1;i<=k;i++)
			for (int j=1;j<=k;j++)
				if (i!=j && j!=_k && _k!=i) d[i][j]=min(d[i][j],d[i][_k]+d[_k][j]); 
}

void prep2()
{
	for (int i=1;i<=k;i++)
		for (int j=1;j<=n;j++) dis[i][j]=INF;
	for (int i=1;i<=k;i++)
		for (int j=1;j<=k;j++) dis[i][num[j]]=d[i][j];
		
		
		
	for (int i=1;i<=k;i++)
	{
		for (int _k=0;_k<E[num[i]].size();_k++)//注意这里是E[num[i]]不是num[i]，检查了40分钟才发现QAQ
			for (int j=1;j<=k;j++)
			{
				int to=E[num[i]][_k].to;
				dis[j][to]=min(dis[j][to],d[j][i]+E[num[i]][_k].dis);
			}
	}
}

void solve()
{
	int t=0;
	ll totalans=0;
	for (int i=0;i<q;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		ll ans=INF;
		if (id[a]) ans=dis[id[a]][b];
			else
			{
				for (int j=0;j<E[a].size();j++)
				{
					int v=E[a][j].to;
					if (id[v]) ans=min(ans,E[a][j].dis+dis[id[v]][b]);
				}
			}
		if (ans<INF)
		{
			totalans+=ans;
			t++;
		}
	}
	printf("%d\n",t);
	printf("%d",totalans);
}

int main()
{
	init();
	prep();
	prep2();
	solve();
	return 0;
}

/*
TLE的solve，答案是正确的QAQ 
void solve()
{
	int t=0;
	ll totalans=0;
	for (int i=1;i<=q;i++)
	{
		int a,b;
		ll ans=INF;
		scanf("%d%d",&a,&b);
		if (id[a] && id[b]) ans=d[id[a]][id[b]];
		else if (id[a])
		{
			for (int ib=0;ib<rE[b].size();ib++) ans=min(ans,d[id[a]][id[rE[b][ib].to]]+(ll)rE[b][ib].dis);
		}
		else if (id[b])
		{
			for (int ia=0;ia<E[a].size();ia++) ans=min(ans,d[id[E[a][ia].to]][id[b]]+(ll)E[a][ia].dis);
		}
		else
		{
			for (int ia=0;ia<E[a].size();ia++)
				for (int ib=0;ib<rE[b].size();ib++)
				{
					ll now=(ll)E[a][ia].dis+(ll)rE[b][ib].dis;
					now+=d[id[E[a][ia].to]][id[rE[b][ib].to]];
					ans=min(ans,now);
				}
		}
		if (ans!=INF) t++,totalans+=ans;
	}
	printf("%d\n",t);
	printf("%lld",totalans);
}*/ 
