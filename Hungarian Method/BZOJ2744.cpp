#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector> 
using namespace std;
const int MAXA=200+50;
const int MAXB=3000+50;
int na,nb,m;
int a[MAXA],b[MAXB]; 
bool map[MAXA][MAXB];
vector<int> E[MAXB];
int T1=0,T2=0,ban[MAXB],tim[MAXB],vis[MAXB],lk[MAXB];

void addedge(int u,int v)
{
	E[u].push_back(v);
}

int count(int x)
{
	int re=0;
	while (x)
	{
		re+=x&1;
		x>>=1;
	}
	return re;
}

int find(int x)
{
	if (ban[x]==T1)
		return 0;
	for (int i=0;i<E[x].size();i++)
	{
		int to=E[x][i];
		if ((ban[to]!=T1) && (vis[to]!=T2))
		{
			vis[to]=T2;
			if (tim[to]!=T1 || !lk[to] || find(lk[to]))
			{
				tim[to]=T1;
				lk[to]=x;
				return 1;
			}
		}
	}
	return 0;
}

int mis(int x=0,int y=0)
{
	++T1;
	int ret=0;
	for (int i=1;i<=nb;i++)
		if (map[x][i] || map[y][i]) ban[i]=T1,++ret;
	for (int i=1;i<=nb;i++)
		if (!(b[i]&1))
		{
			++T2;
			if (find(i)) ++ret;
		}
	return (nb-ret);
}

void init()
{
	memset(map,1,sizeof(map));
	scanf("%d%d%d",&na,&nb,&m);
	for (int i=1;i<=na;i++) scanf("%d",&a[i]);
	for (int i=1;i<=nb;i++) scanf("%d",&b[i]);
	for (int i=0;i<m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		map[x][y]=0;
	}
}

void solve()
{
	for (int i=1;i<=nb;i++)
		if (!(b[i]&1))
			for (int j=1;j<=nb;j++)
				if (b[j]&1)
					if (!(count(b[i]|b[j])&1))
						addedge(i,j);
	for (int i=1;i<=nb;i++) map[0][i]=0;
	int ans=mis();
	for (int i=1;i<=na;i++)
		ans=max(ans,mis(i)+1);
	for (int i=1;i<=na;i++)
		if (a[i]&1)
			for (int j=1;j<=na;j++)
				if (!(a[j]&1))
					ans=max(ans,mis(i,j)+2);
	printf("%d",ans);
}

int main()
{
	init();
	solve();
	return 0;
} 
