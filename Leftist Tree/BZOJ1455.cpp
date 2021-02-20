#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1000000+500;
struct node
{
	int key,dis,del;
	int lson,rson,father;
}ltree[MAXN];
int n,m; 

int find(int a)
{
	while (ltree[a].father!=a) a=ltree[a].father;
	return a;
}

void build(int rt,int val)
{
	ltree[rt].key=val;
	ltree[rt].dis=(rt==0)?-1:0;
	ltree[rt].del=0;
	ltree[rt].lson=ltree[rt].rson=0;
	ltree[rt].father=rt;
}

int merge(int x,int y)
{
	if (x==0||y==0) return (x|y);
	if (ltree[x].key>ltree[y].key) swap(x,y);
	ltree[x].rson=merge(ltree[x].rson,y);
	int &l=ltree[x].lson,&r=ltree[x].rson;
	ltree[l].father=ltree[r].father=x;
	if (ltree[l].dis<ltree[r].dis) swap(l,r);
	if (r==0) ltree[x].dis=0;
		else ltree[x].dis=ltree[r].dis+1;
	return x;
}

void Del(int rt)
{
	int l=ltree[rt].lson,r=ltree[rt].rson;
	ltree[l].father=l;
	ltree[r].father=r;
	ltree[rt].dis=ltree[rt].lson=ltree[rt].rson=0;
	ltree[rt].del=1;
	merge(l,r);
}

void init()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		int score;
		scanf("%d",&score);
		build(i,score);
	}
	build(0,0);
}

void solve()
{
	scanf("%d",&m);
	for (int i=0;i<m;i++)
	{
		char op[1];
		scanf("%s",op);
		if (op[0]=='M')
		{
			int a,b;
			scanf("%d%d",&a,&b);
			if (!ltree[a].del&&!ltree[b].del)
			{
				int fa=find(a),fb=find(b);
				if (fa!=fb) merge(fa,fb);//不要忘记要判断两者不在同一个集合中 
			}
		}
		if (op[0]=='K')
		{
			int a;
			scanf("%d",&a);
			if (ltree[a].del) puts("0");
				else
				{
					int fa=find(a);
					printf("%d\n",ltree[fa].key);
					Del(fa);
				}
		}
	}
}

int main()
{
	init();
	solve();
	return 0;
}
