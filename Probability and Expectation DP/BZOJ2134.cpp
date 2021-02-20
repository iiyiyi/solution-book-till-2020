#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=10000000+50;
int a[MAXN];
double ans;
int n,A,B,C;

void init()
{
	scanf("%d%d%d%d%d",&n,&A,&B,&C,a+1);
	for (int i=2;i<=n;i++) a[i]=((ll)a[i-1]*A+B)%100000001;
	for (int i=1;i<=n;i++) a[i]=a[i]%C+1;
}

void solve()
{
	ans=0;
	for (int i=1;i<=n;i++)
	{
		double x=(double)a[i]*1.0,y=(double)a[i%n+1]*1.0;
		ans+=1.0/max(x,y);
	}
	printf("%.3f\n",ans);
}

int main()
{
	init();
	solve();
	return 0;
}
