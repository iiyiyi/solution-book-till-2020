#include<bits/stdc++.h>
using namespace std;
const int MAXN=100000+50;
int n,m,in;
vector<int> E[MAXN];
priority_queue<int> que;
int ans[MAXN],inn[MAXN];

void init()
{
	scanf("%d%d",&n,&m);
	memset(inn,0,sizeof(inn));
	for (int i=1;i<=n;i++) vector<int>().swap(E[i]);
	for (int i=0;i<m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		inn[u]++;
		E[v].push_back(u);
	}
}

void solve()
{
	while (!que.empty()) que.pop();
	ans[0]=0;
	for (int i=1;i<=n;i++) if (!inn[i]) que.push(i);
	while (!que.empty())
	{
		int u=que.top();que.pop();
		ans[++ans[0]]=u;
		for (int i=0;i<E[u].size();i++)
		{
			int v=E[u][i];
			inn[v]--;
			if (!inn[v]) que.push(v);
		}
	}
	if (ans[0]<n) puts("Impossible!");
		else 
		{
			for (int i=ans[0];i>=1;i--) printf("%d ",ans[i]);
			printf("\n");
		}
}

int main()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		init();
		solve();
	}
	return 0;
}
