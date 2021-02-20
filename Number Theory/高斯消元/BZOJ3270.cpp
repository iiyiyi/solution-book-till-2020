#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
const int MAXN=20+5;
double f[MAXN*MAXN][MAXN*MAXN],p[MAXN];
int id[MAXN][MAXN];
vector<int> E[MAXN];
double a[MAXN*MAXN][MAXN*MAXN]; 
int n,m,aa,bb;

void init()
{
	scanf("%d%d%d%d",&n,&m,&aa,&bb);
	int cnt=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++) id[i][j]=++cnt;
	a[id[aa][bb]][n*n+1]=-1;
	for (int i=1;i<=n;i++) E[i].push_back(i);//不要忘记把自己向自己是可以走的
	for (int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		E[u].push_back(v);
		E[v].push_back(u); 
	}
	for (int i=1;i<=n;i++) scanf("%lf",&p[i]);
}

void buildequ()
{
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		{
			a[id[i][j]][id[i][j]]--;//位于方程右边系数为1，移到左边系数变成-1 
			for (int x=0;x<E[i].size();x++)
				for (int y=0;y<E[j].size();y++)
				{
					int tx=E[i][x],ty=E[j][y];
					int fr=id[i][j],to=id[tx][ty];
					if (tx!=ty)
					{
						if (tx==i && ty==j) a[fr][to]+=p[tx]*p[ty];//停留在原地不动
						else if (tx==i) a[fr][to]+=p[tx]*(1-p[ty])/(E[ty].size()-1);
						else if (ty==j) a[fr][to]+=p[ty]*(1-p[tx])/(E[tx].size()-1);
						else a[fr][to]+=(1-p[tx])*(1-p[ty])/(E[ty].size()-1)/(E[tx].size()-1);
					} 
				} 
		}
}

void guass()
{
	for (int i=1;i<=n*n;i++)
	{
		int t=i;
		for (int j=i+1;j<=n*n;j++) if (fabs(a[j][i])>fabs(a[t][i])) t=j;
		if (t!=i) for (int j=i;j<=n*n+1;j++) swap(a[i][j],a[t][j]);//不要忘记要到n*n+1 
		for (int j=i+1;j<=n*n;j++)
		{
			double x=a[j][i]/a[i][i];
			for (int k=i;k<=n*n+1;k++) a[j][k]-=a[i][k]*x;
		}
	}
	for (int i=n*n;i>=1;i--)
	{
		for (int j=i+1;j<=n*n;j++) a[i][n*n+1]-=a[i][j]*a[j][n*n+1];
		a[i][n*n+1]/=a[i][i]; 
	}
}

void printans()
{
	for (int i=1;i<=n;i++) printf("%.6lf ",a[id[i][i]][n*n+1]);
}

int main()
{
	init();
	buildequ();
	guass();
	printans();
	return 0;
}
