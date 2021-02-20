#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=10;
const int MAXM=105;
const int HASH=30007;
const int INF=0x7fffffff;
ll ans=-1ll << 60;
int n,m,sat[MAXM][MAXN];
int code[MAXN];

struct HashMap
{
	vector<int> hash[HASH];
	vector<ll> state,f;
	
	void clear()
	{
		for(int i=0;i<HASH;i++) vector<int>().swap(hash[i]);
		vector<ll>().swap(state);
		vector<ll>().swap(f);
	}
	
	void push(ll st,ll ans)
	{
		int h=st%HASH;
		for (int i=0;i<hash[h].size();i++)
		{
			int now=hash[h][i];
			if (state[now]==st)
			{
				f[now]=max(f[now],ans);
				return;
			}
		}
		state.push_back(st);
		f.push_back(ans);
		hash[h].push_back(state.size()-1);
	}
}dp[2];

void decode(ll state)
{
	memset(code,0,sizeof(code));
	for (int i=n;i>=0;i--)
	{
		code[i]=state&7;
		state>>=3;
	}
}

void shift()
{
	for (int i=n;i>0;i--) code[i]=code[i-1];
    code[0]=0;
} 

ll encode()
{
	int ch[MAXN],cnt=0;
	memset(ch,-1,sizeof(ch));
	ch[0]=0;
	ll ret=0;
	for (int i=0;i<=n;i++)
	{
		if (ch[code[i]]==-1) ch[code[i]]=++cnt;
		code[i]=ch[code[i]];
		ret<<=3;
		ret|=code[i];
	}
	return ret;
}

void dpblank(int i,int j,int cur)
{
	for (int k=0;k<dp[1-cur].state.size();k++)
	{
		decode(dp[1-cur].state[k]);
		if (j==1)//把之前shift的写法改成这样写了，总之就过了，也不知道为什么orz 
		{
			if (code[n]) continue;
			shift();
		}
		int left=code[j-1],up=code[j];
		
		if (left && up)
		{
			code[j-1]=code[j]=0;
			if (left==up)
			{
				if (encode()==0) ans=max(ans,dp[1-cur].f[k]+sat[i][j]);
				//注意和之前不一样的地方：如果已经封闭起来了就更新答案 
			}
			else
			{
				for (int t=0;t<=n;t++) if (code[t]==left) code[t]=up;
				dp[cur].push(encode(),dp[1-cur].f[k]+sat[i][j]);
			}
		}
		
		if ((left && (!up)) || (up && (!left)))
		{
			int t=left|up;
			code[j-1]=0;
			code[j]=t;
			dp[cur].push(encode(),dp[1-cur].f[k]+sat[i][j]); 			
			code[j-1]=t;
			code[j]=0;
			dp[cur].push(encode(),dp[1-cur].f[k]+sat[i][j]);
		}
		
		if (!left && !up)
		{ 
        	dp[cur].push(encode(),dp[1-cur].f[k]);
        	//注意并不一定是所有格子都要经过，所以还要考虑不经过当前格子的情况 
			code[j-1]=code[j]=MAXN-1;
			dp[cur].push(encode(),dp[1-cur].f[k]+sat[i][j]);
		}
	}
}

void init()
{
	scanf("%d%d",&m,&n);
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++) scanf("%d",&sat[i][j]);
}

void solve()
{
	int cur=0;
	dp[cur].clear();
	dp[cur].push(0,0);
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++)
		{
			cur^=1;
			dp[cur].clear();
			dpblank(i,j,cur);
		}
	printf("%lld",ans);
}

int main()
{
	init();
	solve();
	return 0;
}
