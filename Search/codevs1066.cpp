#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=500+50;
struct node
{
	int l,r;
	bool operator < (const node&x) const
	{
		return l<x.l;
	}
}arriv[MAXN];
int m,n,h[MAXN][MAXN],vis[MAXN][MAXN];
int f[MAXN],cover[MAXN];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};

void init()
{
	scanf("%d%d",&m,&n);
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++) scanf("%d",&h[i][j]); 
}

void dfs(int x,int y,int fr)
{
	vis[x][y]=fr;
	if (x==m)
	{
		arriv[fr].l=min(arriv[fr].l,y);
		arriv[fr].r=max(arriv[fr].r,y);
		cover[y]=1;
	}
	for (int i=0;i<4;i++)
	{
		int xx=x+dx[i],yy=y+dy[i];
		if (xx<=0 || xx>m || yy<=0 || yy>n) continue;
		if (h[xx][yy]<h[x][y] && vis[xx][yy]!=fr) dfs(xx,yy,fr);
	}
}

void solve()
{
	memset(cover,0,sizeof(cover));
	memset(vis,0,sizeof(vis));
	for (int i=1;i<=n;i++) 
	{
		arriv[i].l=MAXN,arriv[i].r=-1;
		dfs(1,i,i);
	}
	
	int flag=1,rem=0;
	for (int i=1;i<=n;i++) if (!cover[i]){flag=0;rem++;}
	
	if (flag)
	{
		puts("1");
		sort(arriv+1,arriv+n+1); 
		for (int i=1;i<=n;i++) f[i]=MAXN;
		f[0]=0;
		for (int i=1;i<=n;i++)
		{
			int l=arriv[i].l,r=arriv[i].r;
			for (int j=l-1;j<=r;j++) f[r]=min(f[r],f[j]+1);
		}
		printf("%d",f[n]);
	} 
	else printf("0\n%d",rem);
}

int main()
{
	init();
	solve();
	return 0;
} 
