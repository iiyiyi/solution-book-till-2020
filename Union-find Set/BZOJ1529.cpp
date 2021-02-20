#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAXN=50000+50;
int rank[MAXN],u[MAXN];
int n,k,ans;

int find(int x)
{
	if (x!=u[x])
	{
		int tmp=u[x];
		u[x]=find(u[x]);
		rank[x]=(rank[x]+rank[tmp])%3;
	} 
	return u[x];
} 

void init()
{
	ans=0;
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;i++) rank[i]=0,u[i]=i;
}

void solve()
{
	for (int i=1;i<=k;i++)
	{
		int d,x,y;
		scanf("%d%d%d",&d,&x,&y);
		if (x>n||y>n||((d==2) && (x==y))) 
		{
			ans++;
			continue;
		}
		int fx=find(x),fy=find(y);
		int v=(d==1)?0:1;
		if (fx!=fy)
		{
			u[fx]=fy;
			rank[fx]=(rank[y]+v-rank[x]+3)%3;
		}
		else
			if (rank[x]!=(rank[y]+v)%3) ans++;
	}
	printf("%d",ans);
}

int main()
{
	init();
	solve();
	return 0;
} 
