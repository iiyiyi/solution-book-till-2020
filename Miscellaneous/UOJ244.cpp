#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=1e5+10;
const ll INF=1e16;
int n;
ll a[MAXN];

void init()
{
	scanf("%d",&n);
	for (int i=0;i<=n;i++) scanf("%lld",&a[i]);
}

void solve()
{
	ll ans=INF;
	ll Min=INF,now=0;
	for (int i=n;i>=0;i--)
	{
		ans=min(ans,now+(4*i+1)*a[i]);
		Min=min(Min,a[i]);
		now=now+2*Min+a[i]*2;
	}
	printf("%lld",ans);
} 

int main()
{
	init();
	solve();
}
