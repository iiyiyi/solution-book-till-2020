#include<bits/stdc++.h>
using namespace std;
const int MAXN=5000+5;
const int MAXC=50000+50;

int main()
{
	int c,h,v[MAXN],f[MAXC];
	scanf("%d%d",&c,&h);
	memset(f,0,sizeof(f));
	for (int i=1;i<=h;i++)
	{
		scanf("%d",&v[i]);
		for (int j=c;j>=v[i];j--) f[j]=max(f[j],f[j-v[i]]+v[i]);
	}
	printf("%d",f[c]);
	return 0;
} 
