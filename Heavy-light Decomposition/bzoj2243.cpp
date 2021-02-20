#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector> 
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
using namespace std;
const int MAXN=100000+50;
int c[MAXN],n,m;
int lazy[MAXN<<3],sum[MAXN<<3],Lcol[MAXN<<3],Rcol[MAXN<<3];
int fa[MAXN],son[MAXN],size[MAXN],dep[MAXN],top[MAXN],pos[MAXN],rpos[MAXN],cnt;
int tmpl,tmpr,nowlc,nowrc;
vector<int> E[MAXN];

//线段树 
void pushup(int rt)
{
	Lcol[rt]=Lcol[rt<<1];
	Rcol[rt]=Rcol[rt<<1|1];
	lazy[rt]=-1;
	if (lazy[rt<<1] && lazy[rt<<1|1])
		if (lazy[rt<<1]==lazy[rt<<1|1]) lazy[rt]=lazy[rt<<1];
	sum[rt]=sum[rt<<1]+sum[rt<<1|1]-(Rcol[rt<<1]==Lcol[rt<<1|1]?1:0);
}

void pushdown(int rt)
{
	if (lazy[rt]!=-1)
	{
		lazy[rt<<1]=lazy[rt<<1|1]=lazy[rt];
		lazy[rt]=-1;
		sum[rt<<1]=sum[rt<<1|1]=1;
	}
}

void build(int l,int r,int rt)
{
	if (l==r) 
	{
		Lcol[rt]=Rcol[rt]=lazy[rt]=c[rpos[l]];
		sum[rt]=1;
		return;
	}
	lazy[rt]=-1;
	int m=(l+r)>>1;
	if (l<=m) build(lson);
	if (m<r) build(rson);
	pushup(rt);
}

void modify(int L,int R,int cover,int l,int r,int rt)
{
	if (l==r)
	{
		lazy[rt]=cover;
		sum[rt]=1;
		return;
	}
	int m=(l+r)>>1;
	pushdown(rt);
	if (L<=m) modify(L,R,cover,lson);
	if (R>m) modify(L,R,cover,rson);
	pushup(rt);
}

int query(int L,int R,int l,int r,int rt)
{
	if (l==r) 
	{
		if (l<tmpl) tmpl=l,nowlc=lazy[rt];
		if (r>tmpr) tmpr=r,nowrc=lazy[rt];
		return sum[rt];
	}
	int m=(l+r)>>1;
	if (R<=m) return query(L,R,lson);
	if (L>m) return query(L,R,rson);
	int ans=0;
	ans=query(L,R,lson)+query(L,R,rson)-(Rcol[lson]==Lcol[rson]?1:0);
}

//树剖查询
int solve_query(int a,int b,int c,char op)
{
	int ret=0,f1=top[a],f2=top[b];
	int lc=-1,rc=-1;
	while (f1!=f2)
	{
		if (dep[f1]>=dep[f2])
		{
			if (op=='C') modify(pos[f1],pos[a],c,1,n,1);
			else if (op=='Q') 
			{
				tmpl=-1;tmpr=MAXN;
				ret+=query(pos[f1],pos[a],1,n,1);
				if (lc==nowrc) ret--;
				lc=nowlc;
			}
			a=fa[f1];
			f1=top[a];
		}
		else
		{
			if (op=='C') modify(pos[f2],pos[b],c,1,n,1);
			else if (op=='Q') 
			{
				tmpl=-1;tmpr=MAXN;
				ret+=query(pos[f2],pos[b],1,n,1);
				if (rc==nowrc) ret--;
				rc=nowlc;
			}
			b=fa[f2];
			f2=top[b];
		}
	}
	if (dep[f1]>=dep[f2])
	{
		if (op=='C') modify(pos[f1],pos[a],c,1,n,1);
			else if (op=='Q') 
			{
				ret+=query(pos[f1],pos[a],1,n,1);
				if (lc==nowlc) ret--;
				if (rc==nowrc) ret--;
			}
	}
	else
	{
		if (op=='C') modify(pos[f2],pos[b],c,1,n,1);
			else if (op=='Q') 
			{
				ret+=query(pos[f2],pos[b],1,n,1);
				if (lc==nowrc) ret--;
				if (rc==nowlc) ret--;
			}
	}
	if (op=='Q') return ret;
}

//树剖预处理 
void dfs1(int u,int father,int d)
{
	fa[u]=father;
	dep[u]=d;
	son[u]=-1;
	size[u]=1;
	for (int i=0;i<E[u].size();i++)
	{
		int v=E[u][i];
		if (v==fa[u]) continue;
		dfs1(v,u,d+1);
		if (son[u]==-1 || size[son[u]]<size[v]) son[u]=v; 
	}	
} 

void dfs2(int u,int t)
{
	top[u]=t;
	pos[u]=++cnt;
	rpos[cnt]=u;
	if (son[u]!=-1) dfs2(son[u],top[u]);
	for (int i=0;i<E[u].size();i++)
	{
		int v=E[u][i];
		if (v==fa[u] || v==son[u]) continue;
		dfs2(v,v);
	}
}

//主程序 
void init()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&c[i]);
	for (int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		E[u].push_back(v);
		E[v].push_back(u);
	}
}

void query()
{
	dfs1(1,0,1);
	cnt=0;
	dfs2(1,1);
	build(1,n,1);
	for (int i=1;i<=m;i++)
	{
		char str[1];
		int a,b,c=0;
		scanf("%s",str);
		if (str[0]=='C') scanf("%d%d%d",&a,&b,&c);
			else if (str[0]=='Q') scanf("%d%d",&a,&b);
		solve_query(a,b,c,str[0]);
	}
}

int main()
{
	init();
	query();
	return 0;
}
