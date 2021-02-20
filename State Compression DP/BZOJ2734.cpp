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
	int cur=0,before=-1;//beforeָ��һ���м����� 
	for (int i=0;now*(1<<i)<=n;i++)//ö��ÿһ�еĵ�һ����������ܵ����� 
	{
		cur=1-cur;
		int tmp=now*(1<<i),j;
		for (j=0;tmp<=n;j++,tmp*=3);//���ÿһ���м�����
		for (int k=0;k<(1<<j);k++)//ö�ٵ�ǰ�е�״̬ 
		{
			f[cur][k]=0;//����Ҫ�����˳�ʼ��� 
			if (usable[k])
			{
				if (before==-1) {f[cur][k]=1;continue;}//����ǵ�һ�У��򽫿���״̬��Ϊ1 
				for (int p=0;p<(1<<before);p++)
					if (usable[p])
						if ((k&p)==0) f[cur][k]=f[cur][k]+f[1-cur][p],f[cur][k]%=mod;//���ﲻҪ������ҲҪmod 
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
	LL ans=1;//Ϊ�˷�ֹ�˷���ʱ���������������longlong����ת����int 
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
