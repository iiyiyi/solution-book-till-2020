#include<bits/stdc++.h>
using namespace std;
const int MAXN=15000+50;
const int MAXM=30000+50;
const int DEG=20;
struct Edge
{
	int u,v,w;
	bool operator < (const Edge &x) const
	{
		return w<x.w;
	};
};
Edge edge[MAXM];
vector<Edge> E[MAXN];
int n,m,k;
int u[MAXN],h[MAXN];
int dep[MAXN],anc[MAXN][DEG],maxlen[MAXN][DEG];

void addedge(int u,int v,int w)
{
	E[u].push_back((Edge){u,v,w});
	E[v].push_back((Edge){v,u,w});
}

int find(int x)
{
	int r=x;
	while (u[r]!=r) r=u[r];
	int tmp;
	while (u[x]!=x)
	{
		tmp=u[x];
		u[x]=r;
		x=tmp;
	}
	return r;
}

void union_set(int fa,int fb)
{
	if (h[fa]>=h[fb])
	{
		u[fb]=fa;
		if (h[fa]==h[fb]) h[fa]++;
	}
	else u[fa]=fb;
}

void dfs(int u,int fa,int d)
{
	anc[u][0]=fa;
	dep[u]=d;
	for (int i=0;i<E[u].size();i++)
	{
		int to=E[u][i].v;
		if (to==fa) continue;
		maxlen[to][0]=E[u][i].w;
		dfs(to,u,d+1);
	}
}

void getanc()
{
	for (int i=1;i<DEG;i++)
		for (int j=1;j<=n;j++)
		{
			anc[j][i]=anc[anc[j][i-1]][i-1];
			maxlen[j][i]=max(maxlen[j][i-1],maxlen[anc[j][i-1]][i-1]);
		}
}

int swim(int x,int H,int &ret)
{
	for (int i=0;H>0;i++)
	{
		if (H&1) ret=max(ret,maxlen[x][i]),x=anc[x][i];//swim过程中不要忘记更新ret 
		H/=2;
	}
	return x;
}

int lca(int a,int b)
{
	int ret=-1;
	if (dep[a]<dep[b]) swap(a,b);
	a=swim(a,dep[a]-dep[b],ret);
	if (a==b) return ret;
	for (int i=DEG-1;i>=0;i--)
	{
		if (anc[a][i]!=anc[b][i])
		{
			ret=max(ret,maxlen[a][i]);
			a=anc[a][i];
			ret=max(ret,maxlen[b][i]);
			b=anc[b][i];
		}
	}
	ret=max(ret,maxlen[a][0]);//最后一条和父亲的连边不要忘记 
	ret=max(ret,maxlen[b][0]);
	return (ret);
}


void init()
{
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=m;i++)
		scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
	for (int i=1;i<=n;i++) u[i]=i,h[i]=1;
}

void kruskal()
{
	sort(edge+1,edge+m+1);
	for (int i=1;i<=m;i++)
	{
		int a=edge[i].u,b=edge[i].v;
		int fa=find(a),fb=find(b);
		if (fa!=fb)
		{
			union_set(fa,fb);
			addedge(edge[i].u,edge[i].v,edge[i].w);
		}
	}
}

void query()
{
	dfs(1,0,1); 
	getanc();
	for (int i=0;i<k;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		printf("%d\n",lca(a,b));
	}
}

int main()
{
	init();
	kruskal();
	query();
	return 0;
} 
