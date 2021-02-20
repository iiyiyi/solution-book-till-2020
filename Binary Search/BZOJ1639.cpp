#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAXN=100000+50;
int n,m,a[MAXN],lb,ub;

int check(int x)
{
	int tmp=0,t=1;
	for (int i=1;i<=n;i++)
	{
		if (tmp+a[i]<=x) tmp+=a[i];
			else
			{
				t++;
				if (t>m) return 0;
				tmp=a[i];
			}
	}
	return 1;
}

void init()
{
	scanf("%d%d",&n,&m);
	ub=0,lb=0;
	for (int i=1;i<=n;i++) scanf("%d",&a[i]),ub+=a[i],lb=max(lb,a[i]-1);
}

void solve()
{
	while (lb+1<ub)
	{
		int mid=(lb+ub)>>1;
		if (check(mid)) ub=mid;
			else lb=mid;
	}
	printf("%d",ub);
}

int main()
{
	init();
	solve();
	return 0;
}
