#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100000+50;
typedef long long ll;
int n,d;
ll h[MAXN];
ll ans[MAXN],tmp[MAXN];
ll ansx;

void init()
{
	scanf("%d%d",&n,&d);
	for (int i=1;i<=n;i++) scanf("%lld",&h[i]);
} 

int check(ll x)
{
	int j=1;
	ll sum=0;
	for (int i=1;i<=d;i++)
	{
		while (sum<x && j<=n)
		{
			tmp[j]=i;
			sum+=h[j++];
		} 
		if (sum<x) return 0;
		sum>>=1;
	}
	while (j<=n) tmp[j++]=d;
	for (int i=1;i<=n;i++) ans[i]=tmp[i];
	ansx=x;
	return 1;
}

void solve()
{
	ll lb=1,ub=50000000000ll;
	while (lb<=ub)
	{
		ll mid=(lb+ub)>>1;
		if (check(mid)) lb=mid+1;else ub=mid-1;
	}
	printf("%lld\n",ansx);
	for (int i=1;i<=n;i++) 
		printf("%lld\n",ans[i]); 
}

int main()
{
	init();
	solve();
	return 0;
} 
