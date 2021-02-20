#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int INF=0x7fffffff;
const int MAXN=10000000+50;
typedef long long ll;
int miu[MAXN],g[MAXN],prime[MAXN],pnum=0;
ll sum[MAXN];
int N,M;

void get_miu(int maxn)
{
	miu[1]=1;
	g[1]=0;
	sum[1]=sum[0]=0;
	for (int i=2;i<maxn;i++) miu[i]=-INF;
	for (int i=2;i<maxn;i++)
	{
		if (miu[i]==-INF)
		{
			miu[i]=-1;
			prime[++pnum]=i;
			g[i]=1;
		}
		for (int j=1;j<=pnum;j++)
		{
			if (i*prime[j]>=maxn) break;
			if (i%prime[j]==0) 
			{
				miu[i*prime[j]]=0;
				g[i*prime[j]]=miu[i];
			}
				else
				{
					miu[i*prime[j]]=-miu[i];
					g[i*prime[j]]=miu[i]-g[i];
				} 
		}
		sum[i]=sum[i-1]+g[i];
	}
} 

void get_ans()
{
	ll ans=0; 
	scanf("%d%d",&N,&M);
	if (N>M) swap(N,M);
	int pos;
	for (int t=1;t<=N;t=pos+1)
	{
		pos=min(N/(N/t),M/(M/t));
		ans+=(ll)(sum[pos]-sum[t-1])*(N/t)*(M/t);
	}
	printf("%lld\n",ans);
}

int main()
{
	get_miu(MAXN);
	int T;
	scanf("%d",&T);
	while (T--) get_ans();
	return 0;
} 
