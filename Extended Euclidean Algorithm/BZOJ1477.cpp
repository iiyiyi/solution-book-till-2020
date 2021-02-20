#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;

ll extgcd(ll a,ll b,ll &x,ll &y)
{
	ll ret;
	if (b==0)
	{
		x=1,y=0;
		return a;
	}
	ret=extgcd(b,a%b,x,y);
	ll tmp=x;
	x=y;
	y=tmp-(a/b)*y;
	return ret;
}

int main()
{
	ll X,Y,m,n,L,x,y;
	scanf("%lld%lld%lld%lld%lld",&X,&Y,&m,&n,&L);
	ll d=extgcd(n-m,L,x,y);
	if ((X-Y)%d!=0) puts("Impossible");else
	{ 
		ll delta=abs(L/d);
		x=(x*(X-Y)/d+delta)%delta;
		while (x<0) x=(x+delta)%delta;
		printf("%lld",x);

	}
	return 0;
} 
