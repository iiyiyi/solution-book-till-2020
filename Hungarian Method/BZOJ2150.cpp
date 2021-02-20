#include<bits/stdc++.h>
using namespace std;
const int MAXN=55;
int m,n,r,c,maps[MAXN][MAXN];
int lk[MAXN*MAXN],vis[MAXN*MAXN];
vector<int> E[MAXN*MAXN];

int check(int x,int y)
{
	if (x>=1 && x<=m && y>=1 && y<=n && maps[x][y]) return 1;else return 0;
}

int id(int x,int y){return ((x-1)*n+y);}

void addedge(int u,int v)
{
	E[u].push_back(v);
}

int find(int u)
{
	for (int i=E[u].size()-1;i>=0;i--)
	{
		int v=E[u][i];
		if (!vis[v])
		{
			vis[v]=1;
			if (!lk[v]|| find(lk[v]))//呜哇这里写成了find(v)半天没有发现，果然是老阿姨了啊 
			{
				lk[v]=u;
				return 1;
			}
		}
	}
	return 0;
}

void init()
{
	scanf("%d%d%d%d",&m,&n,&r,&c);
	for (int i=1;i<=m;i++)
	{
		char str[MAXN];
		scanf("%s",str);
		for (int j=0;j<n;j++)
			if (str[j]=='.') maps[i][j+1]=1;else maps[i][j+1]=0;
	}
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++)
			if (maps[i][j])
			{
				if (check(i+r,j+c)) addedge(id(i,j),id(i+r,j+c));
				if (check(i+r,j-c)) addedge(id(i,j),id(i+r,j-c));
				if (check(i+c,j+r))	addedge(id(i,j),id(i+c,j+r));
				if (check(i+c,j-r)) addedge(id(i,j),id(i+c,j-r));
			}
}

void solve()
{
	memset(lk,0,sizeof(lk));
	int sum=0,ans=0;
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++)
		{
			if (maps[i][j]==1)
			{
				int x=id(i,j);
				memset(vis,0,sizeof(vis));
				sum++;
				if (find(x)) ans++;
			}
		}
	printf("%d",sum-ans);
}

int main()
{
	init();
	solve();
}
