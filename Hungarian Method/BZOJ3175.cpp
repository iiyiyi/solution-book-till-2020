#include<bits/stdc++.h>
using namespace std;
const int MAXN=205;
int n,maps[MAXN][MAXN];
int lk[MAXN*MAXN],vis[MAXN*MAXN];
vector<int> E[MAXN*MAXN];

int check(int x,int y)
{
	if (x>=1 && x<=n && y>=1 && y<=n && maps[x][y]) return 1;else return 0;
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
			if (!lk[v]|| find(lk[v]))
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
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		char str[MAXN];
		scanf("%s",str);
		for (int j=0;j<n;j++)
			if (str[j]=='0') maps[i][j+1]=1;else maps[i][j+1]=0;
	}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if (maps[i][j]==1)
			{
				if (check(i-1,j-2)) addedge(id(i,j),id(i-1,j-2));
				if (check(i-2,j-1)) addedge(id(i,j),id(i-2,j-1));
				if (check(i+1,j-2)) addedge(id(i,j),id(i+1,j-2));
				if (check(i+2,j-1)) addedge(id(i,j),id(i+2,j-1));
				if (check(i-1,j+2)) addedge(id(i,j),id(i-1,j+2));
				if (check(i-2,j+1)) addedge(id(i,j),id(i-2,j+1));
				if (check(i+1,j+2)) addedge(id(i,j),id(i+1,j+2));
				if (check(i+2,j+1)) addedge(id(i,j),id(i+2,j+1));
			}
}

void solve()
{
	memset(lk,0,sizeof(lk));
	int sum=0,ans=0;
	for (int i=1;i<=n;i++)
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
	printf("%d",sum-ans/2);//不要忘记了除以2 
}

int main()
{
	init();
	solve();
}
