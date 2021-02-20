#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
const int MAXN=1000+50;
vector<int> E[MAXN];
stack<int> s;
int low[MAXN],dfn[MAXN],cnt=0,bcnt=0;
int instack[MAXN],b[MAXN];
int n,m;

void addedge(int u,int v)
{
	E[u].push_back(v);
}

void tarjan(int u)
{
	dfn[u]=low[u]=++cnt;
	instack[u]=1;
	s.push(u);
	for (int i=0;i<E[u].size();i++)
	{
		int to=E[u][i];
		if (!instack[to]) tarjan(to),low[u]=min(low[u],low[to]);
			else if (instack[to]==1) low[u]=min(low[u],dfn[to]);
	}
	
	if (dfn[u]==low[u])
	{
		int x;
		++bcnt;
		do
		{
			x=s.top();s.pop();
			instack[x]=2;
			b[x]=bcnt;
		}while (x!=u);
	}
}

void init()
{
	scanf("%d%d",&n,&m);
	for (int i=0;i<m;i++)
	{
		int a,b,c;char op[5];
		scanf("%d%d%d%s",&a,&b,&c,op);
		a++,b++;
		if (op[0]=='A')
		{
			if (c==0) addedge(a,b+n),addedge(b,a+n);
			if (c==1) addedge(a,b),addedge(b,a),addedge(a+n,a),addedge(b+n,b);
		}
		if (op[0]=='O')
		{
			if (c==0) addedge(a+n,b+n),addedge(b+n,a+n),addedge(a,a+n),addedge(b,b+n);
			if (c==1) addedge(a+n,b),addedge(b+n,a);
		}
		if (op[0]=='X')
		{
			if (c==0) addedge(a,b),addedge(b,a),addedge(a+n,b+n),addedge(b+n,a+n);
			if (c==1) addedge(a+n,b),addedge(b+n,a),addedge(a,b+n),addedge(b,a+n); 
		}
	}
}

void solve()
{
	memset(instack,0,sizeof(instack));
	for (int i=1;i<=2*n;i++) if (!instack[i]) tarjan(i); 
	int flag=1;
	for (int i=1;i<=n;i++)
		if (b[i]==b[i+n])
		{
			flag=0;
			break;
		}
	puts(flag?"YES":"NO");
}

int main()
{
	init();
	solve();
	return 0;
}
