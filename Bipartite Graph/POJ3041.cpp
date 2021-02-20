#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN=505;
vector<int> E[MAXN];
int lk[MAXN],vis[MAXN],n,k; 

int find(int u)
{
	for (int i=0;i<E[u].size();i++)
	{
		int v=E[u][i];
		if (!vis[v])
		{
			vis[v]=1;
			if (!lk[v]||find(lk[v]))
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
	scanf("%d%d",&n,&k);
	for (int i=1;i<=k;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		E[x].push_back(y);
	}
}

void solve()
{
	int ans=0;
	memset(lk,0,sizeof(lk));
	for (int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof(vis));
		if (find(i)) ans++;
	}
	printf("%d",ans);
} 

int main()
{
	init();
	solve();
	return 0;
}
