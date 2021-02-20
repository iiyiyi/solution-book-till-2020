#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<complex>
#include<cmath>
#define pi acos(-1)
using namespace std;
const int MAXN=131072;
typedef complex<double> com;
int n,m,L;
com a[MAXN],b[MAXN];
int c[MAXN],Rev[MAXN]; 

void get_bit(){for (n=1,L=0;n<m;n<<=1) L++;} 
void get_Rtable(){for (int i=0;i<n;i++) Rev[i]=(Rev[i>>1]>>1)|((i&1)<<(L-1));}
void multi(com* a,com* b){for (int i=0;i<n;i++) a[i]*=b[i];}

void FFT(com* a,int flag)
{
	for (int i=0;i<n;i++)if(i<Rev[i])swap(a[i],a[Rev[i]]); //利用逆序表，快速求逆序
	for (int i=1;i<n;i<<=1)
	{
		com wn(cos(2*pi/(i*2)),flag*sin(2*pi/(i*2)));
		for (int j=0;j<n;j+=(i<<1))
		{
			com w(1,0);
			for (int k=0;k<i;k++,w*=wn)
			{
				com x=a[j+k],y=w*a[j+k+i];
				a[j+k]=x+y;
				a[j+k+i]=x-y;
			}
		}
	}
	if (flag==-1) for (int i=0;i<n;i++) a[i]/=n;
}

void init()
{
	char str[MAXN];
	scanf("%d",&n);
	scanf("%s",str);
	for (int i=0;i<n;i++) a[i]=str[n-1-i]-'0';
	scanf("%s",str);
	for (int i=0;i<n;i++) b[i]=str[n-1-i]-'0';
}

void solve()
{
	m=n<<1;//相乘后的位数是原来的2倍 
	get_bit();
	get_Rtable();//求逆序表：末位为0，直接为其前一半逆序表的值右移一位，末位为1，在最高位添加1
	FFT(a,1),FFT(b,1);//分别将a与b的系数表达式转为点值表达式
	multi(a,b);//点值表达式相乘
	FFT(a,-1);//将相乘后的点值表达式转为系数表达式
	
}

void print()
{	
	for(int i=0;i<m;i++) c[i]=(int)(a[i].real()+0.5);
	for (;c[m-1]==0;m--); //把前置的0清空 
	for (int i=0;i<m;i++)
	{
		if (c[i]>=10)
		{
			c[i+1]+=c[i]/10;
			c[i]%=10;
			if (i==m-1) m++;
		}
	}
	for (int i=m-1;i>=0;i--) printf("%d",c[i]);
}

int main()
{
	init();
	solve();
	print();
	return 0;
} 
