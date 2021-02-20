#include<bits/stdc++.h>
using namespace std;
const int MAXN=200000+50;
const int DEG=20;
int n,k,rt;
int dep[MAXN],party[MAXN],maxdep[MAXN],maxpos[MAXN],maxdis[MAXN];
vector<int> E[MAXN];
int anc[MAXN][DEG];

void getanc()
{
	for (int i=1;i<DEG;i++)
		for (int j=1;j<=n;j++)
			anc[j][i]=anc[anc[j][i-1]][i-1];
} 

int swim(int x,int H)
{
	for (int i=0;H>0;i++)
	{
		if (H&1) x=anc[x][i];
		H/=2;
	}
	return x;
}

int LCA(int u,int v)
{
	if (dep[u]<dep[v]) swap(u,v);
	u=swim(u,dep[u]-dep[v]);
	if (u==v) return u;//不知道为什么总是忘掉这句话(╯▔皿▔)╯ 
	for (int i=DEG-1;i>=0;i--)
	{
		if (anc[u][i]!=anc[v][i])
		{
			u=anc[u][i];
			v=anc[v][i];
		}
	}
	return (anc[u][0]);
}

void dfs(int x,int d)
{
	dep[x]=d;
	for (int i=0;i<E[x].size();i++)
	{
		int to=E[x][i];
		dfs(to,d+1);
	}  
}

void init()
{
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;i++)
	{
		int p;
		scanf("%d%d",&party[i],&p);
		if (p!=0) E[p].push_back(i);
			else rt=i;
		anc[i][0]=p;
	}
	dfs(rt,0);
	for (int i=1;i<=n;i++) 
		if (maxdep[party[i]]<dep[i]) 
		{
			maxdep[party[i]]=dep[i];
			maxpos[party[i]]=i;
		}
}

void solve()
{
	getanc();
	memset(maxdis,0,sizeof(maxdis));
	for (int i=1;i<=n;i++)
	{
		int np=party[i],mp=maxpos[np];
		int lca=LCA(i,mp);
		int nowdis=-2*dep[lca]+dep[i]+dep[mp];
		maxdis[np]=max(maxdis[np],nowdis);
	}
	for (int i=1;i<=k;i++) printf("%d\n",maxdis[i]); 
}

int main()
{
	init();
	solve();
	return 0;
}
