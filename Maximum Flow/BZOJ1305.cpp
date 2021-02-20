#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define INF 0x7fffffff
#define S 0
#define T 4*n+1
using namespace std;
struct node
{
	int to,pos,cap;
};
const int MAXN=50+5;
int n,k; 
vector<node> E[MAXN*4+2];
vector<node> tmpE[MAXN*4+2];
int dis[MAXN*4+2];

void addedge(int u,int v,int w)
{
    tmpE[u].push_back((node){v,tmpE[v].size(),w});
    tmpE[v].push_back((node){u,tmpE[u].size()-1,0});
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
        if (head==T) return true;    //首次抵达T即可返回，不需要整张图全部分层 
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
 
int dinic()
{
	int flow=0;
    while (bfs())
    {
        int f=dfs(S,T,INF);
        if (f) flow+=f;else break;
    }
    return flow;
}

void init()
{
	scanf("%d%d",&n,&k);
//0 源点  
//1～n 男性喜欢  
//n+1~2n 男性不喜欢  
//2n+1~3n 女性不喜欢  
//3n+1~4n 女性喜欢  
//4n+1 汇点  
	for (int i=1;i<=n;i++) addedge(i,i+n,k);
	for (int i=2*n+1;i<=3*n;i++) addedge(i,i+n,k);
	for (int i=1;i<=n;i++)
	{
		char str[MAXN];
		scanf("%s",str+1);
		for (int j=1;j<=n;j++)
		{
			if (str[j]=='Y') addedge(i,3*n+j,1);
				else addedge(n+i,2*n+j,1); 
		} 
	}
	for (int i=1;i<=n;i++) addedge(S,i,0);
	for (int i=3*n+1;i<=4*n;i++) addedge(i,T,0);
}

void solve()
{
	int lb=0,ub=n;
	while (lb+1<ub)
	{
		for (int i=S;i<=T;i++)
			for (int j=0;j<E[i].size();j++) E[i][j]=tmpE[i][j];
		int mid=(lb+ub)>>1;
		for (int i=0;i<n;i++) E[S][i].cap=mid;
		for (int i=3*n+1;i<=4*n;i++) E[i][E[i].size()-1].cap=mid;
		int d=dinic();
		if (d==mid*n) lb=mid;else ub=mid;
	}
	for (int i=S;i<=T;i++)
		for (int j=0;j<E[i].size();j++) E[i][j]=tmpE[i][j];
	for (int i=0;i<n;i++) E[S][i].cap=ub;
	for (int i=3*n+1;i<=4*n;i++) E[i][E[i].size()-1].cap=ub;
	int d=dinic();
	printf("%d",(d==ub*n)?ub:lb);
}

int main()
{
	init();
	solve();
	return 0;
}
