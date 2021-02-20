#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=10000000+50;
typedef long long ll;
int n;
int prime[MAXN],pnum=0;
int phi[MAXN];
ll sum[MAXN];

void get_phi(int maxn)
{
	memset(phi,0,sizeof(phi));
	memset(sum,0,sizeof(sum));
	phi[1]=sum[1]=1;
	for (int i=2;i<=maxn;i++)
	{
		if (phi[i]==0)
		{
			prime[++pnum]=i;
			phi[i]=i-1;
		}
		for (int j=1;j<=pnum;j++)
		{
			if (i*prime[j]>maxn) break;
			if (i%prime[j]==0) phi[i*prime[j]]=phi[i]*prime[j];
				else phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
		sum[i]=sum[i-1]+phi[i];
	}
}

int main()
{
	scanf("%d",&n);
	get_phi(n);
	ll ans=0;
	for (int i=1;i<=pnum;i++)
	{
		ans+=sum[n/prime[i]]*2-1;
	}
	printf("%lld",ans);
	return 0;	
} 
