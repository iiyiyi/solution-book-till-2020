#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAXN=1e6+5;
int appear[MAXN],p,a[MAXN],hash[MAXN],d;

void init()
{
	scanf("%d",&p);
	for (int i=1;i<=p;i++) scanf("%d",&a[i]),hash[i]=a[i];
	sort(hash+1,hash+p+1);
	d=unique(hash+1,hash+p+1)-(hash+1);
	for (int i=1;i<=p;i++) a[i]=lower_bound(hash+1,hash+d+1,a[i])-hash;
}

void solve()
{
	memset(appear,0,sizeof(appear));
	appear[a[1]]=1;
	int l=1,r=1,sum=1,ans=MAXN;
	for (;;)
	{	
		if (sum>=d)
		{
			ans=min(ans,(r-l+1));
			appear[a[l]]--;
			if (!appear[a[l++]]) sum--;
		}
		else
		{
			if (r==p) break;
			appear[a[r+1]]++;
			if (appear[a[++r]]==1) sum++;
		}
	}
	printf("%d",ans);
}

int main()
{
	init();
	solve();
	return 0;
}
