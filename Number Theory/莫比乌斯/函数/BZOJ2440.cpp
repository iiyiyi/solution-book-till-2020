#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll MAXN=50000+50; 
const ll INF=0x7fffffff;
int T;
ll k;
int miu[MAXN];
ll prime[MAXN];
int pnum=0;

void get_miu()
{
	for (int i=0;i<MAXN;i++) miu[i]=-INF;
	miu[1]=1;
	for (int i=2;i<MAXN;i++)
	{
		if (miu[i]==-INF)
		{
			miu[i]=-1;
			prime[++pnum]=i;
		}
		for (int j=1;j<=pnum;j++)
		{
			if (i*prime[j]>=MAXN) break;
			if (i%prime[j]==0) miu[i*prime[j]]=0;
				else miu[i*prime[j]]=-miu[i];
		}
	}
}

ll square(ll x)
{
	ll res=0;
	for (int i=1;i*i<=x;i++) res+=miu[i]*(x/(i*i));
	return res;
}

ll get_ans()
{
	ll lb=-1,ub=MAXN*MAXN;
	while (ub-lb>1)
	{
		ll mid=(lb+ub)>>1;
		ll nowk=square(mid);
		if (nowk>=k) ub=mid;
			else lb=mid;
	}
	return ub;
}

int main()
{
	get_miu();
	scanf("%d",&T);
	for (int i=0;i<T;i++)
	{
		scanf("%lld",&k);
		printf("%lld\n",get_ans());
	}
	return 0;
}
