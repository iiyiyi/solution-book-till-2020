#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int MAXN=14;
const int HASH=30007;
int ex,ey;
int m,n;
int maze[MAXN][MAXN];
int code[MAXN],ch[MAXN];
struct HashMap
{
    vector<int> hash[HASH];//存储f和state的下标 
    vector<ll> f,state;//存储对应的方案数和状态 
    void init()
    {
        for (int i=0;i<HASH;i++) vector<int>().swap(hash[i]);
        vector<ll>().swap(f);
        vector<ll>().swap(state);
    }
    void push(ll st,ll ans)
    {
        int h=st%HASH;
        for (int i=0;i<hash[h].size();i++)
        {
            int now=hash[h][i];
            if (state[now]==st)//如果已经存储了当前状态，直接累加 
            {
                f[now]+=ans;
                return;
            }
        }
        //如果没有存储过当前状态，累加 
        state.push_back(st);
        f.push_back(ans);
        hash[h].push_back(state.size()-1);
    }
}dp[2];

void decode(ll st)
{
    memset(code,0,sizeof(code));
    for (int i=n;i>=0;i--)
    {
        code[i]=st&7;//每三位代表一个信息 
        st>>=3;
    }
}

ll encode()
//用最小表示法重新编码 
{
    int cnt=1;
    memset(ch,-1,sizeof(ch));
    ch[0]=0;
    long long st=0;
    for (int i=0;i<=n;i++)
    {
        if (ch[code[i]]==-1) ch[code[i]]=cnt++;
        code[i]=ch[code[i]];
        st<<=3;
        st|=code[i]; 
    } 
    return st;
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
        int left=code[j-1];//左插头 
        int up=code[j];//上插头
        
        /*如果上下插头都没有*/ 
        if (!left && !up)
        {
            if (maze[i][j+1] && maze[i+1][j])
            {
                code[j-1]=code[j]=MAXN-1;
                //这里只要随便设置一个大数即可
                
                //【attention】这里千万不可以设置成MAXN，否则ch数组会抱★★★★★★★★
                
                //因为encode会重新用最小表示法编码 
                dp[cur].push(encode(),dp[1-cur].f[k]);
            }
        }
        
        /*只有上插头或者只有左插头*/
        if ((left&&(!up))||((!left)&&up))
        {
            
            int t=left|up;
            if (maze[i][j+1])//右边没有障碍
            {
                code[j-1]=0;
                code[j]=t;
                dp[cur].push(encode(),dp[1-cur].f[k]);
            } 
            if (maze[i+1][j])//下面没有障碍
            {
                code[j-1]=t;
                code[j]=0;
                if (j==n) shift();
                dp[cur].push(encode(),dp[1-cur].f[k]);
            }
        }
        
        /*上插头和右插头都有*/
        if (left && up)
        {
            if (left==up)
            {
                if (i==ex && j==ey)
                {
                    code[j-1]=code[j]=0;
                    if (j==n) shift();
                    dp[cur].push(encode(),dp[1-cur].f[k]);
                }
            }
            else
            {
                code[j-1]=code[j]=0;
                for (int t=0;t<=n;t++)
                    if (code[t]==up) code[t]=left;
                if (j==n) shift();
                dp[cur].push(encode(),dp[1-cur].f[k]);
            }
        } 
    }
}

void DpHorizon(int cur,int i,int j)//只能水平走 
{
	for (int k=0;k<dp[1-cur].state.size();k++)
	{
		decode(dp[1-cur].state[k]);
		int left=code[j-1],up=code[j];
		
		if(!up && left&& maze[i][j+1]!=0 && maze[i][j+1]!=3&& j!=n&&j!=1) //右边不是障碍物，也能够水平走,并且不是最右边 
		{
			code[j-1]=0;
            code[j]=left;
            dp[cur].push(encode(),dp[1-cur].f[k]);
		} 	
	} 
	
}

void DpVertical(int cur,int i,int j)//只能竖直走 
{
	for (int k=0;k<dp[1-cur].state.size();k++)
	{
		decode(dp[1-cur].state[k]);
		int left=code[j-1],up=code[j];
		
		if(up && !left && maze[i+1][j]!=0 && maze[i+1][j]!=2&&i!=m&&i!=1)//下边不是障碍物，也能够竖直走 
		{
			code[j-1]=up;
            code[j]=0;
            if(j==n)shift();
            dp[cur].push(encode(),dp[1-cur].f[k]);
		} 	
	} 
	
}

void dpblock(int i,int j,int cur)
{
    int k=0;
    for (int k=0;k<dp[1-cur].state.size();k++)
    {
        decode(dp[1-cur].state[k]);
        code[j-1]=code[j]=0;
        if (j==n) shift();
        dp[cur].push(encode(),dp[1-cur].f[k]);
    }
}

void solve()
{
    int cur=0;
    ll ans=0;
    dp[cur].init();
    dp[cur].push(0,1);//DP数组初始化 
    for (int i=1;i<=m;i++)
        for (int j=1;j<=n;j++)
        {
            cur^=1;
            dp[cur].init();
            if (maze[i][j]==1) dpblank(i,j,cur);
                else if (maze[i][j]==0)  dpblock(i,j,cur);
                else if  (maze[i][j]==2)DpHorizon(cur,i,j);
                else  DpVertical(cur,i,j);
        }
    for (int i=0;i<dp[cur].state.size();i++)
        ans+=dp[cur].f[i];
    printf("%lld",ans);
}


void init()
{
	scanf("%d%d",&m,&n);
	for (int i=1;i<=m;i++)
	{
		char str[MAXN];
		scanf("%s",str);
		for (int j=1;j<=n;j++)
		{
			if (str[j-1]=='#') maze[i][j]=0;
			if (str[j-1]=='.') maze[i][j]=1;
			if (str[j-1]=='-') maze[i][j]=2;
			if (str[j-1]=='|') maze[i][j]=3;
			if (str[j-1]!='#') ex=i,ey=j;
		}
	}
}

int main()
{

    init();
    if (ex==0) puts("0");//如果没有一个是空格的话直接输出0 
        else solve();
   
}
