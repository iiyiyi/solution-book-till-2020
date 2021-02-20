#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAXN=20000+50;
int n;
int a[5*MAXN],b[5*MAXN],e[5*MAXN],f[5*MAXN];
//f[i]表示以a[i]为末尾的最长公共子串，这样就可以避免讨论交叉 
int pos[MAXN][6];
int ans=0;

int lowbit(int x) 
{
	return (x&(-x));
}

int query(int x)
{
	int ret=0;//这里初值必须设为0而不是-1 
	while (x>0) ret=max(ret,e[x]),x-=lowbit(x);
	return ret;
}

void update(int x,int delta)
{
	while (x<=5*n) e[x]=max(e[x],delta),x+=lowbit(x);
} 

void init()
{
	memset(e,0,sizeof(e));
	memset(f,0,sizeof(f));
	memset(a,0,sizeof(a));
	scanf("%d",&n);
	for (int i=1;i<=5*n;i++) 
	{
		scanf("%d",&a[i]);
		pos[a[i]][++pos[a[i]][0]]=i;
	}
	for (int i=1;i<=5*n;i++) scanf("%d",&b[i]); 
}

void dp()
{
	for (int i=1;i<=5*n;i++)
		for (int j=5;j>=1;j--)//这里一定要从后往前 
		{
			int nowp=pos[b[i]][j];
			f[nowp]=max(f[nowp],query(nowp-1)+1);
			update(nowp,f[nowp]);
			ans=max(ans,f[nowp]);
		}
	printf("%d\n",ans);
}

int main()
{
	init();
	dp();
	return 0;	
} 
