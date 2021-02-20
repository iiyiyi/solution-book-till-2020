#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN=10000+500;
vector<int> E[MAXN],rE[MAXN];
int n,in[MAXN],visfr[MAXN],visto[MAXN],vis[MAXN],lk[MAXN],ans[MAXN],cnt=0;

void addedge(int u,int v)
{
	E[u].push_back(v);
	rE[v].push_back(u); 
}

int find(int u)
{
	for (int j=0;j<E[u].size();j++)
    {
    	int i=E[u][j];
        if (!vis[i] && !visto[i])
        {
            vis[i]=1;
            if (!lk[i] || find(lk[i]))
            {
                lk[i]=u;
                ans[u]=i;
                return 1;
            }
        }
    }
    return 0;
}

void init()
{
	memset(visfr,0,sizeof(visfr));
	memset(visto,0,sizeof(visto));
	memset(in,0,sizeof(in));
	memset(lk,0,sizeof(lk));
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		int d;
		scanf("%d",&d);
		int a=i+d;if (a>n) a-=n;
		int b=i-d;if (b<1) b+=n;
		if (a<b) addedge(i,a),addedge(i,b);
			else if (a>b) addedge(i,b),addedge(i,a);
				else if (a==b)
				{
					visfr[i]=visto[a]=1;
					ans[i]=a;
					cnt++;
				}
		if (a!=b) in[a]++,in[b]++;else in[a]++;
	}
	for (int i=1;i<=n;i++)
		if (in[i]==1 && !visto[i])
		{
			visto[i]=visfr[rE[i][0]]=1;
			ans[rE[i][0]]=i;
			cnt++;
		}
}

void solve()
{
	for (int i=n;i>=1;i--)
	{
		if (visfr[i]) continue;
		memset(vis,0,sizeof(vis));
		if (find(i)) cnt++;else break;
	}
	if (cnt==n)
	{
		for (int i=1;i<=n;i++) 
		{
			printf("%d",(ans[i]+n-1)%n);
			if (i!=n) printf(" ");
		}
	}
	else puts("No Answer");
}

int main()
{
	freopen("transform.in","r",stdin);
	freopen("transform.out","w",stdout);
	init();
	solve();
	return 0;
}
