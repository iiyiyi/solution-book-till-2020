#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int MAXN=50000+50;
const int INF=0x7ffffff;
int a,b,d;
int miu[MAXN];
int miu_sum[MAXN];

void get_miu(int maxn)
{
	int prime[MAXN],pnum=0;
	memset(miu_sum,0,sizeof(miu_sum));
	miu[1]=miu_sum[1]=1;
	for (int i=2;i<maxn;i++) miu[i]=-INF;
	for (int i=2;i<maxn;i++)
	{
		if (miu[i]==-INF)
		{
			miu[i]=-1;
			prime[++pnum]=i;
		}
		for (int j=1;j<=pnum;j++)
		{
			if (i*prime[j]>=maxn) break;
			if (i%prime[j]==0) miu[i*prime[j]]=0;
				else miu[i*prime[j]]=-miu[i];
		}
		miu_sum[i]=miu_sum[i-1]+miu[i];
	}
}

ll get_ans(int a,int b,int d)
{
	int ub=min(a,b),pos;
	ll ans=0;
	for (int i=1;i<=ub;i=pos+1)
	{
		pos=min(a/(a/i),b/(b/i));
		ans+=(ll)(miu_sum[pos]-miu_sum[i-1])*(a/i)*(b/i);
	}
	return ans;
}

int main()
{
	int T;
	scanf("%d",&T);
	get_miu(MAXN-1); 
	for (int i=0;i<T;i++)
	{
		scanf("%d%d%d",&a,&b,&d);
		a/=d;b/=d;
		printf("%lld\n",get_ans(a,b,d));
	}
}
