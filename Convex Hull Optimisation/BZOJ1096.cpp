#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
using namespace std;
const int MAXN=1000000+50;
typedef long long ll;
int n,d[MAXN],c[MAXN];
ll psum[MAXN],pdsum[MAXN],f[MAXN],y[MAXN];
int que[MAXN];

double slop(int i,int j)
{
	ll x1=psum[i];
	ll x2=psum[j];
	ll y1=f[i]+pdsum[i];
	ll y2=f[j]+pdsum[j];
	return(1.0*(y2-y1)/(x2-x1));
}

void init()
{
	scanf("%d",&n);
	memset(psum,0,sizeof(psum));
	memset(pdsum,0,sizeof(pdsum));
	memset(f,0,sizeof(f));
	for (int i=1;i<=n;i++)
	{
		int p;
		scanf("%d%d%d",&d[i],&p,&c[i]);
		psum[i]=psum[i-1]+(ll)p;
		pdsum[i]=pdsum[i-1]+(ll)p*d[i];
	}
}

ll dp()
{
	int head=0,tail=1;
	for (int i=1;i<=n;i++)
	{
		while (head+1<tail && slop(que[head],que[head+1])<=1.0*d[i]) head++;
		int j=que[head];
		f[i]=d[i]*psum[i]-pdsum[i]+c[i]+f[j]-d[i]*psum[j]+pdsum[j];
		while (head+1<tail && slop(que[tail-1],i)<=slop(que[tail-2],que[tail-1])) tail--;
		que[tail++]=i;
	}
	return(f[n]);
}

int main()
{
	init();
	printf("%lld\n",dp());
	return 0;
} 
