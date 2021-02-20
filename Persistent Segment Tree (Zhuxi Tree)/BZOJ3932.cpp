//时刻->下标
//优先级->数值 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector> 
#define lson l,m
#define rson m+1,r
using namespace std;
const int MAXN=100000+50;
typedef long long ll;
struct node
{
	int time,p,delta;

}a[MAXN*2];
bool cmp(node x,node y)
{
	return (x.time<y.time);
}
int m,n,tot,d;
int hash[MAXN],T[MAXN],size[MAXN<<7],L[MAXN<<7],R[MAXN<<7];
ll sum[MAXN<<7];

int build(int l,int r)
{
	int rt=++tot;
	sum[rt]=size[rt]=0;
	if (l<r)
	{
		int m=(l+r)>>1;
		L[rt]=build(lson);
		R[rt]=build(rson);
	}
	return rt;
}

int update(int pre,int l,int r,int x,int delta)
{
	int rt=++tot;
	L[rt]=L[pre],R[rt]=R[pre]; 
	sum[rt]=sum[pre]+(ll)delta*hash[x]; // sum  优先级的和：例如两个优先级为3的人物，那么sum=6,而size=2 
	size[rt]=size[pre]+delta;			// size 优先级个数的和：例如两个优先级为3的人物，那么sum=6,而size=2 
	if (l!=r)
	{
		int m=(l+r)>>1;
		if (x<=m) L[rt]=update(L[rt],lson,x,delta);
			else R[rt]=update(R[rt],rson,x,delta);
	}
	return rt;
}


ll query(int rt,int l,int r,ll k)
{
	int nowsize=size[rt];
	if (k>=nowsize) return (sum[rt]);
	if (l==r) return (sum[rt]/size[rt]*k);
	//当l==r时，当前值可能有多个，且总数大于k，所以只需返回k*当前值即可 
    int num=size[L[rt]];
    ll ret;
    int m=(l+r)>>1;
    if(num>=k)
        ret=query(L[rt], lson, k);
    else
        ret=sum[L[rt]]+query(R[rt],rson, k-num);
    return ret;
}

void init()
{
	tot=0;
	scanf("%d%d",&m,&n);
	for (int i=1;i<=m;i++)
	{
		int s,e,p;
		scanf("%d%d%d",&s,&e,&p);
		a[2*i-1]=(node){s,p,1};
		a[2*i]=(node){e+1,p,-1};
		hash[i]=p;
	}
	sort(hash+1,hash+m+1);
	m=m*2;
	sort(a+1,a+m+1,cmp);
	
	d=unique(hash+1,hash+(m>>1)+1)-(hash+1);
	T[0]=build(1,d);
	for (int i=1;i<=m;i++)
	{
		int x=lower_bound(hash+1,hash+d+1,a[i].p)-hash;
		int t=a[i].time;
		if (i==1 || t!=a[i-1].time)
		{
			if (i!=1) for (int j=a[i-1].time+1;j<t;j++) T[j]=T[j-1];
			T[t]=update(T[t-1],1,d,x,a[i].delta);
		}
		else T[t]=update(T[t],1,d,x,a[i].delta);
	}
}

void solve()
{
	int pre=1;
	for (int i=0;i<n;i++)
    {
        ll x,a,b,c;
        scanf("%lld%lld%lld%lld",&x,&a,&b,&c);
        ll k=1+(ll)(a*pre+b)%c;
        ll ans=query(T[x],1,d,k); 
        printf("%lld\n",ans);
        pre=ans;
    }
}

int main()
{
	//freopen("cqoi15_query.in","r",stdin);
	//freopen("cqoi15_query.out","w",stdout);
	init();
	solve(); 
	return 0;
} 

