#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<complex>
#include<cmath>
#define pi acos(-1)
using namespace std;
typedef complex<double> com;
typedef long long ll;
const int MAXN=262144+50;
com a[MAXN],b[MAXN],c[MAXN];
int m,n,len,L,Rev[MAXN];
void get_bit(){for (n=1,L=0;n<m;n<<=1) L++;} 
void get_Rtable(){for (int i=0;i<n;i++) Rev[i]=(Rev[i>>1]>>1)|((i&1)<<(L-1));}

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
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		int ai;
		scanf("%d",&ai);
		a[ai]+=(1);b[2*ai]+=(1);c[3*ai]+=(1);
		len=max(len,3*ai);
	}
}

void solve()
{
	m=len<<1;
	len++;m++;
	get_bit();
	get_Rtable();
	FFT(a,1);
	FFT(b,1);
	FFT(c,1);
	com t2=(2),t3=(3),t6=(6);
	for (int i=0;i<n;i++) 
	   a[i]=(a[i]*a[i]*a[i]-t3*a[i]*b[i]+t2*c[i])/t6+(a[i]*a[i]-b[i])/t2+a[i];
	FFT(a,-1);
}

void get_ans()
{
	for (int i=1;i<m;i++) 
	{
		ll num=(ll)(a[i].real()+0.5);
		if (num!=0) printf("%d %d\n",i,num);
	}
}

int main()
{
	init();
	solve();
	get_ans();
	return 0;
}
