#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000+5;
int w[MAXN][MAXN],vis[MAXN][MAXN];
int peak,valley,higher,lower,n;
int dx[8]={1,1,1,-1,-1,-1,0,0};
int dy[8]={0,1,-1,0,1,-1,1,-1};
struct node
{
	int x,y;
};
queue<node> que;

void init()
{
	peak=valley=0;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++) scanf("%d",&w[i][j]);
}

void bfs(int x,int y)
{
	lower=higher=0;
	while (!que.empty()) que.pop();
	que.push((node){x,y});
	vis[x][y]=1;
	while (!que.empty())
	{
		int hx=que.front().x,hy=que.front().y;
		que.pop();
		for (int i=0;i<8;i++)
		{
			int xx=hx+dx[i],yy=hy+dy[i];
			if (xx<=0 || xx>n || yy<=0 || yy>n) continue;
			if (w[xx][yy]==w[hx][hy] && !vis[xx][yy])
			{
				que.push((node){xx,yy});
				vis[xx][yy]=1;
			}
			else
			{
				if (w[xx][yy]>w[hx][hy]) higher++;
					else if (w[xx][yy]<w[hx][hy]) lower++;
			}
		} 
	} 
	if (higher==0 && lower!=0) peak++;
	if (lower==0 && higher!=0) valley++; 
}

void solve()
{
	memset(vis,0,sizeof(vis));
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if (!vis[i][j]) bfs(i,j);
	if (!peak && !valley) peak=valley=1;
	printf("%d %d\n",peak,valley);
}

int main()
{
	init();
	solve();
	return 0;
} 
