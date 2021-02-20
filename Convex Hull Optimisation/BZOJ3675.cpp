#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const int MAXN=100100;
const int MAXK=250;
int n,k;
LL sum[MAXN],x[2][MAXN],y[MAXN],f[MAXN][2],fr[MAXN][MAXK];
int cur;

void init()
{
    scanf("%d%d",&n,&k);    
    for (int i=1;i<=n;i++) 
    {
        int tmp;
        scanf("%d",&tmp);
        y[i]=sum[i]=sum[i-1]+tmp;
    }
}

LL dp()
{
    memset(f,0,sizeof(f));
    cur=0;
    for (int i=1;i<=n;i++) x[1-cur][i]=f[i][cur]-(sum[i]*sum[i]);
    for (int j=2;j<=k+1;j++)
    {
        cur=1-cur;
        int head=0,tail=1,que[MAXN];
        for (int i=j-1;i<=n;i++)//上一次至多分割为j-1部分，则至少从j-1开始 
        {
            while (head+1<tail && x[cur][que[head]]-x[cur][que[head+1]]<=g[i]*(y[que[head]]-y[que[head+1]])) head++;
            int best=que[head];
            f[i][cur]=f[best][1-cur]+sum[best]*(sum[i]-sum[best]);
            fr[i][j]=best;
            while (head+1<tail && (LL)(x[cur][que[tail-1]]-x[cur][i])*(y[que[tail-2]]-y[que[tail-1]])>=(LL)(x[cur][que[tail-2]]-x[cur][que[tail-1]])*(y[que[tail-1]]-y[i])) tail--;
            que[tail++]=i;
            x[1-cur][i]=f[i][cur]-(sum[i]*sum[i]);
        }
    }
    return (f[n][cur]);
}

void printans()
{
    printf("%lld\n",dp());
    int ans[MAXK];
	memset(ans,0,sizeof(ans));//不要忘记初始化★
    for (int i=k+1;i>=2;i--)
    {
    	ans[++ans[0]]=fr[n][i];
    	n=fr[n][i];
	}
	for (int i=ans[0];i>=1;i--) printf("%d ",ans[i]);
}

int main()
{
    init();
    printans();
    return 0;   
} 
