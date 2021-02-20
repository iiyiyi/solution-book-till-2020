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
	for (int i=0;i<n;i++)if(i<Rev[i])swap(a[i],a[Rev[i]]); //�������������������
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
	m=n<<1;//��˺��λ����ԭ����2�� 
	get_bit();
	get_Rtable();//�������ĩλΪ0��ֱ��Ϊ��ǰһ��������ֵ����һλ��ĩλΪ1�������λ���1
	FFT(a,1),FFT(b,1);//�ֱ�a��b��ϵ�����ʽתΪ��ֵ���ʽ
	multi(a,b);//��ֵ���ʽ���
	FFT(a,-1);//����˺�ĵ�ֵ���ʽתΪϵ�����ʽ
	
}

void print()
{	
	for(int i=0;i<m;i++) c[i]=(int)(a[i].real()+0.5);
	for (;c[m-1]==0;m--); //��ǰ�õ�0��� 
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
