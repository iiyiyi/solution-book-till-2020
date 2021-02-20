#include<bits/stdc++.h>
using namespace std;
const int MAXN=500000+50;
const int INF=0x7fffffff;
struct edge
{
    int to,len;
};
vector<edge> E[MAXN];
int n,s;
int l,r,dis[MAXN],f[MAXN],ban[MAXN];
 
void addedge(int u,int v,int w)
{
    E[u].push_back((edge){v,w});
    E[v].push_back((edge){u,w});
}
 
void init()
{
    scanf("%d%d",&n,&s);
    for (int i=1;i<n;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        addedge(u,v,w);
    }
}
 
void dfs(int u,int fa)
{
    f[u]=fa;
    for (int i=0;i<E[u].size();i++)
    {
        int to=E[u][i].to;
        if (ban[to] || to==f[u]) continue;
        dis[to]=dis[u]+E[u][i].len;
        dfs(to,u);
    }
}
 
void getd()
{
    memset(ban,0,sizeof(ban));
     
    l=1,r=1;
    dfs(l,0);
    for (int i=1;i<=n;i++) if (dis[i]>dis[r]) r=i;
     
    l=r;
    dis[r]=0;
    dfs(r,0);
    for (int i=1;i<=n;i++) if (dis[i]>dis[l]) l=i;
}
 
void solve()
{
    int i=l,j=l,ans=INF;
    for (;i;i=f[i])
    {
        while (f[j] && dis[i]-dis[f[j]]<=s) j=f[j];
        ans=min(ans,max(dis[j],dis[l]-dis[i]));
        //ÿ���ҵ���iΪһ���˵����ӽ���S����
        //�Ƚ����˵��ֱ���˵�ĳ��� 
    }
    for (i=l;i;i=f[i]) ban[i]=1;
    //����Ҫ�ҳ�������ֱ���������ȣ����Խ�ֹ����ֱ���ϵĵ� 
	for (int i=l;i;i=f[i]) dis[i]=0,dfs(i,f[i]);
	//��������ע������i�ĸ��ױ��봫��ȥf[i],������޸���ֱ�� 
    for (int i=1;i<=n;i++) ans=max(ans,dis[i]);
    printf("%d",ans);
}
 
int main()
{
    init();
    getd();
    solve();
    return 0;
} 
