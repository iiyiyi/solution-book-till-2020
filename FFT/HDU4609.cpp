#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<complex>
#include<cmath>
#define pi acos(-1)
using namespace std;
const int MAXN = 400040;
typedef complex<double> com;
typedef long long ll;
int n,m,L,tmpn;
com a[MAXN],b[MAXN];
int c[MAXN],Rev[MAXN],l[MAXN],len; 
ll sum[MAXN],num[MAXN];//把sum和num放在子程序里就会错误，放进主程序就可以，为什么？？ 

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
	int tmp[MAXN/4];
    scanf("%d",&n);
    tmpn=n;
    memset(tmp,0,sizeof(tmp));
	memset(Rev,0,sizeof(Rev));
	len=-1;
	for (int i=0;i<n;i++)
    {
    	scanf("%d",&l[i]);
    	if (len<l[i]) len=l[i];
    	tmp[l[i]]++;
	} 
	for (int i=0;i<MAXN;i++) a[i]=b[i]=(0);
	for (int i=1;i<=len;i++) a[i]=(tmp[i]);
}

void solve()
{
    m=len<<1;
    len++;m++;
    get_bit();
    get_Rtable();
    FFT(a,1);
    for (int i=0;i<n;i++) b[i]=a[i];
    multi(a,b);
    FFT(a,-1);
}

void get_ans()
{    
	memset(sum,0,sizeof(sum));
	memset(num,0,sizeof(num));
	for (int i=1;i<m;i++) num[i]=(ll)(a[i].real()+0.5);
	//减掉取两个相同的组合
    for(int i =0;i<tmpn;i++)
    {
        num[l[i]+l[i]]--;
	}	
    for (int i=1;i<m;i++) num[i]/=2;
	sum[0]=0;
	
	for (int i=1;i<m;i++) sum[i]=sum[i-1]+num[i];
	
	ll cnt=0;
	n=tmpn;
    for (int i=0;i<n;i++)
    {
        cnt+=sum[m-1]-sum[l[i]];
        //减掉一个取大，一个取小的
        cnt-= (ll)(n-1-i)*i;
    	//减掉一个取本身，另外一个取其它
    	cnt-= (n-1);
    	//减掉大于它的取两个的组合
        cnt-= (ll)(n-1-i)*(n-i-2)/2;
    }
    ll tot = (ll)n*(n-1)*(n-2)/6;
	printf("%.7lf\n",(double)cnt/tot);

}

int main()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
    	init();
   		solve();
    	get_ans();
    }
    return 0;
}
