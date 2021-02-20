#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAXN=100000+5;
int n;
char str[2][MAXN];
struct SAM
{
	int step[MAXN*2],pre[MAXN*2],next[MAXN*2][26];
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
		int np=newNode(step[p]+1);
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
				while (p&&next[p][x]==q) next[p][x]=nq,p=pre[p]; 
			}
	
		}
		last=np;
	}
	
	inline void clear()
	{
		int tot=0;
		last=newNode(tot);
	}
	
	inline int Query()
	{  
    	int ret=0,cnt=0;  
    	int p=1;  
    	for(int i=0;str[1][i];i++)
		{  
			int index=str[1][i]-'a';
        	if(next[p][index]) p=next[p][index],cnt++;
			else
			{	
            	while (p && !next[p][index]) p=pre[p];
            	if(!p) p=1,cnt=0;  
            		else cnt=step[p]+1,p=next[p][index];
					/*由于沿着pre返回得到的字符串是当前字符串的后缀，所以第一个拥有index孩子的就是最长满足的后缀，长度即为step+1*/  
        	}
        	ret=max(ret,cnt);  
    	}  
    	return ret;  
	}  
}suf;

void init()
{
	scanf("%d",&n);
	scanf("%s",str[0]);
	int len=strlen(str[0]);
	suf.clear();
	for (int i=0;i<len;i++) suf.extend(str[0][i]-'a');
	scanf("%s",str[1]);
}

int main()
{
	init(); 
	printf("%d",suf.Query());
	return 0;
} 
