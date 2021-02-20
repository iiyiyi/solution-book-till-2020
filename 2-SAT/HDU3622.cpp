#include<bits/stdc++.h>
#define eps 1e-8
using namespace std;
const int MAXN=250;
const int INF=0x7fffffff;
int n;
int x[MAXN],y[MAXN];
int dfn[MAXN],low[MAXN],col[MAXN],instack[MAXN],colcnt,cnt;
vector<int> E[MAXN];
stack<int> S; 

void addedge(int u,int v)
{
	E[u].push_back(v);
}

double dist(int x1,int y1,int x2,int y2)
{
	double ret=sqrt((double)(x1-x2)*(x1-x2)+(double)(y1-y2)*(y1-y2));
	//cout<<x1<<' '<<x2<<' '<<y1<<' '<<y2<<' '<<ret<<endl;
	return ret;
}

void tarjan(int u)
{
    dfn[u]=low[u]=++cnt;
    instack[u]=1;
    S.push(u);
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
    
    if (dfn[u]==low[u])
    {
        colcnt++;
        int x;
        do
        {
            x=S.top();
            col[x]=colcnt;
            instack[x]=2;
            S.pop();
        }while (x!=u);
    }
}

void build(double r)
{
	for (int i=0;i<MAXN;i++) vector<int>().swap(E[i]);
	for (int i=1;i<=n-1;i++)
		for (int j=i+1;j<=n;j++)
		{
			if (dist(x[i],y[i],x[j],y[j])<2*r) addedge(i,j+n),addedge(j,i+n);
			if (dist(x[i],y[i],x[j+n],y[j+n])<2*r) addedge(i,j),addedge(j+n,i+n);
			if (dist(x[i+n],y[i+n],x[j],y[j])<2*r) addedge(i+n,j+n),addedge(j,i);
			if (dist(x[i+n],y[i+n],x[j+n],y[j+n])<2*r) addedge(i+n,j),addedge(j+n,i); 
		}
}

void init()
{
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&x[i],&y[i]);
		scanf("%d%d",&x[i+n],&y[i+n]);
	}
}

void solve()
{
	double lb=0,ub=INF;
	while (ub-lb>eps)
	{
		double mid=(lb+ub)/2;
		build(mid);
		memset(instack,0,sizeof(instack));
		colcnt=cnt=0;
		for (int i=1;i<=2*n;i++) if (!instack[i]) tarjan(i);
		int flag=1;
		for (int i=1;i<=n;i++)
			if (col[i]==col[i+n])
			{
				flag=0;
				break;
			}
		if (flag) lb=mid;
			else ub=mid;
	}
	printf("%.2f\n",ub);
}

int main()
{
	while (scanf("%d",&n)!=EOF)
	{
		init();
		solve();
	}
	return 0;
}
