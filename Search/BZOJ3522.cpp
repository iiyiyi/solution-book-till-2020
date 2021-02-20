#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=5000+50;
int n;
int p1[MAXN],p2[MAXN],tmp[MAXN];
vector<int> E[MAXN];

void dfs(int fr,int u,int dep)
{
	tmp[dep]++;
	for (int i=0;i<E[u].size();i++)
	{
		int v=E[u][i];
		if (v==fr) continue;
		dfs(u,v,dep+1);
	}
}

void solve()
{
	ll ans=0;
	for (int i=1;i<=n;i++)
	{
		memset(p1,0,sizeof(p2));
		memset(p2,0,sizeof(p1));
		for (int j=0;j<E[i].size();j++)
		{
			memset(tmp,0,sizeof(tmp));
			int to=E[i][j];
			dfs(i,to,1);
			for (int k=1;k<=n;k++)
			{
				ans+=(ll)p2[k]*tmp[k];
				p2[k]+=p1[k]*tmp[k];
				p1[k]+=tmp[k];
			}
		}
	}
	printf("%lld\n",ans);
}

void init()
{
	scanf("%d",&n);
	for (int i=0;i<n-1;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		E[x].push_back(y);
		E[y].push_back(x);
	}
}

int main()
{
	init();
	solve();
	return 0;	
} 
