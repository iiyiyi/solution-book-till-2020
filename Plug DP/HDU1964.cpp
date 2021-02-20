#include<bits/stdc++.h>
#define u 0
#define d 1
#define l 2
#define r 3
using namespace std;
typedef long long ll;
const int MAXN=15;
const int HASH=10007;
struct Hashmap
{
	vector<int> hash[HASH];
	vector<ll> state,f;
	void clear()
	{
		for (int i=0;i<HASH;i++) vector<int>().swap(hash[i]);
		vector<ll>().swap(state);
		vector<ll>().swap(f);
	}
	
	void push(ll st,ll ans)
	{
		int now=st%HASH;
		for (int i=0;i<hash[now].size();i++)
		{
			int h=hash[now][i];
			if (state[h]==st) //st写成了now QAQ下面return还忘记写到大括号里面去了，浪费了3个小时查orz 
			{
				f[h]=min(f[h],ans);
				return;
			}
		}
		hash[now].push_back(state.size());
		state.push_back(st);
		f.push_back(ans);
	}
}dp[2];
int m,n;
int maze[MAXN][MAXN][4],code[MAXN];//上下左右 
int ch[MAXN];

void decode(ll st)
{
	for (int i=n;i>=0;i--)
	{
		code[i]=st&7;
		st>>=3;
	}
}

ll encode()
{
	ll ret=0;
	int cnt=0;
	memset(ch,-1,sizeof(ch));
	ch[0]=0;
	for (int i=0;i<=n;i++)
	{
		if (ch[code[i]]==-1) ch[code[i]]=++cnt;
		code[i]=ch[code[i]];
		ret<<=3;
		ret+=code[i];
	}
	return ret;
}

void shift()
{
    for (int i=n;i>0;i--) code[i]=code[i-1];
    code[0]=0;
} 

void dpblank(int i,int j,int cur)
{
	for (int k=0;k<dp[1-cur].state.size();k++)
	{
		decode(dp[1-cur].state[k]);
		if (j==1)
		{
			if (code[n]!=0) continue;
				else shift();
		}
		int left=code[j-1],up=code[j];//left和up要等到shift之后再取值 
		if (left && up)
		{
			if (left==up)
			{
				if (i==m && j==n)
				{
					code[j-1]=code[j]=0;
					dp[cur].push(encode(),dp[1-cur].f[k]);
				}
			}
			else
			{
				code[j-1]=code[j]=0;
				for (int i=0;i<=n;i++) if (code[i]==left) code[i]=up;
				dp[cur].push(encode(),dp[1-cur].f[k]);
			}
		}
		
		if ((left && !up) || (up && !left))
		{	
			int t=left|up;
			if (j<n)
			{
				code[j-1]=0,code[j]=t;
				dp[cur].push(encode(),dp[1-cur].f[k]+maze[i][j][r]);
			}
			if (i<m)
			{
				code[j-1]=t,code[j]=0;
				dp[cur].push(encode(),dp[1-cur].f[k]+maze[i][j][d]);
			}
		}	
		
		if (!left && !up)
		{
			if (i<m && j<n) 
			{
				code[j-1]=code[j]=MAXN-1;
				dp[cur].push(encode(),dp[1-cur].f[k]+maze[i][j][d]+maze[i][j][r]);
			}
		}
	}
}

void init()
{
	scanf("%d%d",&m,&n);
	char str[MAXN];
	getchar();
	gets(str);
	memset(maze,0xef,sizeof(maze));
	for (int i=1;i<=m;i++)
	{
		gets(str);
		for (int j=1;j<=(n-1);j++)
			maze[i][j][r]=maze[i][j+1][l]=str[2*j]-'0';
		if (i!=m)
		{
			gets(str);
			for (int j=1;j<=n;j++)
				maze[i][j][d]=maze[i+1][j][u]=str[2*j-1]-'0';
		}
		
	}
	gets(str);
}
void solve()
{
	int cur=0;
	dp[cur].clear();
	dp[cur].push(0,0);
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++)//m和n写反掉啦 
		{
			cur^=1;
			dp[cur].clear();
			dpblank(i,j,cur);
		}
	ll ans=1e16;
	for (int i=0;i<dp[cur].state.size();i++) ans=min(ans,dp[cur].f[i]);
	printf("%lld\n",ans);
}

int main()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		init();
		solve();
	}
	return 0;
}
