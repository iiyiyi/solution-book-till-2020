#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 1000000001
using namespace std;
typedef long long LL;
const int MAXN=12;
int n;
int usable[1<<MAXN],f[2][1<<MAXN];
bool mark[1<<MAXN];

int Usable(int x)
{
	if (x<<1&x || x>>1&x) return 0;else return 1;
}

int dp(int now)
{
	memset(f,0,sizeof(f));
	int cur=0,before=-1;//before指上一行有几个数 
	for (int i=0;now*(1<<i)<=n;i++)//枚举每一行的第一个数，求出总的行数 
	{
		cur=1-cur;
		int tmp=now*(1<<i),j;
		for (j=0;tmp<=n;j++,tmp*=3);//求出每一行有几个数
		for (int k=0;k<(1<<j);k++)//枚举当前行的状态 
		{
			f[cur][k]=0;//【不要忘记了初始化☆】 
			if (usable[k])
			{
				if (before==-1) {f[cur][k]=1;continue;}//如果是第一行，则将可行状态设为1 
				for (int p=0;p<(1<<before);p++)
					if (usable[p])
						if ((k&p)==0) f[cur][k]=f[cur][k]+f[1-cur][p],f[cur][k]%=mod;//这里不要忘记了也要mod 
			}
		}
		before=j;
	}
	int ans=0;
	for (int i=0;i<(1<<before);i++) ans+=f[cur][i],ans%=mod; 
	return (ans);
}

void getusable()
{
	memset(usable,0,sizeof(usable));
	for (int i=0;i<(2<<MAXN);i++)
		if (Usable(i)) usable[i]=1;
}

void solve()
{
	memset(mark,0,sizeof(mark));
	LL ans=1;//为了防止乘法的时候溢出，可以先用longlong，再转换回int 
	for (int i=1;i<=n;i++)
		if ((i%2)&&(i%3)) ans=(ans*dp(i))%mod;
	printf("%d\n",(int)ans);
}

int main()
{
	scanf("%d",&n);
	getusable();
	solve();
	return 0;
}
