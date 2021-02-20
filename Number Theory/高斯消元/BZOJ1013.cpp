#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=15;
int n;
double pos[MAXN][MAXN],l[MAXN][MAXN];

void Gauss()
{
	for (int i=1;i<=n;i++)
	{
		int t=i;
		for (int j=i+1;j<=n;j++) if (fabs(l[j][i])>fabs(l[t][i])) t=j;
		if (t!=i) for (int j=i;j<=n+1;j++) swap(l[i][j],l[t][j]);
		for (int j=i+1;j<=n;j++)
		{
			double x=l[j][i]/l[i][i];
			for (int k=i;k<=n+1;k++) l[j][k]-=l[i][k]*x;
		}
	}
	for (int i=n;i>=1;i--)
	{
		for (int j=i+1;j<=n;j++) l[i][n+1]-=l[j][n+1]*l[i][j];
		l[i][n+1]/=l[i][i];
	}
}


void init()
{
	scanf("%d",&n);
	memset(l,0,sizeof(l)); 
	for (int i=1;i<=n+1;i++)
		for (int j=1;j<=n;j++) 
		{
			scanf("%lf",&pos[i][j]);
			if (i!=1)
			{
				l[i-1][j]=2*(pos[i][j]-pos[i-1][j]); 
				l[i-1][n+1]+=pos[i][j]*pos[i][j]-pos[i-1][j]*pos[i-1][j];
			}
		}
}

void print_ans()
{
	for (int i=1;i<=n;i++) 
	{
		printf("%.3lf",l[i][n+1]);
		if (i!=n) printf(" ");
	}
}

int main()
{
	init();
	Gauss();
	print_ans();
	return 0;
}
