#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm> 
using namespace std;
const int INF=0x7fffffff;
const int MAXN=100000+50;
struct node
{
	int key,dis;
	int lson,rson;
	int father; 
};
node ltree[MAXN];
int n;

void build(int x,int k)
{
	ltree[x].key=k;
	ltree[x].father=x;
	ltree[x].lson=ltree[x].rson=0;
	ltree[x].dis=(x==0)?-1:0;
}

int find(int x)
{
	if (ltree[x].father==x) return x;
		else return(find(ltree[x].father));
}

int merge(int x,int y)
{
	if (x==0) return y;
	if (y==0) return x;
	if (ltree[x].key<ltree[y].key) swap(x,y);
	ltree[x].rson=merge(ltree[x].rson,y);
	int &l=ltree[x].lson,&r=ltree[x].rson;
	ltree[l].father=ltree[r].father=x;
	if (ltree[l].dis<ltree[r].dis) swap(l,r);
	if (r==0) ltree[x].dis=0;
		else ltree[x].dis=ltree[r].dis+1;
	return x;
}

int del(int rt)
{
	int l=ltree[rt].lson;
	int r=ltree[rt].rson;
	ltree[l].father=l;
	ltree[r].father=r;
	ltree[rt].dis=ltree[rt].lson=ltree[rt].rson=0;
	return merge(l,r);
}

int solve(int x,int y)
{
	ltree[x].key>>=1;
	ltree[y].key>>=1;
	int left,right;
	left=del(x);
	right=del(y);
	left=merge(left,x);
	right=merge(right,y);
	left=merge(left,right);
	return ltree[left].key;
}

void init()
{
	for (int i=1;i<=n;i++)
	{
		int strong;
		scanf("%d",&strong);
		build(i,strong);
	}
	build(0,0);
}

void get_ans()
{
	int q;
	scanf("%d",&q);
	for (int i=0;i<q;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		int fx=find(x),fy=find(y);
		if (fx==fy) cout<<-1<<endl;
			else cout<<solve(fx,fy)<<endl;
	}
}

int main()
{
	while (scanf("%d",&n)!=EOF)
	{
		init();
		get_ans();
	} 
	return 0;	
} 
