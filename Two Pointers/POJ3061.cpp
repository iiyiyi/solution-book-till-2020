#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
const int MAXN=100000+50;
int num[MAXN],n,s;

void solve()
{
	scanf("%d%d",&n,&s);
	for (int i=1;i<=n;i++) scanf("%d",&num[i]);
	int l=1,r=1,sum=num[1],len=MAXN;
	for (;;)
	{
		if (sum>=s)
		{
			len=min(len,r-l+1);
			sum-=num[l++];
		}
		else
		{
			if (r==n) break;
			sum+=num[++r];
		}
	}
	if (len==MAXN) puts("0");
		else printf("%d\n",len);
}

int main()
{
	int T;
	scanf("%d",&T);
	while (T--)	solve();	
	return 0;
}
