
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int MAXN=100000+50;
const int INF=0x7fffffff;
int a,b,c,d,inp,ub;
int miu[MAXN];

void init()
{
	scanf("%d%d%d%d%d",&a,&b,&c,&d,&inp);
	if (inp!=0)
	{
		b=b/inp;
		d=d/inp;
		ub=min(b,d);
	}
}

void get_miu(int maxn)
{
	int prime[MAXN],pnum=0;
	miu[1]=1;
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
	}
}

ll get_ans()
{
	ll ans1=0,ans2=0;
	for (int k=1;k<=ub;k++)
      ans1+=(ll)miu[k]*(b/k)*(d/k);
    for (int k=1;k<=ub;k++)
      ans2+=(ll)miu[k]*(ub/k)*(ub/k);//这里一定要写成(ll) 
	ll ans=ans1-ans2/2;
    return (ans);
}

int main()
{
	int T;
	scanf("%d",&T);
	get_miu(MAXN);
	for (int i=0;i<T;i++)
	{
		cout<<"Case "<<i+1<<": ";
		init();
		if (inp==0)
		{
			cout<<0<<endl;continue;
		}
		cout<<get_ans()<<endl;
	}
	return 0;
}

