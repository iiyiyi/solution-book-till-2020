#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack>
#include<cmath>
using namespace std;
const int MAXN=1000000+50;
typedef long long ll;
struct node
{
	int key,dis,size;
	int lson,rson,father;
	int L,R;

}ltree[MAXN];
int n,z[MAXN];
stack<int> S;

void pushup(int x)
{
	int l=ltree[x].lson,r=ltree[x].rson;
	ltree[x].size=1+ltree[l].size+ltree[r].size;
} 

void build(int rt,int x)
{
	ltree[rt].key=x;
	ltree[rt].dis=(rt==0)?-1:0;
	ltree[rt].size=(rt==0)?0:1;
	//不要忘了当Rt=0的时候size为0 
	ltree[rt].lson=ltree[rt].rson=0;
	ltree[rt].father=ltree[rt].L=ltree[rt].R=rt;
}

int merge(int x,int y)
{
	if (x==0 || y==0) return (x+y);
	if (ltree[x].key<ltree[y].key) swap(x,y);
	ltree[x].L=min(ltree[x].L,ltree[y].L);
	ltree[x].R=max(ltree[x].R,ltree[y].R);
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
	int l=ltree[rt].lson,r=ltree[rt].rson;
	ltree[rt].dis=0;
	ltree[rt].size=1;
	ltree[rt].lson=ltree[rt].rson=0;
	int ret=merge(l,r);
	ltree[ret].L=ltree[rt].L;
	ltree[ret].R=ltree[rt].R;
	return ret;
}

void init()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&z[i]),z[i]-=i;
	for (int i=1;i<=n;i++) build(i,z[i]);
	build(0,0);
} 

void solve()
{
	int before=z[1];
	S.push(1);
	for (int i=2;i<=n;i++)
	{
		int now=i;
		while (!S.empty())
		{
			int tail=S.top();
			if (ltree[now].key<ltree[tail].key)
			{
				S.pop();
				int tmp=merge(tail,now);
				now=tmp;
				while (ltree[now].size*2>(ltree[now].R-ltree[now].L+2)) now=del(now);
				//不要忘记了这里是ltree[now].R-ltree[now].L+2，一开始写成了+1 
				if (S.empty())
				{
					S.push(now);
					break;
				}
			}
			else
			{
				S.push(now);
				break;
			}
		}
	}
	ll ans=0;
	while (!S.empty())
	{
		int now=S.top();S.pop();
		for (int i=ltree[now].L;i<=ltree[now].R;i++) ans+=abs(z[i]-ltree[now].key);
	}
	printf("%lld",ans);
}

int main()
{
	init();
	solve();
	return 0;
}
