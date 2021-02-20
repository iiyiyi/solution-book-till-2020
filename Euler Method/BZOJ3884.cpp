#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long ll;
using namespace std;

int get_phi(int x)
{
	int res=x;
	for (int i=2;i*i<=x;i++)
	{
		if (x%i==0)
		{
			res-=res/i;
			while (x%i==0) x/=i;
		}
	}
	if (x>1) res-=res/x;
	return res;
}

int quick_power(ll x,int y,int MOD)//这里有可能会溢出，用long long
{
	ll ret=1;
	while (y)
	{
		if (y&1) ret=(ret*x)%MOD;
		x=(x*x)%MOD;
		y>>=1;
	}
	return ret;
}

int solve(int p)
{
	if (p==1) return 0;
	int k=0;
	while (!(p&1)) p>>=1,++k;
	int phi=get_phi(p);
	int re=solve(phi);
	re=(re-k%phi+phi)%phi;
	int ans=quick_power(2,re,p)%p;
	return (ans<<k);
}

void init()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		int p;
		scanf("%d",&p);
		printf("%d\n",solve(p));
	}
}

int main()
{
	init();
	return 0;
}
