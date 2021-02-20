#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1000+50;
int f[MAXN][MAXN];

void add(int a,int b)
{
	int lena=f[a][0],lenb=f[b][0];
	int len=max(lena,lenb);
	int i,rem=0;
	for (i=1;i<=len || rem;i++)
	{
		rem=(f[a][i]+f[b][i])/10;
		f[a][i]+=f[b][i];
		f[a][i]%=10;
		f[a][i+1]+=rem;
	}
	f[a][0]=i-1;
}

int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	memset(f,0,sizeof(f));
	f[0][0]=f[0][1]=1;
	for (int i=1;i<=k;i++)
		for (int j=i;j<=n;j++) add(j,j-i);
	for (int i=f[n][0];i>=1;i--) printf("%d",f[n][i]);printf("\n");
	return 0;
} 
