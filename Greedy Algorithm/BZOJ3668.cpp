#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a,b,n,m;

void init()
{
	scanf("%d%d",&n,&m);
	a=0,b=1073741823;
	for (int i=0;i<n;i++)
	{
		char str[3];
		int x;
		scanf("%s%d",str,&x);
		if (str[0]=='A') a&=x,b&=x;
			else if (str[0]=='O') a|=x,b|=x;
				else if (str[0]=='X') a^=x,b^=x;
	}
}

void solve()
{
	int attack=0,ans=0;
	for (int i=30;i>=1;i--)
	{
		if ((a>>(i-1))&1) ans+=1<<(i-1);
			else if (((b>>(i-1))&1) && attack+(1<<(i-1))<=m) ans+=1<<(i-1),attack+=(1<<(i-1));
	}
	printf("%d",ans);
}

int main()
{
	init();
	solve();
	return 0;
} 
