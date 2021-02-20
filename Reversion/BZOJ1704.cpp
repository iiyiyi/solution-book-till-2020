#include<bits/stdc++.h>
using namespace std;
const int INF=0x7fffffff;
const int MAXN=5005;
int n,dir[MAXN]; 
int f[MAXN];

int calc(int k)
{
	memset(f,0,sizeof(f));
	int sum=0,res=0;
	for (int i=1;i+k-1<=n;i++)
	{
		if ((dir[i]+sum)%2!=0) res++,f[i]=1;
		sum+=f[i];
		if (i-k>=0) sum-=f[i-k];
	}
	if (k==2) for (int i=1;i+k-1<=n;i++) cout<<i<<"!"<<f[i]<<endl;
	
	for (int i=n-k+2;i<=n;i++)
	{
		if ((dir[i]+sum)%2!=0) return -1;
		if (i-k>=0) sum-=f[i-k];
	}
	return res;
}

void init()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		char s[2];
		scanf("%s",s);
		if (s[0]=='B') dir[i]=1;else dir[i]=0; 
	 } 
}

void solve()
{
	int ans=INF,ansk;
	for (int i=1;i<=n;i++)
	{
		int now=calc(i);
		if (now>=0 && ans>now)
		{
			ans=now;
			ansk=i;
		}
	}
	printf("%d %d\n",ansk,ans);
}

int main()
{
	init();
	solve();
	return 0;
}
