#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define MOD 1000000007
using namespace std;
typedef long long ll;
const int MAXN=1000000+5;
struct node
{
	ll uni,ord;//uni表示a≠1，ord表示a=1 
}n,m;
ll a,b,c,d;

ll quick(ll x,ll p)
{
	ll res=p,retu=1,now=x;
	while (res>0)
	{
		if (res&1) retu=(retu*now) % MOD;
		now=(now*now) % MOD;
		res>>=1;
	}
	return retu;
}

ll ni(ll x)
{
	return quick(x,MOD-2);
}

node get_value(char str[])
{
	int len=strlen(str);
	node ret=(node){0,0}; 
	for (int i=0;i<len;i++)
	{
		ret.uni=((ret.uni*10)%(MOD-1)+str[i]-'0')%(MOD-1);
		ret.ord=((ret.ord*10)%MOD+str[i]-'0')%MOD;
	}
	return ret;
} 

void init()
{
	char strm[MAXN],strn[MAXN];
	scanf("%s%s",strn,strm);
	n=get_value(strn);
	m=get_value(strm);
	scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
}

void get_ans()
{
	ll f;//=f[n+1][1]
	if (a==1)
	{
		ll D=((((c*(m.ord-1))%MOD)*b)%MOD+d)%MOD;
		if (c==1) f=(1+n.ord*D)%MOD;
			else
			{
				ll cn=quick(c,n.uni);
				f=(cn+(D*(cn-1)*ni(c-1)%MOD))%MOD; 
			} 
	}
	if (a!=1)
	{
		ll am=quick(a,m.uni-1);
		ll A=(am*c)%MOD;
		ll B=(((((b*c)%MOD*(am-1))%MOD*ni(a-1)))%MOD+d)%MOD;
		ll An=quick(A,n.uni);
		f=An+((B*(An-1)%MOD)*ni(A-1))%MOD;
	}
	printf("%lld",((f-d)*ni(c)%MOD+MOD)%MOD); 
}

int main()
{
	init();
	get_ans();
	return 0;
} 
