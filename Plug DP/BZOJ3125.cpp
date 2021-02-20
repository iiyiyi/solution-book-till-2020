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
    vector<int> hash[HASH];//�洢f��state���±� 
    vector<ll> f,state;//�洢��Ӧ�ķ�������״̬ 
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
            if (state[now]==st)//����Ѿ��洢�˵�ǰ״̬��ֱ���ۼ� 
            {
                f[now]+=ans;
                return;
            }
        }
        //���û�д洢����ǰ״̬���ۼ� 
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
        code[i]=st&7;//ÿ��λ����һ����Ϣ 
        st>>=3;
    }
}

ll encode()
//����С��ʾ�����±��� 
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
        int left=code[j-1];//���ͷ 
        int up=code[j];//�ϲ�ͷ
        
        /*������²�ͷ��û��*/ 
        if (!left && !up)
        {
            if (maze[i][j+1] && maze[i+1][j])
            {
                code[j-1]=code[j]=MAXN-1;
                //����ֻҪ�������һ����������
                
                //��attention������ǧ�򲻿������ó�MAXN������ch����ᱧ���������
                
                //��Ϊencode����������С��ʾ������ 
                dp[cur].push(encode(),dp[1-cur].f[k]);
            }
        }
        
        /*ֻ���ϲ�ͷ����ֻ�����ͷ*/
        if ((left&&(!up))||((!left)&&up))
        {
            
            int t=left|up;
            if (maze[i][j+1])//�ұ�û���ϰ�
            {
                code[j-1]=0;
                code[j]=t;
                dp[cur].push(encode(),dp[1-cur].f[k]);
            } 
            if (maze[i+1][j])//����û���ϰ�
            {
                code[j-1]=t;
                code[j]=0;
                if (j==n) shift();
                dp[cur].push(encode(),dp[1-cur].f[k]);
            }
        }
        
        /*�ϲ�ͷ���Ҳ�ͷ����*/
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

void DpHorizon(int cur,int i,int j)//ֻ��ˮƽ�� 
{
	for (int k=0;k<dp[1-cur].state.size();k++)
	{
		decode(dp[1-cur].state[k]);
		int left=code[j-1],up=code[j];
		
		if(!up && left&& maze[i][j+1]!=0 && maze[i][j+1]!=3&& j!=n&&j!=1) //�ұ߲����ϰ��Ҳ�ܹ�ˮƽ��,���Ҳ������ұ� 
		{
			code[j-1]=0;
            code[j]=left;
            dp[cur].push(encode(),dp[1-cur].f[k]);
		} 	
	} 
	
}

void DpVertical(int cur,int i,int j)//ֻ����ֱ�� 
{
	for (int k=0;k<dp[1-cur].state.size();k++)
	{
		decode(dp[1-cur].state[k]);
		int left=code[j-1],up=code[j];
		
		if(up && !left && maze[i+1][j]!=0 && maze[i+1][j]!=2&&i!=m&&i!=1)//�±߲����ϰ��Ҳ�ܹ���ֱ�� 
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
    dp[cur].push(0,1);//DP�����ʼ�� 
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
    if (ex==0) puts("0");//���û��һ���ǿո�Ļ�ֱ�����0 
        else solve();
   
}
