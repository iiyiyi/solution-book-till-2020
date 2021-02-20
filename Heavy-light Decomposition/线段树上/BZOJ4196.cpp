#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
using namespace std;
const int MAXN=100000+50;
const int rt=0;
vector<int> E[MAXN];
int n;
int fa[MAXN],dep[MAXN],hson[MAXN],size[MAXN];
int cnt=0,top[MAXN],pos[MAXN];
int sum[MAXN<<3],add[MAXN<<3],change[MAXN<<3];

//树链剖分部分 
void addedge(int u,int v)
{
	E[u].push_back(v);
}

void dfs1(int u,int father,int depth)
{
	fa[u]=father;
	dep[u]=depth;
	size[u]=1;
	hson[u]=-1;
	for (int i=0;i<E[u].size();i++)
	{
		int to=E[u][i];
		dfs1(to,u,depth+1);
		size[u]+=size[to];
		if (hson[u]==-1 || size[to]>size[hson[u]]) hson[u]=to;
	}
}

void dfs2(int u,int t)
{
	pos[u]=++cnt;
	top[u]=t;
	if (hson[u]!=-1) dfs2(hson[u],t);
	for (int i=0;i<E[u].size();i++)
	{
		int to=E[u][i];
		if (to!=hson[u]) dfs2(to,to);
	}
}

//线段树部分
void build()
{
	memset(sum,0,sizeof(sum));
	memset(add,0,sizeof(add));
} 

void pushup(int rt)
{
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}

void pushdown(int rt,int m)
{
	if (change[rt])
	{
		change[rt<<1]=change[rt<<1|1]=1;
		add[rt<<1]=add[rt];
		add[rt<<1|1]=add[rt];
		sum[rt<<1]=add[rt]*(m-(m>>1));
		sum[rt<<1|1]=add[rt]*(m>>1);
		add[rt]=change[rt]=0;
	}
} 

int query_sum(int L,int R,int l,int r,int rt)
{
	if (L<=l && r<=R) return sum[rt];
	pushdown(rt,r-l+1);
	int m=(l+r)>>1;
	int ret=0;
	if (m>=L) ret+=query_sum(L,R,lson);
	if (m<R) ret+=query_sum(L,R,rson);
	pushup(rt); 
	return ret;
}

void modify(int L,int R,int l,int r,int rt,int x)
{
	if (L<=l && r<=R)
	{
		change[rt]=1;
		add[rt]=x;
		sum[rt]=(r-l+1)*x;
		return;
	}
	pushdown(rt,r-l+1);
	int m=(l+r)>>1;
	if (m>=L) modify(L,R,lson,x);
	if (m<R) modify(L,R,rson,x);
	pushup(rt);
}

//树链剖分查询部分 
int install(int x,int y)
{
	int ret=dep[x],f1=top[x],f2=top[y];
	while (f1!=f2)
	{
		ret-=query_sum(pos[f1],pos[x],1,n,1);
		modify(pos[f1],pos[x],1,n,1,1);
		x=fa[f1];
		f1=top[x];
	}
	ret-=query_sum(pos[y],pos[x],1,n,1);
	modify(pos[y],pos[x],1,n,1,1);
	return (ret);
}

int uninstall(int x)
{
	int ret=query_sum(pos[x],pos[x]+size[x]-1,1,n,1);
	modify(pos[x],pos[x]+size[x]-1,1,n,1,0);
	return ret;
}


//读入部分 
void init()
{
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		int tmp;
		scanf("%d",&tmp);
		addedge(tmp,i);
	}
	dfs1(0,0,1);
	dfs2(0,0);
}

void get_ans()
{
	memset(sum,0,sizeof(sum));
	memset(change,0,sizeof(change));
	memset(add,0,sizeof(add));
	int q;
	scanf("%d",&q);
	for (int i=0;i<q;i++)
	{
		char str[25];
		int x;
		scanf("%s%d",str,&x);
		if (str[0]=='i') printf("%d\n",install(x,rt));
			else if (str[0]=='u') printf("%d\n",uninstall(x));
	}
}

int main()
{
	init();
	build(); 
	get_ans();
	return 0;
}
