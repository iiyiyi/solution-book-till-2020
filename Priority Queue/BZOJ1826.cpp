#include<bits/stdc++.h>
using namespace std;
const int MAXN=110000;
typedef pair<int,int> p;
const int INF=0x7fffffff;
int n,m,a[MAXN],d,hash[MAXN];
int rcap[MAXN],nap[MAXN];//recently appear & next appear
priority_queue<p> que;
int inque[MAXN],qsize;

void init()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]),hash[i]=a[i];
	sort(hash+1,hash+n+1);
	d=unique(hash+1,hash+n+1)-(hash+1);
	for (int i=1;i<=n;i++) a[i]=lower_bound(hash+1,hash+d+1,a[i])-hash;
	for (int i=1;i<=n;i++) rcap[i]=nap[i]=INF;
	for (int i=1;i<=n;i++)
	{
		if (rcap[a[i]]!=INF) nap[rcap[a[i]]]=i;
		rcap[a[i]]=i;
	}
} 

void solve()
{
	int ans=0;
	memset(inque,0,sizeof(inque));
	qsize=0;
	for (int i=1;i<=n;i++)
	{
		if (!inque[a[i]])
		{
			if (qsize==m) //这里不能用que.size()代替，因为相同元素可能都在优先队列里呢 
			{
				inque[que.top().second]=0;
				que.pop();
				qsize--;
			}
			inque[a[i]]=1;
			ans++;
			qsize++;
		}
		que.push(p(nap[i],a[i]));
	}
	printf("%d\n",ans);
}

int main()
{
	init();
	solve();
	return 0;
}
