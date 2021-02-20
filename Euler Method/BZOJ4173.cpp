#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define MOD 998244353
using namespace std;
typedef long long ll;

ll phi(ll x)
{
	ll ret=x;
	for (ll i=2;i*i<=x;i++)
	{
		if (x%i==0)
		{
			ret-=ret/i;
			while (x%i==0) x/=i;
		}
	}
	if (x>1) ret-=ret/x;
	return ret%MOD;
}

void solve()
{
	ll n,m;
	scanf("%lld%lld",&n,&m);
	printf("%lld",(phi(n)%MOD)*(phi(m)%MOD)%MOD*(n%MOD)%MOD*(m%MOD)%MOD); 
}

int main()
{
	solve();
	return 0;
}
