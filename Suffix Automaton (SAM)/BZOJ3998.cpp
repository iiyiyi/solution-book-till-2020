#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=500000+50;
char str[MAXN];
int len,sign,k;

struct SAM
{
	int step[MAXN*2],pre[MAXN*2],next[MAXN*2][26],q[MAXN*2];
	int v[MAXN*2],s[MAXN*2],sum[MAXN*2];
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
        s[np]=1;
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
	inline void clear()
	{
		tot=0;
		last=newNode(0);
	}
	
	inline void prep()
    {
        for(int i=1;i<=tot;i++)
            v[step[i]]++;//累加每个step[i]的个数 
        for(int i=1;i<=tot;i++)
            v[i]+=v[i-1];//v[i]表示按step值从小到大的顺序排序后，step值为i的数在q数组中最右端的下标 
        for(int i=tot;i>=1;i--)
            q[v[step[i]]--]=i;//每次将当前的i放入对应step[i]最右端的位置，然后将step[i]的最右端左移 
        for(int i=tot;i>=1;i--)
        {
            if(sign==1)	s[pre[q[i]]]+=s[q[i]];
            	else s[q[i]]=1;
        }
        s[1]=0;//不要忘了根节点是虚点 
        for(int i=tot;i>=1;i--)
        {
            sum[q[i]]+=s[q[i]];
            for(int j=0;j<26;j++) sum[q[i]]+=sum[next[q[i]][j]];
        }
     }
     
     inline void dfs(int d,int k)
     {
     	if (k<=s[d]) return;
     	k-=s[d];
     	for (int i=0;i<26;i++)
     	{
     		int tmp=next[d][i];
     		if (tmp>0)
     		{
     			if (k<=sum[tmp])
     			{
     				printf("%c",i+'a');
     				dfs(tmp,k);
     				return;
				}
				k-=sum[tmp];
			}
		}
	 }
}suf;

void init()
{
	scanf("%s",str);
	suf.clear();
	len=strlen(str);
	for (int i=0;i<len;i++) suf.extend(str[i]-'a'); 
	scanf("%d%d",&sign,&k);
}

int main()
{
	init();
	suf.prep();
	suf.dfs(1,k);
	return 0;
}
