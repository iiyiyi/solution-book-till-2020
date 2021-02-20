#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=5000;
int u[MAXN],h[MAXN],appear[MAXN];
int n,m,gang;

int find(int x)
{
    int r=x,temp;
    while (u[r]!=r) r=u[r];
    while (x!=r)
    {
        temp=u[x];
        u[x]=r;
        x=temp;
    }
    return r;
}

void union_set(int fa,int fb)
{
	if (h[fa]>=h[fb])
	{
		u[fb]=fa;
		if (h[fa]==h[fb]) h[fa]++;
	}
	else u[fa]=fb;
}

void init()
{
	for (int i=1;i<=2*n;i++)
	{
		u[i]=i;
		h[i]=1;
	}
}

void solve()
{
	scanf("%d%d",&n,&m);
	init();
	for (int i=1;i<=m;i++)
	{
		char op[2];
		int u,v;
		scanf("%s%d%d",op,&u,&v);
		if (op[0]=='F')
		{
			int fa=find(u),fb=find(v);
			if (fa!=fb) union_set(fa,fb);
		}
		else
		{
			int fa=find(u),fb=find(v+n);
			if (fa!=fb) union_set(fa,fb);
			fa=find(v),fb=find(u+n);
			if (fa!=fb) union_set(fa,fb);
		}
	}
}

void getans()
{
	for (int i=1;i<=n;i++) u[i]=find(i);
	memset(appear,-1,sizeof(appear));
	gang=0;
	for (int i=1;i<=n;i++)
	{
		if (appear[u[i]]==-1)
		{
			gang++;
			appear[u[i]]=1;	
		}
	}
	printf("%d",gang);
}

int main()
{
	solve();
	getans();
	return 0;
}
