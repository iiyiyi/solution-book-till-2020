#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const int MAXN=100100;
const int MAXK=250;
int n,k;
LL sum[MAXN],f[MAXN][2];
int cur;

int read()
{
    int x=0;
    char ch=getchar();
    while (ch<'0'||ch>'9')
        ch=getchar();
    while (ch>='0'&&ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x;
}

void init()
{
	n=read();k=read();  
    for (int i=1;i<=n;i++) 
    {
        int tmp;
		tmp=read();
        sum[i]=sum[i-1]+tmp;
    }
}

void dp()
{
    memset(f,0,sizeof(f));
    cur=0;
    for (int j=2;j<=k+1;j++)
    {
        cur=1-cur;
        int head=0,tail=1,que[MAXN];
        for (int i=j-1;i<=n;i++)//上一次至多分割为j-1部分，则至少从j-1开始 
        {
            while (head+1<tail && (f[que[head]][1-cur]-(LL)(sum[que[head]]*sum[que[head]])-f[que[head+1]][1-cur]+(LL)(sum[que[head+1]]*sum[que[head+1]])<=(LL)-sum[i]*(sum[que[head]]-sum[que[head+1]]))) head++;
            int best=que[head];
            f[i][cur]=f[best][1-cur]+sum[best]*(sum[i]-sum[best]);
            while (head+1<tail)
            {
            	LL x1=f[que[tail-2]][1-cur]-(LL)(sum[que[tail-2]]*sum[que[tail-2]]);
            	LL x2=f[que[tail-1]][1-cur]-(LL)(sum[que[tail-1]]*sum[que[tail-1]]);
            	LL x3=f[que[i]][1-cur]-(LL)(sum[que[i]]*sum[que[i]]);
            	LL y1=sum[que[tail-2]],y2=sum[que[tail-1]],y3=sum[que[i]];
            	if ((LL)(x1-x2)*(y2-y3)<=(LL)(x2-x3)*(y1-y2)) tail--;else break;
			}
            que[tail++]=i;
        }
    }
}

void printans()
{
	printf("%lld\n",f[n][cur]);
}

int main()
{
    init();
	dp();
    printans();
    return 0;   
} 

