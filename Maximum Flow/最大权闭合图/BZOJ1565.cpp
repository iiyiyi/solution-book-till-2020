/*2016.7.29更正*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define S 0
#define T m*n+1
using namespace std;
const int MAXN=35;
struct node
{
	int to,pos,cap;
};
const int INF=0x7fffffff;
vector<int> rE[MAXN*MAXN];
vector<node> E[MAXN*MAXN]; 
int score[MAXN*MAXN];
int n,m,ans=0;
int usable[MAXN*MAXN],into[MAXN*MAXN];
int dis[MAXN*MAXN];

void addedge(int u,int v,int w)
{
	rE[v].push_back(u);
	into[u]++; 
	E[u].push_back((node){v,E[v].size(),w});
	E[v].push_back((node){u,E[u].size()-1,0}); 
}

void Topology()
{
	memset(usable,0,sizeof(usable));
	queue<int> que;
	for (int i=S;i<=T;i++)
		if (!into[i]) que.push(i);
	while (!que.empty())
	{
		int head=que.front();que.pop();
		usable[head]=1;
		if (score[head]>0) ans+=score[head];
		for (int i=0;i<rE[head].size();i++)
		{
			int to=rE[head][i];
			into[to]--;
			if (!into[to]) que.push(to); 
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
        if (head==T) return true;	//首次抵达T即可返回，不需要整张图全部分层 
        for (int i=0;i<E[head].size();i++)
        {
            node tmp=E[head][i];
            if (dis[tmp.to]==-1 && tmp.cap && usable[tmp.to])
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
}

void init()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			int w,fr=(i-1)*m+j;
			scanf("%d%d",&score[fr],&w);
			if (score[fr]>0) addedge(S,fr,score[fr]);
				else if (score[fr]<0) addedge(fr,T,-score[fr]);
			for (int k=1;k<=w;k++)
			{
				int r,c;
				scanf("%d%d",&r,&c);
				r++;c++;
				int to=(r-1)*m+c;
				addedge(to,fr,INF);
			}
			if (j!=m) addedge(fr,fr+1,INF);
		}
}

int main()
{
	init();
	Topology();
	dinic();
	printf("%d",ans);
	return 0;
}
