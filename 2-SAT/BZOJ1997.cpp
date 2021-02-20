#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
const int MAXN=20000+50;
int n,m;
int u[MAXN],v[MAXN],pos[MAXN];
vector<int> E[MAXN];
int dfn[MAXN],low[MAXN],instack[MAXN],col[MAXN],cnt,colcnt;
stack<int> S;

int cross(int i,int j)
{
	int x1=pos[u[i]],y1=pos[v[i]],x2=pos[u[j]],y2=pos[v[j]]; 
	if ((x1<x2 && x2<y1 && y1<y2) || (x2<x1 && x1<y2 && y2<y1)) return 1;else return 0;
}

void addedge(int u,int v)
{
	E[u].push_back(v);
	E[v].push_back(u);
}


void tarjan(int u)
{
    dfn[u]=low[u]=++cnt;
    S.push(u);
    instack[u]=1;
     
    for (int i=0;i<E[u].size();i++)
    {
        int son=E[u][i];
        if (!instack[son])
        {
            tarjan(son);
            low[u]=min(low[son],low[u]);
        }
        else
        if (instack[son]==1)
            low[u]=min(dfn[son],low[u]);
    }
     
    if (dfn[u]==low[u])
    {
        colcnt++;
        int x;
        do
        {
             x=S.top();
             S.pop();
             col[x]=colcnt;
             instack[x]=2;
        }while (x!=u);
    }
} 


void init()
{
	scanf("%d%d",&n,&m);
	cnt=0,colcnt=0;
	for (int i=0;i<MAXN;i++) vector<int>().swap(E[i]);//注意不要忘记清空 
	memset(instack,0,sizeof(instack));
	for (int i=1;i<=m;i++)
		scanf("%d%d",&u[i],&v[i]);
	for (int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		pos[x]=i;
	}
}

void build()
{
	for (int i=1;i<=m;i++)
		if (pos[u[i]]>pos[v[i]]) swap(u[i],v[i]);
	for (int i=1;i<=m;i++)
		for (int j=i+1;j<=m;j++)
			if (cross(i,j))
			{
				addedge(i,j+m);
				addedge(i+m,j);
			}
}

void solve()
{
	for (int i=1;i<=2*m;i++) if (!instack[i]) tarjan(i);
	int f=1;
	for (int i=1;i<=m;i++)
		if (col[i]==col[i+m])
		{
			f=0;
			break;
		}
	if (f) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
}

int main()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		init();
		if (m<=3*n-6)//平面图定理 
		{
			build();
			solve();
		}
		else 
			cout<<"NO"<<endl;
	}
	return 0;	
} 
