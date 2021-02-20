#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define lson l,m
#define rson m+1,r
using namespace std;
const int MAXN=60000+50;//注意要开60000，原来50000个数加修改操作中可能另外出现的10000个数
int n,q,tot,m,d;
struct node
{
	int l,r,k,Q;
}op[MAXN];
int a[MAXN<<2],hash[MAXN<<2],T[MAXN<<2],S[MAXN<<2],use[MAXN<<2];
int L[MAXN<<5],R[MAXN<<5],sum[MAXN<<5];

int lowbit(int x)
{
	return (x&(-x));
}

int build(int l,int r)
{
	int rt=++tot;
	sum[rt]=0;
	if (l!=r)
	{
		int m=(l+r)>>1;
		L[rt]=build(lson);
		R[rt]=build(rson);
	}
	return rt;
}

int update(int pre,int l,int r,int x,int op)
{
	int rt=++tot;
	L[rt]=L[pre],R[rt]=R[pre],sum[rt]=sum[pre]+op;
	if (l<r)
	{
		int m=(l+r)>>1;
		if (x<=m) L[rt]=update(L[pre],lson,x,op);
			else R[rt]=update(R[pre],rson,x,op); 
	} 
	return rt;
}

int Sum(int x)
{
	int ret=0;
	while (x>0)
	{
		ret+=sum[L[use[x]]];
		x-=lowbit(x);
	}
	return ret;
}

int query(int Sl,int Sr,int Tl,int Tr,int l,int r,int k)
{
	if (l==r) return l;
	int m=(l+r)>>1;
	int tmp=Sum(Sr)-Sum(Sl)+sum[L[Tr]]-sum[L[Tl]];
	if (tmp>=k)
	{
		for (int i=Sl;i;i-=lowbit(i)) use[i]=L[use[i]];
		for (int i=Sr;i;i-=lowbit(i)) use[i]=L[use[i]];
		return query(Sl,Sr,L[Tl],L[Tr],lson,k);
	}
	else
	{
		for (int i=Sl;i;i-=lowbit(i)) use[i]=R[use[i]];
		for (int i=Sr;i;i-=lowbit(i)) use[i]=R[use[i]];
		return query(Sl,Sr,R[Tl],R[Tr],rson,k-tmp);
	}
} 

void modify(int x,int p,int delta)
{
	while (x<=n)
	{
		S[x]=update(S[x],1,d,p,delta);
		x+=lowbit(x);
	}
}

void init()
{
	tot=0;
	m=0;
	d=0;
	scanf("%d%d",&n,&q);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]),hash[++m]=a[i];
	for (int i=0;i<q;i++)
	{
		char s[10];
		scanf("%s",s);
		if (s[0]=='Q')	scanf("%d%d%d",&op[i].l,&op[i].r,&op[i].k),op[i].Q=1;
			else 
			{
				scanf("%d%d",&op[i].l,&op[i].r);
				op[i].Q=0;
				hash[++m]=op[i].r;
			}
	}
	/*因为修改后的数可能不在初始几个数的范围内，故要先输入完查询*/ 
	
	sort(hash+1,hash+m+1);
	d=unique(hash+1,hash+1+m)-hash-1;
	
	T[0]=build(1,d);//T表示每一步T树的树根
	for (int i=1;i<=n;i++)
	{
		int x=lower_bound(hash+1,hash+d+1,a[i])-hash;
		T[i]=update(T[i-1],1,d,x,1);
	}
	
	for (int i=1;i<=n;i++) S[i]=T[0];
}

void solve()
{
	//不要忘记了离散化之后的范围上界为d而不是m 
	for (int i=0;i<q;i++)
	{
		if (op[i].Q)
		{
			for (int j=op[i].l-1;j;j-=lowbit(j)) use[j]=S[j];
			for (int j=op[i].r;j;j-=lowbit(j)) use[j]=S[j];
			int ans=query(op[i].l-1,op[i].r,T[op[i].l-1],T[op[i].r],1,d,op[i].k);
			printf("%d\n",hash[ans]);
		}
		else
		{
			int x=lower_bound(hash+1,hash+d+1,a[op[i].l])-hash;
			int y=lower_bound(hash+1,hash+d+1,op[i].r)-hash;
			modify(op[i].l,x,-1);
			modify(op[i].l,y,1);
			a[op[i].l] =op[i].r;
		}
	}
}

int main()
{
	freopen("dynrank.in","r",stdin);
	freopen("dynrank.out","w",stdout);
	int T;
	scanf("%d",&T);
	while (T--)
	{
		init();
		solve();
	}
	return 0;
}
