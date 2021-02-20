#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=300000+50;
int n;
char s[MAXN];
double f[MAXN],g[MAXN];

int main()
{
	scanf("%d",&n);
	scanf("%s",s+1);
	f[0]=g[0]=0;
	for (int i=1;i<=n;i++)
	{
		if (s[i]=='x') f[i]=f[i-1],g[i]=0;
		if (s[i]=='o') f[i]=f[i-1]+2*g[i-1]+1,g[i]=g[i-1]+1;
		if (s[i]=='?') f[i]=f[i-1]+g[i-1]+0.5,g[i]=(g[i-1]+1)/2;
	}
	printf("%.4lf",f[n]);
	return 0;
} 
