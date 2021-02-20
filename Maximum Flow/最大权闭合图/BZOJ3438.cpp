#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#define S 0
#define T (m*2+n)+1
using namespace std;
const int MAXN=1000+50;
const int INF=0x7fffffff;
struct node
{
    int to,pos,cap;
};
int m,n; 
vector<node> E[MAXN*3];
int dis[MAXN*3],ans,a[MAXN],b[MAXN];
 
void addedge(int u,int v,int w)
{
    E[u].push_back((node){v,E[v].size(),w});
    E[v].push_back((node){u,E[u].size()-1,0});
}
 
void init()
{
    ans=0;
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);
    for (int i=1;i<=n;i++) scanf("%d",&b[i]);
    scanf("%d",&m);
    for (int i=1;i<=n;i++)
    {
        ans+=a[i]+b[i];
        addedge(S,i,a[i]);
        addedge(i,T,b[i]);
    }
    int cnt=n;
    for (int i=1;i<=m;i++)
    {
        int k,c1,c2,x;
        scanf("%d%d%d",&k,&c1,&c2);
        ++cnt,addedge(S,cnt,c1);
        ++cnt,addedge(cnt,T,c2);
        ans+=c1+c2;
        for (int j=0;j<k;j++)
        {
            scanf("%d",&x);
            addedge(cnt-1,x,INF);
            addedge(x,cnt,INF);
        }
    }
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
            else dis[tmp.to]=-1;//注意一下这里要清为-1，很重要★★★★★ 
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
