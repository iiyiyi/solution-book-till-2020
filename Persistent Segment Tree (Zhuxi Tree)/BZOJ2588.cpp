#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define lson l,m
#define rson m+1,r
using namespace std;
const int MAXN=100000+500;
const int DEG=20;
int w[MAXN];
vector<int> E[MAXN];
int d,hash[MAXN];
int T[MAXN],tot,sum[MAXN<<5],L[MAXN<<5],R[MAXN<<5];
int anc[MAXN][DEG],dep[MAXN];
int n,m;

/*Chairman Tree*/
int build(int l,int r)
{
	int rt=++tot;
	sum[rt]=0;
	if (l!=r)
	{
		int m=(l+r)>>1;
		L[rt]=build(lson);
		R[rt]=build(rson); 
	}
	return rt;
}

int update(int pre,int l,int r,int x)
{
	int rt=++tot;
	L[rt]=L[pre],R[rt]=R[pre];
	sum[rt]=sum[pre]+1;
	if (l!=r)
	{
		int m=(l+r)>>1;
		if (x<=m) L[rt]=update(L[pre],lson,x);
			else R[rt]=update(R[pre],rson,x);
	}
	return rt;
}

int query(int u,int v,int lca,int lcafa,int l,int r,int k)
{
	if (l==r) return l;
	int num=(sum[L[u]]-sum[L[lca]]+sum[L[v]]-sum[L[lcafa]]);
	int m=(l+r)>>1;
	if (num>=k) return query(L[u],L[v],L[lca],L[lcafa],lson,k);
		else return query(R[u],R[v],R[lca],R[lcafa],rson,k-num);
}

/*LCA*/
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
		H>>=1;
	}
	return x;
}

int LCA(int u,int v)
{
	if (dep[u]<dep[v]) swap(u,v);
	u=swim(u,dep[u]-dep[v]);
	if (u==v) return u;
	for (int i=DEG-1;i>=0;i--)
	{
		if (anc[u][i]!=anc[v][i])
		{
			u=anc[u][i];
			v=anc[v][i];
		}
	}
	return anc[u][0];
}
 
/*main*/
void dfs(int u,int pa,int depth)
{ 
	anc[u][0]=pa;
	dep[u]=depth;
	int x=lower_bound(hash+1,hash+d+1,w[u])-hash;
	T[u]=update(T[pa],1,d,x);
	for (int i=0;i<E[u].size();i++)
		if (E[u][i]!=pa) dfs(E[u][i],u,depth+1);
}

void init()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&w[i]),hash[i]=w[i];
	sort(hash+1,hash+n+1);
	d=unique(hash+1,hash+n+1)-(hash+1);
	
	for (int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		E[u].push_back(v);
		E[v].push_back(u);
	}

	
	tot=0;
	T[1]=build(1,d);//对于根先建立主席树
}

void solve()
{
	getanc();
	int preans=0;
	for (int i=0;i<m;i++)
	{
		int u,v,k;
		scanf("%d%d%d",&u,&v,&k);
		u=u^preans;
		int lca=LCA(u,v);
		int ans=query(T[u],T[v],T[lca],T[anc[lca][0]],1,d,k);
		printf("%d",hash[ans]);
		if (i!=m-1) printf("\n");
		preans=hash[ans];
	}
}

int main()
{
	init();
	dfs(1,0,1);
	solve();
	return 0;
}
