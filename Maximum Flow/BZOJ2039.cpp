#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#define S 0
#define T n+1
using namespace std;
const int MAXN=1000+50;
const int INF=0x7fffffff;
struct node
{
    int to,pos,cap;
};
int m,n,ans=0; 
vector<node> E[MAXN*3];
int dis[MAXN],e[MAXN][MAXN],sum[MAXN];
 
void addedge(int u,int v,int w)
{
    E[u].push_back((node){v,E[v].size(),w});
    E[v].push_back((node){u,E[u].size()-1,0});
}
 
void init()
{
    scanf("%d",&n);
    int cost;
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&cost);
        addedge(i,T,cost);
    }
    int Eij;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
        {
            scanf("%d",&e[i][j]);
            ans+=e[i][j];
            if (i!=j) 
            {
                sum[i]+=e[i][j];
                addedge(i,j,2*e[i][j]); 
            }
        }
    for (int i=1;i<=n;i++) addedge(S,i,sum[i]);
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
 
int main()
{
    init();
    dinic();
    return 0;
}
