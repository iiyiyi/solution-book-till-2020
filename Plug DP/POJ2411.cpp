#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int MAXN=11;
ll dp[2][1<<MAXN];

void solve(int m,int n)
{
	if (m<n) swap(m,n);
	int cur=0;
	memset(dp,0,sizeof(dp));
	dp[cur][(1<<n)-1]=1;
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++)
		{
			cur^=1;
			/*cur要放在第二重循环后面，一开始写在了三重循环里面*/ 
			memset(dp[cur],0,sizeof(dp[cur]));
			/*不要忘了要清空当前状态*/
			for (int k=0;k<=(1<<n)-1;k++)
			{
				//上放
				if (i!=1 && !(k&(1<<(n-1))))
				{
					int now=(((k<<1)|1)&((1<<n)-1));
					dp[cur][now]+=dp[1-cur][k];
				} 
				//不放
				if (k&(1<<(n-1)))
				{
					int now=((k<<1)&((1<<n)-1));
					dp[cur][now]+=dp[1-cur][k];
				}
				//左放 
				if (j!=1 && (k&(1<<(n-1))) && !(k&1))
				{
					int now=(((k<<1)|3)&((1<<n)-1));
					dp[cur][now]+=dp[1-cur][k];
				} 
			}
		}
	cout<<dp[cur][(1<<n)-1]<<endl;
}

int main()
{
	int m,n;
	while (scanf("%d%d",&m,&n))
	{
		if (m==n && n==0) break;
		solve(m,n);
	}
	return 0;
}
