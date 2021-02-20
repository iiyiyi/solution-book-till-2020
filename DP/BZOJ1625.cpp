#include<bits/stdc++.h>
using namespace std;
const int MAXN=12880+5;

int main()
{
	int dp[MAXN],n,m;
	memset(dp,0,sizeof(dp));//如果需要恰巧装满，则dp[0]=0,dp[else]=-INF
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		int w,d;
		scanf("%d%d",&w,&d);
		for (int j=m;j>=w;j--) dp[j]=max(dp[j],dp[j-w]+d);
	}
	printf("%d",dp[m]);
	return 0;
} 
