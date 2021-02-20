#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#define EPS (1e-8) 
using namespace std;
const int MAXN=500000+50;
struct node
{
	int to;
	double p;
};
vector<node> E[MAXN];
double q[MAXN],f1[MAXN],f2[MAXN],ans;

void addedge(int a,int b,double p)
{
	E[a].push_back((node){b,p});
}

bool dcmp(double a)  
{  
    return fabs(a-0)<EPS;  
}  

void dfs1(int u,int fa)
{
	for (int i=0;i<E[u].size();i++)
	{
		int to=E[u][i].to;
		if (to!=fa) 
		{
			dfs1(to,u);
			f1[u]=f1[u]+f1[to]*E[u][i].p-f1[u]*f1[to]*E[u][i].p;
		}
	}
}

void dfs2(int u,int fa)
{
	ans+=f2[u];
	for (int i=0;i<E[u].size();i++)
	{
		int to=E[u][i].to; 
		if (to!=fa)
		{
			if (dcmp(1.0-E[u][i].p*f1[to])) f2[to]=1.0;
			else
			{
				double tmp=(f2[u]-E[u][i].p*f1[to])/(1.0-E[u][i].p*f1[to]);
				f2[to]=f1[to]+tmp*E[u][i].p-f1[to]*tmp*E[u][i].p;
			}
			dfs2(to,u);
		}
	}
}

void init()
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n-1;i++)
	{
		int a,b;
		double p;
		scanf("%d%d%lf",&a,&b,&p);
		addedge(a,b,p/100); 
		addedge(b,a,p/100);
	}
	for (int i=1;i<=n;i++)
	{
		scanf("%lf",&q[i]);
		f1[i]=q[i]/100;
	}
}

void solve()
{
	dfs1(1,0);
	f2[1]=f1[1];
	dfs2(1,0);
	printf("%.6lf",ans);
}

int main()
{
	init();
	solve();
	return 0;
}
