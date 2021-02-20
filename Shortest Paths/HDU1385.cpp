#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<queue>
#include<vector>
using namespace std;
const int MAXN=2000+50;
const int INF=0x7fffffff;

struct edge
{
    int to,len;
};

vector<edge> E[MAXN];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > pque;
int vis[MAXN],dis[MAXN],pre[MAXN],tax[MAXN];
int s1[MAXN],s2[MAXN],n;

void addedge(int u,int v,int w)
{
    E[u].push_back((edge){v,w});
}

void init()
{
    for (int i=1;i<MAXN;i++) vector<edge>().swap(E[i]);
    while (!pque.empty()) pque.pop();
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
        {
            int aij;
            scanf("%d",&aij);
            if (aij>=0 && i!=j) addedge(i,j,aij);
        }
    for (int i=1;i<=n;i++) scanf("%d",&tax[i]);
}

int compare(int now,int before)
{
    memset(s1,0,sizeof(s1));
    memset(s2,0,sizeof(s2));
    int i=0,j=-1;
    s1[0]=before;
    while (now!=0) s1[++i]=now,now=pre[now];
    while (before!=0) s2[++j]=before,before=pre[before];
    for (;i>=0 && j>=0;i--,j--)
        if (s1[i]<s2[j]) return 1;
            else if (s1[i]>s2[j]) return 0; 
    return (s1<s2);
}

int dijkstra(int S,int T)
{
    for (int i=1;i<=n;i++) vis[i]=0,dis[i]=INF,pre[i]=-1;
    dis[S]=0,pre[S]=0;
    pque.push(pair<int,int>(0,S));
    while (!pque.empty())
    {
        int u=pque.top().second;pque.pop();
        vis[u]=1;
        for (int i=0;i<E[u].size();i++)
        {
            int v=E[u][i].to,len=E[u][i].len+tax[v];
            if (dis[v]>=dis[u]+len)
            {
                if (dis[v]>dis[u]+len)
                {
                    dis[v]=dis[u]+len;    
                    pre[v]=u;
                    pque.push(pair<int,int>(dis[v],v));
                }
                else if (dis[v]==dis[u]+len && compare(u,v)) 
                {
                    pre[v]=u;
                    pque.push(pair<int,int>(dis[v],v));
                }
            }
        }
    }

    int i=0,now=T;
    while (now!=0) s1[++i]=now,now=pre[now];
    printf("From %d to %d :\n",S,T);
    printf("Path: ");
    while (i>=1)
    {
        printf("%d",s1[i--]);
        if (i!=0) printf("-->");
    }
    printf("\nTotal cost : %d\n\n",(S==T)?0:dis[T]-tax[T]);
    //注意如果S==T的时候，就不要减去tax了，否则会出现负值。 
}

void solve()
{
    int a,b;
    while (scanf("%d%d",&a,&b))
    {
        if (a==-1 && a==b) return;
        dijkstra(a,b);
    }
}

int main()
{
    while (scanf("%d",&n))
    {
        if (n==0) break;
        init();
        solve();
    } 
    return 0;    
}
