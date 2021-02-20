#include<bits/stdc++.h>
using namespace std;
const int INF=1e9;
const int MAXN=2000+50;
int n,m,f[MAXN][MAXN],a[MAXN],b[MAXN],tmp[MAXN],premin[MAXN];

void dp()
{
	memset(premin,0,sizeof(premin));
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{	
			f[i][j]=premin[j]+abs(a[i]-b[j]);
			if (j==1) premin[j]=f[i][j];else premin[j]=min(premin[j-1],f[i][j]);
		}
}

void init()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
}

void solve()
{
	int ans=INF;
	for (int i=1;i<=n;i++) b[i]=a[i];
	sort(b+1,b+n+1);
	m=unique(b+1,b+n+1)-(b+1);
	dp();
	for (int i=1;i<=m;i++) ans=min(ans,f[n][i]);
	for (int i=1;i<=m;i++) tmp[i]=b[i];
	for (int i=1;i<=m;i++) b[n-i+1]=tmp[i];
	dp();
	for (int i=1;i<=m;i++) ans=min(ans,f[n][i]);
	printf("%d",ans);
}

int main()
{
	init();
	solve();
	return 0;
}
