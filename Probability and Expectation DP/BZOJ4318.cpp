#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
double l1[2],l2[2],f[2];
int n; 

int main()
{
	scanf("%d",&n);
	int cur=0; 
	for (int i=1;i<=n;i++,cur=1-cur)
	{
		double a1;
		scanf("%lf",&a1);
		l1[cur]=(l1[1-cur]+1)*a1;
		l2[cur]=(l2[1-cur]+2*l1[1-cur]+1)*a1;
		f[cur]=f[1-cur]+(3*l2[1-cur]+3*l1[1-cur]+1)*a1;
	}
	printf("%.1lf\n",f[1-cur]);
	return 0;
}
