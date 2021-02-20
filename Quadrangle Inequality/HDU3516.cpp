#include<cstdio>  
#include<cstring>  
#include<iostream>  
#include<algorithm>  
using namespace std;  
const int MAXN=1010;
const int INF=1e9;
//这里INF设太大会溢出来 
int T,t,n;  
int dp[MAXN][MAXN],s[MAXN][MAXN];
int x[MAXN],y[MAXN];  

void solve()
{
	for(int i=n;i>=1;i--)  
        for(int j=i+1;j<=n;j++)  
        {  
            dp[i][j]=INF;  
            for(int k=s[i][j-1];k<=s[i+1][j];k++)  
            {  
  				int ret=dp[i][k]+dp[k+1][j]+x[k+1]-x[i]+y[k]-y[j];  
               	if(ret<dp[i][j])  
               	{  
            	    dp[i][j]=ret;  
                    s[i][j]=k;  
                }  
            }  
        }  
    printf("%d\n",dp[1][n]);  
}

void init()
{
	for(int i=1;i<=n;i++)  
        scanf("%d%d",&x[i],&y[i]); 
	memset(dp,0,sizeof(dp));
	memset(s,0,sizeof(s)); 
    for(int i=1;i<=n;i++)  
        s[i][i]=i-1;  
}

int main()  
{   
    while(~scanf("%d",&n))  
    {  
		init();
		solve();
    }  
}  
