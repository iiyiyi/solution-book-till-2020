#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int MAXN=50000+50;
const int INF=0x7fffffff;
int a,b,c,d,k;
int miu[MAXN],prime[MAXN],pnum;
ll miusum[MAXN];

void getmiu(int maxn)
{
    memset(miusum,0,sizeof(miusum));
    miu[1]=miusum[1]=1;
    for (int i=2;i<maxn;i++) miu[i]=-INF;
    for (int i=2;i<maxn;i++)
    {
        if (miu[i]==-INF)
        {
            miu[i]=-1;
            prime[++pnum]=i;
        }
        for (int j=1;j<=pnum;j++)
        {
            if (i*prime[j]>=maxn) break;
            if (i%prime[j]==0) miu[i*prime[j]]=0;
                else miu[i*prime[j]]=-miu[i];
			
        }
        miusum[i]=miusum[i-1]+miu[i];
    }
}

ll solve(int b,int d,int k)
{
	b/=k;d/=k;
	int ub=min(b,d),pos;
	ll ret=0;
	for (int i=1;i<=ub;i=pos+1)
	{
		pos=min(b/(b/i),d/(d/i));
		ret+=(ll)(miusum[pos]-miusum[i-1])*(ll)(b/i)*(ll)(d/i);
	}
	return ret;
}

int main()
{
	int T;
	getmiu(MAXN-1);
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
		ll ans=solve(b,d,k)-solve(a-1,d,k)-solve(c-1,b,k)+solve(a-1,c-1,k);
		printf("%lld\n",ans);
	}
}
