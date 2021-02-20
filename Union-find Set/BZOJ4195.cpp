#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector> 
using namespace std;
const int MAXN=2000000+500;
struct node
{
	int num;
	int oripos;
	int ab;//0a1b
	bool operator < (const node &x) const
	{
		return num<x.num;
	}
}que[MAXN];
int h[MAXN],u[MAXN];
int n,a[MAXN],b[MAXN],e[MAXN];

void union_set(int a,int b)
{
	if (h[a]>=h[b])
	{
		u[b]=a;
		if (h[a]==h[b]) h[a]++;
	}
	else u[a]=b;
}

int find(int x)
{
	int r=x;
	while (u[r]!=r) r=u[r];
	int p=x;
	while (u[p]!=p)
	{
		int tmp=u[p];
		u[p]=r;
		p=tmp;
	}
	return r;
}


void init()
{
	scanf("%d",&n);
	int qlen=-1;
	for (int i=0;i<n;i++)
	{
		scanf("%d%d%d",&a[i],&b[i],&e[i]);
		que[++qlen].num=a[i];
		que[qlen].oripos=i;
		que[qlen].ab=0;
		que[++qlen].num=b[i];
		que[qlen].oripos=i;
		que[qlen].ab=1;
	} 
	sort(que,que+2*n);
	int j=0;
	for (int i=0;i<2*n;i++)
	{
		if (i!=0 && que[i].num!=que[i-1].num) j++;
		if (que[i].ab==0) a[que[i].oripos]=j;
			else b[que[i].oripos]=j;
	}
	memset(h,0,sizeof(h));
	for (int i=0;i<=2*(n+2);i++) u[i]=i;
}

int judge()
{
	for (int i=0;i<n;i++)
		if (e[i]) 
		{
			union_set(find(a[i]),find(b[i]));
		}
	for (int i=0;i<n;i++)
		if (!e[i])
		{
			int fa=find(a[i]),fb=find(b[i]);
			if (fa==fb) return 0;
		}
	return 1;
}

int main()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		init();
		int j=judge();
		if (j) cout<<"YES"<<endl;else cout<<"NO"<<endl;
	}
	return 0;
}

