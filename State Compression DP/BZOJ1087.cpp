#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int MAXN=512;
const int MAXK=100;
const int MAXM=15;
int n,m;
int map[MAXN][MAXN];
ll f[MAXM][MAXK][MAXN];//f[i][j][k]第i行，已用去j个国王，当前行状态为k 
int usable[MAXN];
int digit[MAXN];

int Usable(int x)
{
	if (x<<1&x || x>>1&x) return 0;else return 1;
	//不能有相邻的1 
}

int get_digit(int x)
{
	int ret=0;
	while (x) ret+=x&1,x>>=1;
	return ret;
}

int Judge(int x,int y)
{
	if (x&y || (x<<1)&y || (x>>1)&y) return 0;else return 1;
	/*不可行的情况有三种*/ 
}

void init()
{
	memset(usable,0,sizeof(usable));
	memset(map,0,sizeof(map));
	for (int i=0;i<1<<n;i++)
		if (Usable(i)) usable[++usable[0]]=i;
	/*预处理可行的状态（左右不能有相邻的1）*/ 
	for (int i=1;i<=usable[0];i++)
		for (int j=1;j<=usable[0];j++)
		{ 
			if (Judge(usable[i],usable[j])) map[i][j]=1;
		} 
	/*预处理可行的状态中能够转换的状态*/
	for (int i=1;i<=usable[0];i++) digit[i]=get_digit(usable[i]);
	/*预处理每一个可行状态中1的个数*/
}

ll dp()
{
	memset(f,0,sizeof(f));
	f[0][0][1]=1;
	for (int i=1;i<=n;i++)
		for (int j=0;j<=m;j++)
			for (int k=1;k<=usable[0];k++)
				if (digit[k]<=j)
				{
					for (int l=1;l<=usable[0];l++)
					{
						if (map[l][k] && digit[l]+digit[k]<=j) 
							f[i][j][k]+=f[i-1][j-digit[k]][l];
					}
				}
	ll ret=0;
	for (int i=1;i<=usable[0];i++) ret+=f[n][m][i];
	return ret;
}

int main()
{
	scanf("%d%d",&n,&m);
	init();
	cout<<dp()<<endl;
	return 0;	
} 
