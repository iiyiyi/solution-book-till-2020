#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<complex>
#define pi acos(-1)
using namespace std;
typedef complex<double> com;
typedef long long ll;
const int MAXN=270000;
double q[MAXN];
com a[MAXN],b[MAXN],c[MAXN],e1[MAXN],e2[MAXN];
int m,n,tmpn,L,Rev[MAXN];
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
	scanf("%d",&n);
	tmpn=n;
	for (int i=0;i<n;i++) scanf("%lf",&q[i]);
	for (int i=0;i<n;i++) a[i]=(q[i]),c[i]=(q[n-1-i]);
	for(int i=1;i<n;i++) b[i]=(1.0/i/i);
	//b仅仅和差有关，还是和下标志一一对应的，不要写成1.0/(i+1)/(i+1) 
}

void solve()
{
    m=n<<1;//相乘后的位数是原来的2倍 
    get_bit();
    get_Rtable();
    FFT(a,1);
    FFT(b,1);
    FFT(c,1);
    multi(a,b);
    multi(c,b);
    FFT(a,-1);
    FFT(c,-1);
    for (int i=0;i<tmpn;i++) printf("%.3f\n",a[i].real()-c[tmpn-i-1].real());//不要忘了最后还要把c颠倒回来 
}

int main()
{
	init();
	solve();
}
