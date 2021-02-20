#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=20000+50;
const int INF=20000*200+5;
int n,val,b[MAXN],c[MAXN];
int f[MAXN];//凑出纸值x的面值数量 

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&b[i]);
	for (int i=1;i<=n;i++) scanf("%d",&c[i]);
	scanf("%d",&val);
	f[0]=0;
	for (int i=1;i<=val;i++) f[i]=INF;
	for (int i=1;i<=n;i++)
		for (int k=1;c[i];k<<=1)
		{
			k=min(k,c[i]);
			c[i]-=k;
			for (int j=val;j>=k*b[i];j--)
				f[j]=min(f[j],f[j-k*b[i]]+k);
		}
	printf("%d",f[val]);
	return 0;
}
