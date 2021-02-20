#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000000+50;
int maxque[MAXN],minque[MAXN];
int n,m,c,v[MAXN],ans[MAXN];
int l1,r1,l2,r2;

void solve()
{
	scanf("%d%d%d",&n,&m,&c);
	l1=l2=1,r1=r2=1;
	scanf("%d",&v[1]);
	maxque[1]=minque[1]=1;
	ans[0]=0;
	if (m==1) ans[0]++,ans[ans[0]]=1;
	for (int i=2;i<=n;i++)
	{
		scanf("%d",&v[i]);
		while (maxque[l1]<=i-m && l1<=r1) l1++;
		while (v[maxque[r1]]<=v[i] && l1<=r1) r1--;
		maxque[++r1]=i;
		
		while (minque[l2]<=i-m && l2<=r2) l2++;
		while (v[minque[r2]]>=v[i] && l2<=r2) r2--;
		minque[++r2]=i;
		
		if (i>=m && v[maxque[l1]]-v[minque[l2]]<=c) ans[++ans[0]]=i-m+1;
	}
	
	if (ans[0]==0) puts("NONE");
		else for (int i=1;i<=ans[0];i++) printf("%d\n",ans[i]);
}

int main()
{
	solve();
	return 0; 
}
