#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAXV=305;
const int MAXP=35;
const int INF=0x7fffffff;
int v,p;
int dis[MAXV],sum[MAXV],w[MAXV][MAXV];//w[i][j]表示在[i,j]间建立一个邮局的最小代价 
int s[MAXV][MAXP],dp[MAXV][MAXP];

void init()
{
	scanf("%d%d",&v,&p);
	sum[0]=0;
	for (int i=1;i<=v;i++) scanf("%d",&dis[i]);
	sort(dis+1,dis+v+1);
	for (int i=1;i<=v;i++) sum[i]=dis[i]+sum[i-1];
	for (int i=1;i<=v;i++)
	{
		w[i][i]=0;
		for (int j=i+1;j<=v;j++)
		{
			if ((i+j)%2==0) w[i][j]=sum[j]-sum[(i+j)/2]-sum[(i+j)/2-1]+sum[i-1];
				else w[i][j]=sum[j]-sum[(i+j)/2]-sum[(i+j)/2-1]+sum[i-1]-dis[(i+j)/2];
		}
	}
}

void solve()
{
	memset(dp,127,sizeof(dp));
	for (int i=1;i<=v;i++) dp[i][1]=w[1][i];
	for (int j=2;j<=p;j++)
	{
		s[v+1][j]=v-1;
		for (int i=v;i>=j;i--)
		{
			for (int k=s[i][j-1];k<=s[i+1][j];k++)
			{
				if (dp[i][j]>dp[k][j-1]+w[k+1][i])//一开始这里敲成了w[k+1][j] 
				{
					dp[i][j]=dp[k][j-1]+w[k+1][i];
					s[i][j]=k;
				}
			}
		} 
	}
	printf("%d",dp[v][p]); 
}

int main()
{
	init();
	solve();	
	return 0;	
} 
