#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define INF 0x7fffffff
#define S 0
#define T 
using namespace std;
struct node
{
	int to,pos,cap;
};
int n; 
vector<node> E[MAXN];
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
	scanf("%d",&n);
}

int main()
{
	init();
	solve();
	return 0;
}
