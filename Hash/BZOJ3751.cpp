#include<bits/stdc++.h>
using namespace std;
const int MAXN=100+5;
const int MAXM=1000000+5;
const int MAXP=30000; 
typedef long long ll;
int prime[4]={17389,22349,22367,22369};
int n,m,a[MAXN],hash[MAXN][4],table[MAXP][4],ans[MAXM],cnt=0;

ll get_table(int j,int x)
{
	ll ret=0;
	for (int i=n;i>=0;i--)
		ret=(ret*x+hash[i][j])%prime[j];
	return ret;
}

int read(int x)
{
	char str[10010];
	scanf("%s",str);
	int negative=0;
	for (int i=0;str[i];i++)
	{
		if (str[i]=='-') negative=1;
			else for (int j=0;j<4;j++)
					hash[x][j]=((hash[x][j]*10)%prime[j]+(str[i]-'0'))%prime[j];
	}
	if (negative)
		for (int j=0;j<4;j++)
			hash[x][j]=(prime[j]-hash[x][j])%prime[j];
}

void init()
{
	memset(hash,0,sizeof(hash));
	scanf("%d%d",&n,&m);
	for (int i=0;i<=n;i++) read(i);
	for (int i=0;i<4;i++)
		for (int j=0;j<prime[i];j++) table[j][i]=get_table(i,j);
}

void solve()
{
	for (int i=1;i<=m;i++)
	{
		int flag=1;
		for (int j=0;j<4;j++)
			if (table[i%prime[j]][j])
			{
				flag=0;
				break;
			}
		if (flag) ans[++cnt]=i;
	}
	printf("%d\n",cnt);
	for (int i=1;i<=cnt;i++) printf("%d\n",ans[i]);
}

int main()
{
	init();
	solve();
	return 0;	
} 
