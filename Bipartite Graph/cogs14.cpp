#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN=100+5; 
int n,m,T;
vector<int> E[MAXN];
int vis[MAXN],lk[MAXN];

int find(int u)
{
	for (int i=0;i<E[u].size();i++)
	{
		int to=E[u][i];
		if (vis[to]!=T)
		{
			vis[to]=T;
			if (!lk[to] || find(lk[to]))
			{
				lk[to]=u;
				return 1;
			}
		}
	}
	return 0;
}

void init()
{
	scanf("%d%d",&n,&m);
	m=n-m;n=n-m;
	int a,b;
	while (scanf("%d%d",&a,&b)!=EOF)
	{
		E[a].push_back(b);
	}
}

void solve()
{
	memset(vis,0,sizeof(vis));
	memset(lk,0,sizeof(lk));
	int ans=0;
	T=0;
	for (int i=1;i<=n;i++)
	{
		++T;
		if (find(i)) ++ans;else break;
	}
	printf("%d",ans);
}

int main()
{
	freopen("flyer.in","r",stdin);
	freopen("flyer.out","w",stdout); 
	init();
	solve();
	return 0;
}
