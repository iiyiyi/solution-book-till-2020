#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#define S 0
#define T m*n*3+1 
using namespace std;
const int INF=0x7fffffff;
const int MAXN=3*100*100+50;
struct node
{
    int to,pos,cap;
};
int m,n,ans; 
vector<node> E[MAXN];
int dis[MAXN];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
 
void addedge(int u,int v,int w)
{
    E[u].push_back((node){v,E[v].size(),w});
    E[v].push_back((node){u,E[u].size()-1,0});
}
 
bool bfs()
{
    memset(dis,-1,sizeof(dis));
    queue<int> que;
    while (!que.empty()) que.pop(); 
    que.push(S);
    dis[S]=0;
    while (!que.empty())
    {
        int head=que.front();que.pop();
        if (head==T) return true;  
        for (int i=0;i<E[head].size();i++)
        {
            node tmp=E[head][i];
            if (dis[tmp.to]==-1 && tmp.cap)
            {
                dis[tmp.to]=dis[head]+1;
                que.push(tmp.to);
            }
        }
    }
    return false;
}
 
int dfs(int s,int e,int f)
{
    if (s==e) return f;
    int ret=0;
    for (int i=0;i<E[s].size();i++)
    {
        node &tmp=E[s][i];
        if (dis[tmp.to]==dis[s]+1 && tmp.cap)
        {
            int delta=dfs(tmp.to,e,min(f,tmp.cap));
            if (delta>0)
            {
                tmp.cap-=delta;
                E[tmp.to][tmp.pos].cap+=delta;
                f-=delta;
                ret+=delta;
                if (f==0) return ret;
            }
            else dis[tmp.to]=-1;
        }
    } 
    return ret;
}
 
void dinic()
{
    while (bfs())
    {
        int f=dfs(S,T,INF);
        if (f) ans-=f;else break;
    }
    printf("%d\n",ans);
}

void init()
{
	scanf("%d%d",&n,&m);
	ans=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			int now=(i-1)*m+j,art;
			scanf("%d",&art);
			addedge(S,now,art);
			ans+=art;
		}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			int now=(i-1)*m+j,science;
			scanf("%d",&science);
			addedge(now,T,science);
			ans+=science;
		}
		
	int cnt=m*n,same;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			++cnt;
			scanf("%d",&same);
			addedge(S,cnt,same);
			ans+=same;
			addedge(cnt,(i-1)*m+j,INF);
			for (int k=0;k<4;k++)
			{
				int nowx=i+dx[k],nowy=j+dy[k];
				if (nowx>=1 && nowx<=n && nowy>=1 && nowy<=m)
					addedge(cnt,(nowx-1)*m+nowy,INF);
			}
		}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			++cnt;
			scanf("%d",&same);
			addedge(cnt,T,same);
			ans+=same;
			addedge((i-1)*m+j,cnt,INF);
			for (int k=0;k<4;k++)
			{
				int nowx=i+dx[k],nowy=j+dy[k];
				if (nowx>=1 && nowx<=n && nowy>=1 && nowy<=m)
					addedge((nowx-1)*m+nowy,cnt,INF);
			}
		}
}
 
int main()
{
    init();
    dinic();
    return 0;
}
