#include<iostream>
#include<cstdio>
#include<cstdlib>
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
#define root 1
using namespace std;
const int MAXN=50000+50;
int n,m;
int lsum[MAXN<<2],rsum[MAXN<<2],msum[MAXN<<2];
int cover[MAXN<<2];//Çø¼ä¸²¸Ç 

void pushdown(int l,int r,int rt)
{
	int mid=(l+r)>>1;
	if (cover[rt]!=-1)
	{
		cover[rt<<1]=cover[rt<<1|1]=cover[rt];
		if (cover[rt]==1)
			lsum[rt<<1]=lsum[rt<<1|1]=rsum[rt<<1]=rsum[rt<<1|1]=msum[rt<<1]=msum[rt<<1|1]=0;
		else
		{
			lsum[rt<<1]=rsum[rt<<1]=msum[rt<<1]=mid-l+1;
			lsum[rt<<1|1]=rsum[rt<<1|1]=msum[rt<<1|1]=r-mid;
		}
		cover[rt]=-1;
	}
}

void pushup(int l,int r,int rt)
{
	int mid=(l+r)>>1;
	lsum[rt]=lsum[rt<<1];
	if (lsum[rt<<1]==(mid-l+1)) lsum[rt]+=lsum[rt<<1|1];
	rsum[rt]=rsum[rt<<1|1];
	if (rsum[rt<<1|1]==(r-mid)) rsum[rt]+=rsum[rt<<1];
	msum[rt]=max(rsum[rt<<1]+lsum[rt<<1|1],max(msum[rt<<1],msum[rt<<1|1]));
}

void update(int L,int R,int c,int l,int r,int rt)
{
	if (L<=l && r<=R)
	{
		msum[rt]=lsum[rt]=rsum[rt]=c? 0:(r-l+1);
		cover[rt]=c;
		return;	
	}
	pushdown(l,r,rt);
	int mid=(l+r)>>1;
	if (L<=mid) update(L,R,c,lson);
	if (mid<R) update(L,R,c,rson);
	pushup(l,r,rt);	
}

int query(int q,int l,int r,int rt)
{
	if (l==r) return l;
	pushdown(l,r,rt);
	int mid=(l+r)>>1;
	if (msum[rt<<1]>=q) return(query(q,lson));
	if (rsum[rt<<1]+lsum[rt<<1|1]>=q) return(mid-rsum[rt<<1]+1);
	return (query(q,rson));
}

void build(int l,int r,int rt)
{
	lsum[rt]=rsum[rt]=msum[rt]=r-l+1;
	cover[rt]=-1;
	if (l==r) return;
	int mid=(l+r)>>1;
	build(lson);
	build(rson);
}

void solve()
{
	build(1,n,1); 
	for (int i=0;i<m;i++)
	{
		int op,d,x;
		scanf("%d",&op);
		if (op==1)
		{
			scanf("%d",&d);
			if (msum[root]<d) puts("0");
			else
			{
				x=query(d,1,n,1);
				printf("%d\n",x);
				update(x,x+d-1,1,1,n,1);
			}
		}
		else 
		{
			scanf("%d%d",&x,&d);
			update(x,x+d-1,0,1,n,1);
		}
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	solve();
	return 0;
}
