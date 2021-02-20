#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAXN=220+5;
const int MAXR=132+5;
double p[MAXN];
int d[MAXN];
double f[MAXN][MAXR];
int n,r;

void init()
{
	scanf("%d%d",&n,&r);
	for (int i=1;i<=n;i++) scanf("%lf%d",&p[i],&d[i]);
}

void dp()
{
	double ans=0;
	memset(f,0,sizeof(f));
	f[0][r]=1;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=r;j++)
		{
			f[i][j]=f[i-1][j]*pow(1-p[i-1],j)+f[i-1][j+1]*(1-pow(1-p[i-1],j+1));
			ans+=f[i][j]*(1-pow(1-p[i],j))*d[i];
		}
	printf("%.10lf\n",ans);
}

int main()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		init();
		dp();
	}
	return 0;
}
