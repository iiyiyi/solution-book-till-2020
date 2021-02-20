#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <vector>
#include <algorithm>
#include <functional>
typedef long long ll;
using namespace std;
 
const int inf = 0x3f3f3f3f;
const int maxn = 1e5;
int tot;
int is_prime[maxn];
int miu[maxn];
int prime[maxn];
 
void Moblus()
{
    tot=0;
    miu[1]=1;
    for(int i=2;i<maxn;i++)
    {
        if(!is_prime[i])
        {
            prime[tot++]=i;
            miu[i]=-1;
        }
 
        for(int j=0;j<tot&&i*prime[j]<maxn;j++)
        {
            is_prime[i*prime[j]]=1;
            if(i%prime[j]) miu[i*prime[j]]=-miu[i];
            else
            {
                miu[i*prime[j]]=0;
                break;
            }
        }
    }
}
 
int tmax;
int num[maxn],cnt[maxn];
ll get_()
{
    for(int i=1;i<=tmax;i++)
    {
        for(int j=i;j<=tmax;j+=i) cnt[i]+=num[j];              //计算GCD为i的集合中的个数
    }
    ll ans = 0;
    for(int i=1;i<=tmax;i++)
    {
        int tt=cnt[i];
        if(tt>=4)
        ans+=(ll)miu[i]*tt*(tt-1)*(tt-2)*(tt-3)/24;
    }
    return ans;
}
 
int main()
{
    int n;
    Moblus();
    while(scanf("%d",&n)!=EOF)
    {
        memset(num,0,sizeof(num));
        memset(cnt,0,sizeof(cnt));
        for(int i = 0; i<n; i++)
        {
            int tt;
            scanf("%d",&tt);
            num[tt] ++;
            tmax = max(tmax,tt);
        }
        if(n<4)
            printf("0\n");
        else
            printf("%lld\n",get_());
    }
}
