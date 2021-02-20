#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define L Ltree[Ltree[x].lson]
#define R Ltree[Ltree[x].rson]
using namespace std;
typedef long long ll;
const int MAXN=300000+50;
struct node
{
	ll key;
	int dis,pos,cnt;
	ll lazyadd,lazymul;int lazycnt;//懒惰标记
	int lson,rson; 
};
int n,m;
ll h[MAXN],v[MAXN];//防御力，战斗变化量，
int city[MAXN],knight[MAXN],f[MAXN],a[MAXN],out[MAXN],rt[MAXN];
//每个城市牺牲的骑士数，每个骑士攻破的城市数量,管辖地，战斗变化参数，每个节点的出度（拓扑排序使用），到达每个节点位置时的堆顶元素 
node Ltree[MAXN];//左偏树 
queue<int> que;//树由下至上拓扑排序的队列 

void update(int root,int flag,ll delta)
{
	Ltree[root].lazycnt++;
	Ltree[root].cnt++;
	if (flag)
	{
		Ltree[root].lazyadd*=delta;
		Ltree[root].lazymul*=delta;
		Ltree[root].key*=delta;
	}
	else
	{
		Ltree[root].lazyadd+=delta;
		Ltree[root].key+=delta;
	}
}

void pushdown(int x)
{
	if (Ltree[x].lazycnt)
	{
		L.cnt+=Ltree[x].lazycnt;
		R.cnt+=Ltree[x].lazycnt;
		L.lazycnt+=Ltree[x].lazycnt;
		R.lazycnt+=Ltree[x].lazycnt;
		Ltree[x].lazycnt=0;
	}
	if (Ltree[x].lazymul!=1)
	{
		L.key*=Ltree[x].lazymul;
		R.key*=Ltree[x].lazymul;
		L.lazyadd*=Ltree[x].lazymul;
		R.lazyadd*=Ltree[x].lazymul;
		L.lazymul*=Ltree[x].lazymul;
		R.lazymul*=Ltree[x].lazymul;
		Ltree[x].lazymul=1;
	} 
	if (Ltree[x].lazyadd)
	{
		L.key+=Ltree[x].lazyadd;
		R.key+=Ltree[x].lazyadd;
		L.lazyadd+=Ltree[x].lazyadd;
		R.lazyadd+=Ltree[x].lazyadd;
		Ltree[x].lazyadd=0;
	}
}

int merge(int x,int y)
{
	if (!x||!y) 
	{
		return(x+y);
	}
	if (Ltree[x].key>Ltree[y].key) swap(x,y);
	pushdown(x);
	Ltree[x].rson=merge(Ltree[x].rson,y);
	int &l=Ltree[x].lson,&r=Ltree[x].rson;
	if (Ltree[l].dis<Ltree[r].dis) swap(l,r);
	if (r==0) Ltree[x].dis=0;
		else Ltree[x].dis=Ltree[r].dis+1;
	return x;
}

void init()
{
	scanf("%d%d",&n,&m);
	memset(rt,0,sizeof(rt));
	for (int i=1;i<=n;i++) scanf("%lld",&h[i]);
	for (int i=2;i<=n;i++) 
	{
		scanf("%d%d%lld",&f[i],&a[i],&v[i]);
		out[f[i]]++;
	}
	Ltree[0].dis=-1;
	for (int i=1;i<=m;i++)
	{
		ll s;int c;
		scanf("%lld%d",&s,&c);
		Ltree[i]=(node){s,0,i,0,0,1,0};
		rt[c]=merge(rt[c],i);
	}
}

void Topology()
{
	queue<int> que;
	for (int i=1;i<=n;i++) if (!out[i]) que.push(i);
	while (!que.empty())
	{
		int u=que.front();que.pop();
		int& root=rt[u];
		int father=f[u];
		while (root && (h[u]>Ltree[root].key))//如果堆顶元素小于城市的防御力，即该骑士会牺牲，则不断弹出 
		{
			knight[Ltree[root].pos]=Ltree[root].cnt;
			city[u]++;
			pushdown(root);
			root=merge(Ltree[root].lson,Ltree[root].rson);
		}
		update(root,a[u],v[u]);
		rt[father]=merge(rt[father],root);
		out[father]--;
		if (!out[father]) que.push(father);
	}
	
	while (rt[1])//处理所有能够抵达根节点的所有骑士 
	{
		knight[rt[1]]=Ltree[rt[1]].cnt;
		pushdown(rt[1]);
		rt[1]=merge(Ltree[rt[1]].lson,Ltree[rt[1]].rson);
	} 
}

void printans()
{
	for (int i=1;i<=n;i++) printf("%d\n",city[i]);
	for (int j=1;j<=m;j++) printf("%d\n",knight[j]);
}

int main()
{
	init();
	Topology();
	printans();
	return 0;
}
