#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
using namespace std;
const int MAXN=30000+50;
const int INF=0x7fffffff;
vector<int> E[MAXN];
int fa[MAXN],dep[MAXN],size[MAXN],son[MAXN];
int top[MAXN],pos[MAXN];
int w[MAXN];
int cnt=0,n;
int sum[MAXN<<2],maxn[MAXN<<2];
char str[10];

/*线段树部分*/
void pushup(int rt)
{
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];
	maxn[rt]=max(maxn[rt<<1],maxn[rt<<1|1]);
}

void modify(int pos,int delta,int l,int r,int rt)
{
	if (l==r)
	{
		sum[rt]=maxn[rt]=delta;
		return;
	}
	int m=(l+r)>>1;
	if (pos<=m) modify(pos,delta,lson);
	if (pos>m) modify(pos,delta,rson);
	pushup(rt);
}

int query(int sign,int L,int R,int l,int r,int rt)
{
	if (L<=l && r<=R)
	{
		if (sign==1) return sum[rt];else return maxn[rt];
	}
	int m=(l+r)>>1;
	if (sign==1)
	{
		int ret=0;
		if (L<=m) ret+=query(sign,L,R,lson);
		if (R>m) ret+=query(sign,L,R,rson);
		return ret;
	}
	else
	{
		int res=-INF;
		if (L<=m) res=max(res,query(sign,L,R,lson));
    	if (R>m) res=max(res,query(sign,L,R,rson));
		return res;
	}
}

/*树链剖分部分*/
void addedge(int u,int v)
{
	E[u].push_back(v);
	E[v].push_back(u);
}

void dfs1(int u,int pre,int d)
{
	fa[u]=pre;
	dep[u]=d;
	size[u]=1;
	int tmpmax=0,hson=-1;
	for (int i=0;i<E[u].size();i++)
	{
		int to=E[u][i];
		if (to==pre) continue;
		dfs1(to,u,d+1);
		if (size[to]>tmpmax)
		{
			tmpmax=size[to];
			hson=to;
		}
		size[u]+=size[to];
	}
	son[u]=hson;
}

void dfs2(int u,int t)
{
	pos[u]=++cnt;
	top[u]=t;
	if (son[u]==-1) return;
	dfs2(son[u],t);
	for (int i=0;i<E[u].size();i++)
		if (E[u][i]!=son[u] && E[u][i]!=fa[u]) dfs2(E[u][i],E[u][i]);
}

int Que(int sign,int u,int v)
{
	int ans;
	if (sign==1) ans=0;else ans=-INF;
	int f1=top[u],f2=top[v];
	while (f1!=f2)
	{
		if (dep[f1]<dep[f2])
		{
			swap(f1,f2);
			swap(u,v);
		}
		if (sign==1) ans+=query(1,pos[f1],pos[u],1,n,1);
			else ans=max(ans,query(2,pos[f1],pos[u],1,n,1));
		u=fa[f1];
		f1=top[u];
	}
	if (dep[u]>dep[v]) swap(u,v);
	if (sign==1) ans+=query(1,pos[u],pos[v],1,n,1);
			else ans=max(ans,query(2,pos[u],pos[v],1,n,1));
	return ans;
}

/*主程序部分*/ 
void init()
{
	scanf("%d",&n);
	for (int i=0;i<n-1;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		addedge(a,b);
	}
	dfs1(1,0,1);
	dfs2(1,1);
} 

void get_ans()
{
	for (int i=1;i<=n;i++) 
	{
		scanf("%d",&w[i]);
		modify(pos[i],w[i],1,n,1);
	}
	int q;
	scanf("%d",&q); 
	for (int i=0;i<q;i++)
	{
		int u,v;
		scanf("%s%d%d",str,&u,&v);
		if (str[0]=='C') modify(pos[u],v,1,n,1);
		if (str[0]=='Q' && str[1]=='S') cout<<Que(1,u,v)<<endl;
		if (str[0]=='Q' && str[1]=='M') cout<<Que(2,u,v)<<endl;
	}
}

int main()
{
	init();
	get_ans();
	return 0;
}
