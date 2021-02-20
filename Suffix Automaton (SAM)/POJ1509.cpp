#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=10007*2;
char str[MAXN];
int len;

struct SAM
{
	int step[MAXN],next[MAXN][26],pre[MAXN];
	int tot,last;
	
	inline int newNode(int cnt)
	{
		step[++tot]=cnt;
		pre[tot]=0;
		for (int i=0;i<26;i++) next[tot][i]=0;
		return tot;
	}
	
	inline void extend(int x)
	{
		int p=last;
		int np=newNode(step[last]+1);
		while (p && !next[p][x]) next[p][x]=np,p=pre[p];
		if (!p) pre[np]=1;
		else
		{
			int q=next[p][x];
			if (step[q]==step[p]+1) pre[np]=q;
				else
				{
					int nq=newNode(step[p]+1);
					for (int i=0;i<26;i++) next[nq][i]=next[q][i];
					pre[nq]=pre[q];
					pre[q]=pre[np]=nq;
					while (p && next[p][x]==q) next[p][x]=nq,p=pre[p]; 
				}
		}
		last=np;
	}
	
	inline void add(int x)
	{
		extend(x);
	}
	
	inline void init()
	{
		tot=0;
		last=newNode(0);
	}
}suf;

void programinit()
{
	scanf("%s",str);
	len=strlen(str);
	for (int i=0;i<len;i++) str[i+len]=str[i];
	suf.init();
	for (int i=0;i<len*2;i++) suf.add(str[i]-'a');
}

void solve()
{
	int j=1;
	for (int i=0;i<len;i++)
		for (int k=0;k<26;k++)
			if (suf.next[j][k])
			{
				j=suf.next[j][k];
				break;
			}
	printf("%d\n",suf.step[j]-len+1);
}

int main()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		programinit();
		solve();
	}
}
