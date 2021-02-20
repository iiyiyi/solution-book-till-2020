#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
const int MAXN=100000+50;
int a[MAXN*2];
int p[MAXN*2]; 
int n;

void init()
{
	memset(a,0,sizeof(0));
	scanf("%d",&n);
	a[0]=-1;
	a[1]=0;
	for (int i=1,j=1;i<=n;i++)
	{
		scanf("%d",&a[++j]);
		a[++j]=0;
	}
	n=n*2+1;
}

void solve()
{
	int mx=0,mxid=0;
	memset(p,0,sizeof(p));
	for (int i=1;i<=n;i++)
	{
		if (mx>i) p[i]=((p[2*mxid-i]<(mx-i))?p[2*mxid-i]:(mx-i));
			else p[i]=1;
		while (a[i-p[i]]==a[i+p[i]] && a[i-p[i]]<=a[i-p[i]+2]) p[i]++;
		if (i+p[i]>mx)
		{
			mx=i+p[i];
			mxid=i;
		}
	}
}

int printans()
{
	int ans=-1;
	for (int i=1;i<=n;i++) ans=max(ans,p[i]);
	ans--;
	return ans;
}

int main()
{
	int T;
	scanf("%d",&T);
	for (int i=0;i<T;i++)
	{
		init();
		solve();
		cout<<printans()<<endl;
	}
	return 0;
}
