#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=300000+50;
int s[MAXN*2],n;

void init()
{
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		scanf("%d",&s[i]);
		s[i+n]=s[i];
	} 
}

void solve()
{
	int i=0,j=1,k=0;
	while (k<n)
	{
		int t=s[(i+k)%(2*n)]-s[(j+k)%(2*n)];
		if (t==0) k++;
		else
		{
			if (t>0) i+=k+1;
				else j+=k+1;
			if (i==j) j++;
			k=0;
		}
	}
	for (int r=1,now=i;r<=k;r++,now=(now+1)%(2*n)) 
	{
		printf("%d",s[now]);
		if (r!=k) printf(" ");
	}
}

int main()
{
	init();
	solve();
	return 0;
}
