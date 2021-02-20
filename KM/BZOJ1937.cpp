#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector> 
#include<cmath>
using namespace std;
const int MAXN=55;
const int MAXM=800+50;
const int INF=0x7fffffff;
struct Edge
{
	int u,v,w,t;
}edge[MAXM];
vector<int> E[MAXN];
int val[MAXM][MAXM];
int dep[MAXN],anc[MAXN][20],faedge[MAXN];
int cnt,m,n;

/**build tree**/
void addedge(int u,int v,int w)
{
	edge[++cnt]=(Edge){u,v,w,0};
	E[u].push_back(cnt);
	E[v].push_back(cnt);
}

void dfs(int rt,int fa,int id)
{
	dep[rt]=dep[fa]+1;
	anc[rt][0]=fa;
	faedge[rt]=id;
	for (int i=0;i<E[rt].size();i++)
	{
		int now=E[rt][i];
		if (edge[now].t && edge[now].u!=fa && edge[now].v!=fa)
		{
			if (edge[now].u==rt) dfs(edge[now].v,rt,now);
				else dfs(edge[now].u,rt,now);
		}
	}
}

/*lca*/
int getanc()
{
	for (int i=1;i<20;i++)
		for (int j=1;j<=n;j++)
			anc[j][i]=anc[anc[j][i-1]][i-1];
}

int swim(int u,int H)
{
	int i=0;
	while (H>0)
	{
		if (H&1) u=u[anc][i];
		H>>=1;
		i++;
	}
	return u;
}

int LCA(int u,int v)
{
	if (dep[u]<dep[v]) swap(u,v);
	if (dep[u]!=dep[v]) u=swim(u,dep[u]-dep[v]);
	if (u==v) return u;//不要忘了这句语句
	for (int i=19;i>=0;i--)
	{
		if (anc[u][i]!=anc[v][i])
		{
			u=anc[u][i];
			v=anc[v][i];
		}
	}
	return anc[u][0];
}


/*KM*/

void Addedge(int u,int v,int w)
{
	val[u][v]=max(w,0);//由于两条边的变化量的绝对值之和不可能为负数，则必定设为0 ☆☆☆☆☆☆ 
}

void build(int a,int b,int id)
{
	if (dep[a]<dep[b]) swap(a,b);
	while (a!=b)
	{
		Addedge(faedge[a],id,edge[faedge[a]].w-edge[id].w);
		a=anc[a][0];
	}
}

int fx[MAXM],fy[MAXM],visx[MAXM],visy[MAXM],slack[MAXM],lk[MAXM];

int Hungary_dfs(int u)
{
	visx[u]=1;
	for (int i=1;i<=m;i++)
	{
		int wt=fx[u]+fy[i]-val[u][i];
		if (!visy[i] && wt==0)
		{
			visy[i]=1;
			if (lk[i]==-1 || Hungary_dfs(lk[i]))
			{
				lk[i]=u;
				return 1;
			}
		}
		else slack[i]=min(slack[i],wt);//注意这里是取较小值不是较大 
	}
	return 0;
}

void KM()
{
	memset(lk,-1,sizeof(lk));
	for (int i=1;i<=m;i++)
	{
		fx[i]=-INF;
		fy[i]=0;
		for (int j=1;j<=m;j++) fx[i]=max(fx[i],val[i][j]);
	}
	for (int i=1;i<=m;i++)
	{
		memset(visx,0,sizeof(visx));
		memset(visy,0,sizeof(visy));
		memset(slack,0x3f,sizeof(slack));
		while (!Hungary_dfs(i))
		{
			int delta=INF;
			for (int j=1;j<=m;j++)
				if (!visy[j]) delta=min(delta,slack[j]);
			for (int j=1;j<=m;j++)
			{
				if (visx[j])
				{
					fx[j]-=delta;
					visx[j]=0;
				}
				if (visy[j])
				{
					fy[j]+=delta;
					visy[j]=0;
				}
			}
		}
	}
	int ans=0;
	for (int i=1;i<=m;i++) ans+=(fx[i]+fy[i]);
	printf("%d",ans);
}

/**main part**/
void init()
{
	cnt=0;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		addedge(u,v,w);
	}
	
	for (int i=1;i<=(n-1);i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		for (int j=0;j<E[x].size();j++)
		{
			int id=E[x][j];
			if ((edge[id].u==x && edge[id].v==y)||(edge[id].v==x && edge[id].u==y))
			{
				edge[id].t=1;
				break;
			}
		}
	}
	dfs(1,0,0);//建立以1为根的树，方便后续lca操作。注意仅有树边加入，非树边不加入
}

void solve()
{
	memset(val,0,sizeof(val));
	getanc();
	for (int i=1;i<=m;i++)
	{
		if (!edge[i].t)
		{
			int lca=LCA(edge[i].u,edge[i].v);
			build(edge[i].u,lca,i);
			build(edge[i].v,lca,i);
		}
	}
	KM();
}

int main()
{
	init();
	solve();
	return 0;
}
