#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const int MAXN=50000+50;
int n,l;
int c[MAXN];
LL s[MAXN],g[MAXN],x[MAXN],y[MAXN],f[MAXN];

LL square(LL x)
{
	return x*x;
}

double slop(int i,int j)
{
	return ((y[j]-y[i])/(x[j]-x[i]));
}

void dp()
{
	memset(f,0,sizeof(f));
	int head=0,tail=0;
	int q[MAXN];
	q[head]=0;
	for (int i=1;i<=n;i++)
	{
		y[i]=f[i-1]+square(x[i]);
		while (head+1<tail && slop(q[tail-2],q[tail-1])>slop(q[tail-1],i)) tail--;
		q[tail++]=i;
		while (head+1<tail && slop(q[head],q[head+1])<2.0*g[i]) head++;
		f[i]=f[q[head]-1]+square(g[i]-x[q[head]]);
	}
}

void init()
{
	scanf("%d%d",&n,&l);
	memset(s,0,sizeof(s));
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&c[i]);
		s[i]=s[i-1]+c[i];
		g[i]=s[i]+i-l;
		x[i]=s[i-1]+i;
	}
}

void printans()
{
	printf("%lld",f[n]); 
}

int main()
{
	init();
	dp();
	printans();
	return 0;
}
