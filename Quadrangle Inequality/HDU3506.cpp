#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1000+50;
const int INF=0x7fffffff;
int n;
int a[MAXN*2],sum[MAXN*2];
int dp[MAXN*2][MAXN*2],s[MAXN*2][MAXN*2];

void init()
{
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		a[i+n]=a[i];
	}
	sum[0]=0;
	for (int i=1;i<=2*n;i++) sum[i]=sum[i-1]+a[i];
}

void solve()
{
	memset(dp,0,sizeof(dp));
	memset(s,0,sizeof(s));
	for (int i=1;i<=2*n;i++) s[i][i]=i;
	for (int i=2*n;i>=1;i--)
	{
		for (int j=i+1;j<=2*n;j++)
		{
			dp[i][j]=INF;
			for (int k=s[i][j-1];k<=s[i+1][j];k++)
			{
				if (dp[i][j]>dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1])
				{
					s[i][j]=k;
					dp[i][j]=dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1];
				}
			}
		}
	}
	int ans=INF;
	for (int i=1;i<=n;i++) ans=min(ans,dp[i][i+n-1]);
	printf("%d\n",ans);
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
