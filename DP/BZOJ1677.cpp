#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=1000000+50;
const int MOD=1e9;

int main()
{
	int n;
	scanf("%d",&n);
	int k=1,dp[MAXN];
	memset(dp,0,sizeof(dp));
	dp[0]=1;
	while (k<=n)
	{
		for (int v=k;v<=n;v++) dp[v]=(dp[v]+dp[v-k])%MOD;
		k=k*2;
	}
	printf("%d",dp[n]%MOD);
	return 0;
}
