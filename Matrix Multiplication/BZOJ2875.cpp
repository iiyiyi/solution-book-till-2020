#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
ll matrix[2][2],ans_matrix[2][2];
ll m,n,a,c,g,x0;

ll ksc(ll a,ll b)
{
	ll ans=0; 
	while (b)
	{
		if (b&1) ans=(ans+a)%m;
		a=(a<<1)%m;
		b>>=1;
	}
	return ans;
}

void ksm(ll n)
{
	ans_matrix[0][0]=ans_matrix[1][1]=1;
	ans_matrix[0][1]=ans_matrix[1][0]=0;
	while (n)
	{
		if (n&1)
		{
			ans_matrix[0][0]=ksc(ans_matrix[0][0],matrix[0][0]);
			ans_matrix[1][0]=(ksc(ans_matrix[1][0],matrix[0][0])+matrix[1][0])%m;
		}
		n>>=1;
		ll tmp1=ksc(matrix[0][0],matrix[0][0]);
		ll tmp2=(ksc(matrix[1][0],matrix[0][0])+matrix[1][0])%m;
		matrix[0][0]=tmp1,matrix[1][0]=tmp2;
	}
}

void init()
{
	scanf("%lld%lld%lld%lld%lld%lld",&m,&a,&c,&x0,&n,&g); 
	matrix[0][0]=a%m,matrix[0][1]=0,matrix[1][0]=c%m,matrix[1][1]=1;
}

void get_ans()
{
	ll ans=(ksc(ans_matrix[0][0],x0)+ans_matrix[1][0])%m;
	ans%=g;
	printf("%lld",ans);
}

int main()
{
	//freopen("randoma.in","r",stdin);
	//freopen("randoma.out","w",stdout);
	init();
	ksm(n);
	get_ans();
	return 0;
} 
