#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAXN=50000+50;
const int INF=1e9;
struct node
{
	int w,s;
	bool operator < (const node &x) const
	{
		if (w+s<x.w+x.s) return 1;else return 0;
	}
}cow[MAXN];

int main()
{
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d%d",&cow[i].w,&cow[i].s);
	sort(cow+1,cow+n+1);
	int sum=0,ans=-INF;
	for (int i=1;i<=n;i++)
	{
		int now=sum-cow[i].s;
		ans=max(ans,now);
		sum+=cow[i].w;
	}
	printf("%d",ans);
	return 0;
}
