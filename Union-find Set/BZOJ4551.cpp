#include<bits/stdc++.h>
using namespace std;
const int MAXN=100000+50;
vector<int> E[MAXN];
int mark[MAXN];
int query[MAXN],ans[MAXN]; 
int u[MAXN],fa[MAXN],n,q;
char op[MAXN];

void dfs(int x,int anc,int father)
{
	fa[x]=father;
	if (mark[x]>0) u[x]=x;
		else u[x]=anc;
	for (int i=0;i<E[x].size();i++)
	{
		int to=E[x][i];
		if (to==fa[x]) continue;
		dfs(to,u[x],x);
	}
}

int union_set(int x)
{
	int r=x;
	while (u[r]!=r) r=u[r];
	int now=x;
	while (u[now]!=r)
	{
		int tmp=u[now];
		u[now]=r;
		now=tmp;
	}
	return u[x];
}

void init()
{
	scanf("%d%d",&n,&q);
	for (int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		E[u].push_back(v);
		E[v].push_back(u);
	}
	mark[1]=1;
	for (int i=1;i<=q;i++)
	{
		char tmp[1];
		scanf("%s %d",tmp,&query[i]);
		if (tmp[0]=='C') mark[query[i]]++;
		op[i]=tmp[0];
	}
	dfs(1,1,0);
	for (int i=1;i<=n;i++) cout<<u[i]<<endl;
}

void solve()
{
	memset(ans,0,sizeof(ans));
	for (int i=q;i>=1;i--)
	{
		int now=query[i];
		if (op[i]=='C')
		{
			mark[now]--;
			if (!mark[now]) now=union_set(fa[now]);
		}
		else ans[++ans[0]]=union_set(now);
	}	
	for (int i=ans[0];i>=1;i--) printf("%d\n",ans[i]);
} 

int main()
{
	init();
	solve();
	return 0;
}
