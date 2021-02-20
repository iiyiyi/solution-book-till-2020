#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
const int MAXN=20000+50;
const int MAXM=100000+50;
struct Edge
{
	int u,v;
}edge[MAXM];
int n,m,k;
int vis[MAXM];
int L,R; 
int fa[MAXN],h[MAXN]; 
vector<int> mustchoose;

void initset(){for (int i=1;i<=n;i++) fa[i]=i,h[i]=1;}

int find(int x)
{
	int r=x;
	while (fa[r]!=r) r=fa[r];
	while (fa[x]!=r)
	{
		int tmp=fa[x];
		fa[x]=r;
		x=fa[x];
	}
	return r;
}

void unionset(int a,int b)
{
	if (h[a]>=h[b])
	{
		fa[b]=a;
		if (h[a]==h[b]) h[a]++;
	}
	else fa[a]=b;
}

void init()
{
	scanf("%d%d%d",&n,&m,&k);
	L=0,R=m+1;
	for (int i=1;i<=m;i++) 
	{
		int u,v,c;
		scanf("%d%d%d",&u,&v,&c);
		if (c) edge[++L]=(Edge){u,v};
			else edge[--R]=(Edge){u,v};
	}
}

void solve()
{
	int t=0; 
	initset();
	for (int i=1;i<=m;i++)
	{
		int fa=find(edge[i].u),fb=find(edge[i].v);
		if (fa!=fb)
		{
			unionset(fa,fb);
			if (i>=R)
			{
				vis[i]=1;
				t++;
				mustchoose.push_back(i);
			}
		}
	}
	if (t>k)
	{
		puts("no solution");
		return;
	}
	// 找出必须要选择的鹅卵石路 
	
	initset();
	for (int i=0;i<mustchoose.size();i++)
	{
		int fa=find(edge[mustchoose[i]].u),fb=find(edge[mustchoose[i]].v);
		unionset(fa,fb);		
	}
	for (int i=R;i<=m;i++)
		if (t<k && !vis[i])
		{
			int fa=find(edge[i].u),fb=find(edge[i].v);
			if (fa!=fb)
			{
				unionset(fa,fb);
				vis[i]=1;
				t++;
			}
		}
	if (t<k)
	{
		puts("no solution");
		return;
	}
	//先选择必须要的鹅卵石路，然后再用其他鹅卵石路填充
	
	for (int i=1;i<=L;i++)
	{
		int fa=find(edge[i].u),fb=find(edge[i].v);
		if (fa!=fb)
		{
			unionset(fa,fb);
			vis[i]=1;
		}
	} 
	for (int i=1;i<=L;i++) if (vis[i]) printf("%d %d %d\n",edge[i].u,edge[i].v,1);
	for (int i=R;i<=m;i++) if (vis[i]) printf("%d %d %d\n",edge[i].u,edge[i].v,0);
}

int main()
{
	init();
	solve();
} 
