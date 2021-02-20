#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<complex>
#include<cmath>
#define pi acos(-1)
using namespace std;
const int MAXN=524288+50;
const int MOD=1000000007;
typedef complex<double> com;
typedef long long ll;
com a[MAXN],b[MAXN],c[MAXN];
int ina[MAXN],inb[MAXN],f[MAXN],p[MAXN],Rev[MAXN],m,n,L;
char s[MAXN],str[MAXN];
void get_bit(){for (n=1,L=0;n<m;n<<=1) L++;}
void get_Rev(){for (int i=0;i<n;i++) Rev[i]=(Rev[i>>1]>>1)|((i&1)<<(L-1));}

void FFT(com* a,int flag)
{
    for (int i=0;i<n;i++)if(i<Rev[i])swap(a[i],a[Rev[i]]);
    for (int i=1;i<n;i<<=1)
    {
        com wn(cos(pi/i),flag*sin(pi/i));
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

int manacher()
{
	str[0]='$';
	str[1]='#';
	for (int i=0,j=1;s[i+1];i++)
	{
		str[++j]=s[i+1]; 
		str[++j]='#';
	}
	int mx=0,mxid=0,ret=0;
	memset(p,0,sizeof(p));
	for (int i=1;str[i];i++)
	{
		if (mx>i) p[i]=(p[2*mxid-i]<(mx-i)?p[2*mxid-i]:(mx-i));
			else p[i]=1;
		while(str[i-p[i]]==str[i+p[i]]) p[i]++;
		if (i+p[i]>mx)
		{
			mx=i+p[i];
			mxid=i;
		}
		cout<<p[i]<<endl;
		ret=(ret+p[i]/2)%MOD;
		//注意+的优先级比>>高，所以不能写ret+p[i]>>1 
	}
	//注意我们要求的不是最长回文字串而是回文串的个数,和之前的manacher有细微不同 
	cout<<ret<<endl;
	return ret;
}

void init()
{
	scanf("%s",s+1);
	memset(ina,0,sizeof(ina));
	memset(inb,0,sizeof(inb));
	n=strlen(s+1);
	for (int i=1;i<=n;i++)
		if (s[i]=='a') ina[i]++;
			else if (s[i]=='b') inb[i]++;
	for (int i=1;i<=n;i++) a[i]=(ina[i]),b[i]=(inb[i]);
}

void solve()
{
	m=n<<1;
	get_bit();
	get_Rev();
	FFT(a,1);
	FFT(b,1);
	for (int i=0;i<n;i++) c[i]=a[i]*a[i]+b[i]*b[i];
	FFT(c,-1);
	int pow[MAXN];
	ll ans=0;
	pow[0]=1;
	for (int i=1;i<MAXN;i++) pow[i]=(pow[i-1]*2)%MOD;
	for (int i=0;i<n;i++)
	{
		int tmp=int(c[i].real()+0.5);
		ans=(ans+(ll)pow[(tmp+1)>>1]-1)%MOD;
	}
	printf("%d",(((int)ans+MOD-manacher())%MOD));
}

int main()
{
	init();
	solve();
	return 0;
}
