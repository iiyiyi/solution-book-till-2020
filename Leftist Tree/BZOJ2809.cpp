#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int MAXN=100000+500;
struct node
{
	ll cost,key,sum;
	int size,dis,lson,rson;
}ltree[MAXN];
int n,master;
ll m,ans=-1;
vector<int> E[MAXN];

void build(int x,int fa,ll salary,ll leading)
{
	ltree[x].cost=ltree[x].sum=salary;
	ltree[x].key=leading;
	ltree[x].size=(x==0)?0:1;
	ltree[x].lson=ltree[x].rson=0;
	ltree[x].dis=(x==0)?-1:0;
}

void pushup(int x)
{
	int l=ltree[x].lson,r=ltree[x].rson;
	ltree[x].sum=ltree[x].cost+ltree[l].sum+ltree[r].sum;
	ltree[x].size=1+ltree[l].size+ltree[r].size;
} 

int merge(int x,int y)
{
	if (x==0) return y;
	if (y==0) return x;
	if (ltree[x].cost<ltree[y].cost) swap(x,y);
	/*这里比较大小是cost之间，而不是sum之间……检查了一个下午才发现！！！！！！*/ 
	ltree[x].rson=merge(ltree[x].rson,y);
	int &l=ltree[x].lson,&r=ltree[x].rson;
	if (ltree[l].dis<ltree[r].dis) swap(l,r);
	if (r==0) ltree[x].dis=0;
		else ltree[x].dis=ltree[r].dis+1;
	pushup(x);
	return x;
}

int del(int rt)
{
	int l=ltree[rt].lson;
	int r=ltree[rt].rson;
	ltree[rt].dis=ltree[rt].lson=ltree[rt].rson=0;
	return merge(l,r);
}


void init()
{
	scanf("%d",&n);
	scanf("%lld",&m);
	for (int i=1;i<=n;i++)
	{
		int b;
		long long c,l;
		scanf("%d%lld%lld",&b,&c,&l);
		if (b==0) master=i;
		E[b].push_back(i);
		build(i,b,c,l);
	}
	build(0,0,0,0);
}

int dfs(int u)
{
	int rt=u;
	for (int i=0;i<E[u].size();i++)
	{
		int to=E[u][i];
		rt=merge(rt,dfs(to));
	}
	while (ltree[rt].sum>m)
	{
		ltree[rt].sum-=ltree[rt].cost;
		ltree[rt].size--;
		rt=del(rt);
	}
	ans=max(ans,(ll)ltree[rt].size*(ll)ltree[u].key);
	return rt;
}

void print_ans()
{
	printf("%lld",ans);
} 

int main()
{
	//freopen("dispatching.in","r",stdin);
	//freopen("dispatching.out","w",stdout);
	init();
	dfs(master);
	print_ans(); 
	return 0;
}
