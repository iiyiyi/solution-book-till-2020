#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define mod 31011
using namespace std;
const int MAXN=1000+50;
struct node
{
	int fr,to,len;
	bool operator < (const node &x) const
	{
		return len<x.len;
	}
}edge[MAXN];
int num[MAXN],numss=-1,nstart[MAXN],nend[MAXN];//num[i]长度排序为i的边长需要取多少个,nstart/nend表示长度排序为i的边长排序为几到几 
int n,m,pa[MAXN],tot=0,ans,tmpans; 
int find(int x){return (pa[x]==x?x:find(pa[x]));}

void dfs(int now,int r,int total,int num)
{
	if (num>total) return;
	if (now>r)
	{
		if (num==total) tmpans++;
		return;	
	}
	int u=edge[now].fr,v=edge[now].to;
	int fa=find(u),fb=find(v);
	if (fa!=fb)
	{
		pa[fa]=fb;
		dfs(now+1,r,total,num+1);
		pa[fa]=fa;
	} 
	dfs(now+1,r,total,num);
}

void init()
{
	scanf("%d%d",&n,&m);
	for (int i=0;i<m;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		edge[i]=(node){a,b,c};
	}
	sort(edge,edge+m);
}

void kruskal()
{
	memset(num,0,sizeof(num));
	for (int i=1;i<=n;i++) pa[i]=i;
	for (int i=0;i<m;i++)
	{
		if (i==0 || edge[i].len!=edge[i-1].len)
		{
			if (i!=1) nend[numss]=i-1;
			nstart[++numss]=i;
		}
		int fa=find(edge[i].fr),fb=find(edge[i].to);
		if (fa!=fb)
		{
			pa[fa]=fb;
			num[numss]++;
			tot++;
		} 
	}
	nend[numss]=m-1;
}

void solve()
{
	if (tot<n-1) puts("0");
	else
	{
		ans=1;
		for (int i=1;i<=n;i++) pa[i]=i;
		for (int i=0;i<=numss;i++) 
		{
			tmpans=0;
			dfs(nstart[i],nend[i],num[i],0);
			ans=(ans*tmpans)%mod;
			for (int j=nstart[i];j<=nend[i];j++)
			{
				int u=edge[j].fr,v=edge[j].to;
				int fa=find(u),fb=find(v);
				if (fa!=fb) pa[fa]=fb;
			} 
		}
		printf("%d",ans);
	}
}

int main()
{
	freopen("bzoj_1016.in","r",stdin);
	freopen("bzoj_1016.out","w",stdout);
	init();
	kruskal();
	solve();
	return 0;	
} 
