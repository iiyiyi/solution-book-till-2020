#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
int w,h,n,ans;
const int MAXN=1000+10;
int x1[MAXN],x2[MAXN],y1[MAXN],y2[MAXN];
int hashx[MAXN*2],hashy[MAXN*2];
int fld[MAXN*2][MAXN*2]; 
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};

void compress()
{
	int tx=0,ty=0;
	for (int i=1;i<=n;i++)
	{
		hashx[++tx]=x1[i];hashx[++tx]=x2[i];
		hashy[++ty]=y1[i];hashy[++ty]=y2[i];
	}
	hashx[++tx]=0;hashx[++tx]=w;
	hashy[++ty]=0;hashy[++ty]=h;
	sort(hashx+1,hashx+tx+1);
	sort(hashy+1,hashy+ty+1);
	w=unique(hashx+1,hashx+tx+1)-(hashx+1);
	h=unique(hashy+1,hashy+ty+1)-(hashy+1);
	for (int i=1;i<=n;i++)
	{
		x1[i]=lower_bound(hashx+1,hashx+w+1,x1[i])-hashx-1;
		x2[i]=lower_bound(hashx+1,hashx+w+1,x2[i])-hashx-1;
		y1[i]=lower_bound(hashy+1,hashy+h+1,y1[i])-hashy-1;
		y2[i]=lower_bound(hashy+1,hashy+h+1,y2[i])-hashy-1;
	}
	w--;h--;
}

void init()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d%d%d%d",&x1[i],&y1[i],&x2[i],&y2[i]);
	compress();
}

void imos()	/*imos?*/
{
	memset(fld,0,sizeof(fld));
	for (int i=1;i<=n;i++)
	{
		fld[x1[i]][y1[i]]++;
		fld[x2[i]][y2[i]]++;
		fld[x1[i]][y2[i]]--;
		fld[x2[i]][y1[i]]--;
	}
	
	for (int i=0;i<w;i++)
		for (int j=1;j<h;j++)
			fld[i][j]+=fld[i][j-1];
			
	for (int j=0;j<h;j++)
		for (int i=1;i<w;i++)
			fld[i][j]+=fld[i-1][j];
}

void bfs(int x,int y)
{
	ans++;
	queue<int> qx,qy;
	qx.push(x);
	qy.push(y);
	fld[x][y]=1;
	while (!qx.empty())
	{
		int xx=qx.front();qx.pop();
		int yy=qy.front();qy.pop();
		for (int i=0;i<4;i++)
		{
		 	int nx=xx+dx[i],ny=yy+dy[i];
		 	if (nx<0 || ny<0 || nx>w || ny>h || fld[nx][ny]>0) continue;
		 	qx.push(nx);
		 	qy.push(ny);
		 	fld[nx][ny]=1;
		}
	}
}

void solve()
{
	ans=0;
	for (int i=0;i<w;i++)
		for (int j=0;j<h;j++)
			if (fld[i][j]==0) bfs(i,j);
	printf("%d\n",ans);
}

int main()
{
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	while (~scanf("%d%d",&w,&h)&&w&&h)
	{
		init();
		imos();
		solve();
	}
	return 0;	
} 
