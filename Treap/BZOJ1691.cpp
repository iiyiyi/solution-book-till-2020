#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int MAXN=100000+50;
const int INF=0x7fffffff;
struct node
{
	int fresh,price;
	bool operator < (const node &x) const
	{
		return (fresh>x.fresh);//注意是由大到小排序 
	}
}cow[MAXN],grass[MAXN];
struct treap
{
	int key,cnt,priority;
	treap* lson;
	treap* rson;
	treap()
	{
		cnt=1;
		priority=rand();
		lson=rson=NULL;
	}
};
treap* root=NULL;
int n,m;

void RightRotate(treap* &rt)
{
    treap* tmp=rt->lson;
    rt->lson=tmp->rson;
    tmp->rson=rt;
    rt=tmp;
}

void LeftRotate(treap* &rt)
{
    treap* tmp=rt->rson;
    rt->rson=tmp->lson;
    tmp->lson=rt;
    rt=tmp;
}

void insert(treap* &rt,int x)
{
	if (rt==NULL) 
	{
		rt=new treap;//不要忘记了新建 
		rt->key=x;
	} 
	else if (rt->key==x) rt->cnt++;
	else
	{
		if (rt->key>x)
		{
			insert(rt->lson,x);
			if (rt->lson->priority>rt->priority) RightRotate(rt);
		}
		if (rt->key<x)
		{
			insert(rt->rson,x);
			if (rt->rson->priority>rt->priority) LeftRotate(rt);
		}
	}
}

void del(treap* &rt,int x)
{
	if (rt->key==x)
	{
		if (rt->cnt>1) rt->cnt--;
			else
			{
				treap* tmp=rt;
				if (rt->lson==NULL)
				{
					rt=rt->rson;
					delete tmp;
				}
				else if (rt->rson==NULL)
				{
					rt=rt->lson;
					delete tmp;
				}
				else
				{
					if (rt->lson->priority>rt->rson->priority) RightRotate(rt),del(rt->rson,x);
						else LeftRotate(rt),del(rt->lson,x);
				}
			}
	}
	else
	{
		if (x<rt->key) del(rt->lson,x);
			else del(rt->rson,x);
	}
}

int suc(treap* &rt,int x)
{
	int ans=INF;
	treap* tmp=rt;
	while (tmp)
	{
		if (tmp->key>x)
		{
			ans=min(ans,tmp->key);
			tmp=tmp->lson;
		}
		else tmp=tmp->rson;
	}
	return ans;
}

void init()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d%d",&cow[i].price,&cow[i].fresh);
	for (int i=1;i<=m;i++) scanf("%d%d",&grass[i].price,&grass[i].fresh);
	sort(cow+1,cow+n+1);
	sort(grass+1,grass+m+1);
}

ll solve()
{
	int j=1;
	ll ans=0;
	for (int i=1;i<=n;i++)
	{
		while (grass[j].fresh>=cow[i].fresh && j<=m)
		{
			insert(root,grass[j].price);//这里一开始把j打成i了 
			j++;
		}
		int find=suc(root,cow[i].price-1);//注意由于这里是不低于，也就是≥，并不是取cow[i].price的后继，而是cow[i].price-1的 
		if (find==INF) return(-1);
			else
			{
				ans+=(ll)find;
				del(root,find);
			}
	}
	return ans;
}

int main()
{
	init();
	printf("%lld",solve());
	return 0;
} 
