#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<vector>
#include<stack>
using namespace std;
map<string,int> Name;
const int MAXN=4000+50;
int n,m;
int cnt,col,dfn[MAXN*2],low[MAXN*2],instack[MAXN*2],tar[MAXN*2];
vector<int> E[MAXN*2];
stack<int> S;

void addedge(int u,int v){E[u].push_back(v);}

void tarjan(int u)
{
	low[u]=dfn[u]=++cnt;
	S.push(u);
	instack[u]=1;//不要忘记了这两句
	for (int i=0;i<E[u].size();i++)
	{
		int v=E[u][i];
		if (!instack[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if (instack[v]==1) low[u]=min(low[u],dfn[v]);
	}
	
	if (low[u]==dfn[u])
	{
		++col;
		while (S.top()!=u)
		{
			tar[S.top()]=col,instack[S.top()]=2;
			S.pop();
		}
		tar[u]=col,instack[u]=2;
		S.pop();
	}
}

void init()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		char wife[15],husband[15];
		scanf("%s%s",wife,husband);
		Name[wife]=i;
		Name[husband]=i+n;
		addedge(i,i+n);
	}
	scanf("%d",&m);
	for (int i=1;i<=m;i++)
	{
		char Exgf[15],Exbf[15];
		scanf("%s%s",Exgf,Exbf);
		int exgf=Name[Exgf],exbf=Name[Exbf];
		addedge(exbf,exgf);
	}
}

void solve()
{
	cnt=col=0;
	while (!S.empty()) S.pop();
	memset(instack,0,sizeof(instack));
	for (int j=1;j<=2*n;j++) if (!instack[j]) tarjan(j);
	for (int i=1;i<=n;i++)
		if (tar[i]==tar[i+n]) puts("Unsafe");
			else puts("Safe");
}

int main()
{
	init();
	solve();
	return 0;
}
