#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1000000+500;
char a[MAXN*2],b[MAXN*2];
int n,m;

void init()
{
	scanf("%s",a);
	scanf("%s",b);
	n=strlen(a);
	m=strlen(b);
	for (int i=0;i<n;i++) a[i+n]=a[i],b[i+n]=b[i];
}

int getmin(char *s)
{ 
	int i=0,j=1,k=0;
	while (i<2*n && j<2*n && k<n)
	{
		int t=s[(i+k)%(2*n)]-s[(j+k)%(2*n)];
		if (!t) k++;
		else
		{
			if (t>0) i+=k+1;
				else j+=k+1;
			if (i==j) j++;
			k=0;
		}
	}
	return min(i,j);
}

void solve()
{
	int cala=getmin(a);
	int calb=getmin(b);
	int flag=1;
	for (int i=0;i<n;i++)
		if (a[(i+cala)%(2*n)]!=b[(i+calb)%(2*n)])
		{
			flag=0;
			break;
		}
	if (flag)
	{
		puts("Yes");
		for (int i=0;i<n;i++) printf("%c",a[(i+cala)%(2*n)]);
	}
	else puts("No");
}

int main() 
{
	init();
	if (n==m) solve();
		else puts("No"); 
	return 0;
}
