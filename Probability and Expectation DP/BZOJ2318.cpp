#include<iostream> 
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=1000+5;
double f[MAXN],g[MAXN],p,q;

void solve()
{
	int n;
	scanf("%d",&n);
	n=min(n,1000);
	//由于n很大的时候，概率几乎不再发生改变，则只需要取和1000中较小的即可 
    scanf("%lf%lf",&p,&q); 
    f[0]=0,g[0]=1;
    for(int i=1;i<=n;i++)
    {
        if(f[i-1]>g[i-1])p=1-p,q=1-q;
        //这里p和q表示的含义与题意不同，含义为当前投掷出正面朝上情况的概率
		//如果还剩i-1个石头时，A先手更有利，则在还是i个石头的时候，A希望B拿掉当前石头，B也希望A拿掉，故均希望反面向上。
		//这种情况下，正面朝上的概率就是1-p/1-q 
		//如果还剩i-1个石头时，A后手更有利，则两个人都希望自己能选，正面朝上的概率就是p/q 
        f[i]=(p*g[i-1]+(1-p)*q*f[i-1])/(1-(1-p)*(1-q));
        g[i]=(q*f[i-1]+(1-q)*p*g[i-1])/(1-(1-p)*(1-q));
        if(f[i-1]>g[i-1])p=1-p,q=1-q;
    }
	printf("%.6lf\n",f[n]);
}

int main()
{
	int T;
    scanf("%d",&T);
    while (T--) solve();
    return 0;
}
