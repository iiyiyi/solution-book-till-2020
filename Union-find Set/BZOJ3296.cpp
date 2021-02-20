#include<bits/stdc++.h>
using namespace std;
const int MAXN=10000+30000+50;
int n,m,t;
int u[MAXN],h[MAXN],appear[MAXN];

int find(int x)
{
	int tmp=x;
	while (u[tmp]!=tmp) tmp=u[tmp];
	while (u[x]!=x)
	{
		int temp=u[x];
		u[x]=tmp;
		x=temp;
	}
	return tmp;
}

void union_set(int fa,int fb)
{
	if (h[fa]>=h[fb])
	{
		u[fb]=fa;
		if (h[fa]==h[fb]) h[fa]++;
	}
	else u[fa]=fb;
}

void solve()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=(n+m);i++) u[i]=i,h[i]=0;
	for (int i=1;i<=n;i++)
	{
		int k,lang;
		scanf("%d",&k);
		for (int j=1;j<=k;j++)
		{
			scanf("%d",&lang);
			int fa=find(i),fb=find(lang+n);
			if (fa!=fb)	union_set(fa,fb);
		}
	}
	int t=0;
	memset(appear,0,sizeof(appear));
	for (int i=1;i<=n;i++)
	{
		int fa=find(i);
		if (appear[fa]==0) t++,appear[fa]=1;
	}
	printf("%d",t-1);
}

int main()
{
	solve();
	return 0;
}
