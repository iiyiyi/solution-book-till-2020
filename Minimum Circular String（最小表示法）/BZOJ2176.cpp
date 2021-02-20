#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=10000000+50;
unsigned char str[MAXN*2];
int n;

void init()
{
	scanf("%d",&n);
	scanf("%s",str);
	for (int i=0;i<n;i++) str[i+n]=str[i];
}

void solve()
{
	int i=0,j=1,k=0;
	while (i<2*n && j<2*n && k<n)
	{
		int t=str[(i+k)%(2*n)]-str[(j+k)%(2*n)];
		if (!t) k++;
			else
			{	
				if (t>0) i+=k+1;
					else j+=k+1;
				if (i==j) j++;
				k=0; 
			}
	}
	
	for (int r=0;r<n;r++)
		printf("%c",str[(r+i)%(2*n)]);
}

int main()
{
	init();
	solve();
	return 0;
}
