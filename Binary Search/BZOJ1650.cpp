#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN=50000+50;
int l,n,m,d[MAXN];

int check(int dis)
/*这种检验方式在贪心中经常使用*/
{
	int last=0,tmp=0;
	for (int i=1;i<=n;i++)
	{
		if (d[i]-d[last]<dis)
		{
			tmp++;
			if (tmp>m) return 0;
		}
		else last=i;
	} 
	return 1;
}

void init()
{
	scanf("%d%d%d",&l,&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&d[i]);
	sort(d+1,d+n+1);
	d[0]=0;
	d[++n]=l;
}

void bisearch()
{
	int lb=0,ub=l+1;
	while (lb+1<ub)
	{
		int mid=(lb+ub)>>1;
		if (check(mid)) lb=mid;
			else ub=mid;
	}
	printf("%d",lb);
}

int main()
{
	init();
	bisearch();
	return 0;
}
