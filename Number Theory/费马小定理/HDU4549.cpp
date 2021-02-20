#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll MOD=1000000007;
int a,b,n;

void mul(ll A[][2],ll B[][2])
{
	ll C[2][2];
	memset(C,0,sizeof(C));
	for (int i=0;i<2;i++)
		for (int j=0;j<2;j++)
			for (int k=0;k<2;k++) 
				C[i][j]=(C[i][j]+A[i][k]*B[k][j])%(MOD-1);
	for (int i=0;i<2;i++)
		for (int j=0;j<2;j++) B[i][j]=C[i][j];
}

void fibonacci(ll &fa,ll &fb)
{
	ll acc[2][2]={{1,1},{1,0}};
	ll now[2][2]={{1,0},{0,1}};
	int res=n-1;
	while (res>0)
	{
		if (res&1) mul(acc,now);
		mul(acc,acc);
		res>>=1;
	}
	fa=now[0][1];
	fb=now[0][0];
}

ll get_ans(ll x,ll p)
{
	ll now=x;
	ll res=p;
	ll ret=1;
	while (res>0)
	{
		if (res&1!=0) ret=(ret*now)%MOD;
		now=(now*now)%MOD;
		res>>=1;
	}
	return ret;
}

int main()
{
	while (~scanf("%d%d%d",&a,&b,&n))
	{
		if (n==0) cout<<a<<endl;
		else if (n==1) cout<<b<<endl;
		else
		{
			ll fa=0,fb=0;
			fibonacci(fa,fb);
			printf("%lld\n",(get_ans(a,fa)*get_ans(b,fb))%MOD); 
		}
	}
	return 0;
}
