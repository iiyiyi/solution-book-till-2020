#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN=1000000+500;
typedef long long ll;
vector<int> E[MAXN];
int n,power[MAXN],hate[MAXN];
int vis[MAXN];
int U,V;
ll g[MAXN],f[MAXN];
int banu,banv;
 
void addedge(int u,int v)
{
    E[u].push_back(v);
    E[v].push_back(u);
}
 
void dfs(int u,int fr)
{
    vis[u]=1;
    for (int i=0;i<E[u].size();i++)
    {
        int to=E[u][i];
        if (to!=fr)
        {
            if (!vis[to]) dfs(to,u);
            else
            {
                vis[to]=1;
                U=u;V=to;
                banu=i;cout<<banu<<endl;
                return;
            }
        }
    }
}
 
void TreeDP(int u,int fr,int rt,int ban)
{
    vis[u]=1;
    f[u]=power[u];
    g[u]=0;
    for (int i=0;i<E[u].size();i++)
    {
        int to=E[u][i];
        if (u==rt && i==ban) continue;
        if (to!=fr && to!=rt)
        {
            TreeDP(to,u,rt,ban);
            f[u]+=g[to];
            g[u]+=max(g[to],f[to]);
        }
    }
}
 
void init()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%d%d",&power[i],&hate[i]);
        addedge(i,hate[i]);
    }
} 
 
void get_ans()
{
    memset(vis,0,sizeof(vis));
    ll ans=0;
    for (int i=1;i<=n;i++)
        if (!vis[i]) 
        {
            dfs(i,-1);
            int banu,banv;
            for (int i=0;i<E[U].size();i++) if (E[U][i]==V)
            {
            	banu=i;
            	break;
			}cout<<banu<<endl;
			for (int i=0;i<E[V].size();i++) if (E[V][i]==U)
			{
				banv=i;
				break;
			}
            

            TreeDP(U,-1,U,banu);
            ll uans=g[U];
             
            TreeDP(V,-1,V,banv);
            ll vans=g[V];
            ans+=max(uans,vans);
        }
    cout<<ans<<endl;
}
 
int main()
{
    init();
    get_ans();
    return 0;   
} 

