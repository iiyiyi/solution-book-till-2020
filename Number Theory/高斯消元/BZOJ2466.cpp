#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100+5;
const int INF=0x7fffffff;
int n,map[MAXN][MAXN],que[MAXN];
int ans;
 
void Gauss()
{
    for (int i=1;i<=n;i++)
    {
        int t=i;
        for (;t<=n && !map[t][i];t++);
        if (t<=n)
        {
            if (t!=i) for (int j=i;j<=n+1;j++) swap(map[i][j],map[t][j]);
            for (int j=i+1;j<=n;j++)
                if (map[j][i])
                    for (int k=i;k<=n+1;k++) map[j][k]^=map[i][k];//不要忘记这里要到n+1 
        }
    }
}
 
void dfs(int step,int now)
{
    if (now>=ans) return;
    if (!step)
    {
        ans=min(ans,now);
        return;
    } 
    if (map[step][step])
    {
    	int t=map[step][n+1];
    	//map[step][n+1]后续回溯中还要使用，所以要暂存给t 
        for (int i=step+1;i<=n;i++)
            if (map[step][i]) t^=que[i];//这里不要把step和i搞混了 
        que[step]=t;
        dfs(step-1,now+t);
    }
    else
    {
        que[step]=0;dfs(step-1,now);
        que[step]=1;dfs(step-1,now+1);
    }
}
 
void init()
{
    ans=INF;
    memset(que,0,sizeof(que));
    memset(map,0,sizeof(map));
    for (int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        map[u][v]=map[v][u]=1;
    }
    for (int i=1;i<=n;i++) map[i][i]=1,map[i][n+1]=1;
}
 
int main()
{
    while (~scanf("%d",&n))
    {
        if (n==0) break;
        init();
        Gauss();
        dfs(n,0);
        printf("%d\n",ans);
    }
    return 0;
} 

