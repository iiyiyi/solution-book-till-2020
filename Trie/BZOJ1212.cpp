#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
using namespace std;
const int MAXN=(1<<20)+10; 
const int maxlen=10;
struct Trie
{
	Trie* next[26];
	int avail;
	int dep;
	Trie()
	{
		for (int i=0;i<26;i++) next[i]=NULL;
		avail=0;
		dep=0;
	}
};
int n,m,f;
Trie* rt;

void insert(Trie* rt,char* str)
{
	int len=strlen(str);
	Trie* now=rt;
	for (int i=0;i<len;i++)
	{
		int index=str[i]-'a';
		if (now->next[index]==NULL) 
		{
			now->next[index]=new Trie;
			now->next[index]->dep=now->dep+1;
		}
		now=now->next[index];
	}
	now->avail=1;
}

int dp(Trie* rt,char* str)
{
	int f[MAXN];
	int len=strlen(str),ans;
	memset(f,0,sizeof(f));
	for (int i=0;i<=len;i++)
	{
		if (f[i] || i==0)
		{
			ans=i;
			Trie* now=rt;
			for (int j=i;j<=i+maxlen-1;j++)
			{
				if (str[j]>'z' || str[j]<'a') break;
				int index=str[j]-'a';
				if (now->next[index]==NULL) break;
				now=now->next[index];
				if (now->avail)	f[i+now->dep]=1;
			}
		}
	}
	return ans;
}

void init()
{
	rt=new Trie;
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++)
	{
		char str[11];
		scanf("%s",str);
		insert(rt,str);
	}
}

void get_ans()
{
	for (int i=0;i<m;i++)
	{
		char str[MAXN];
		scanf("%s",str);
		cout<<dp(rt,str)<<endl;
	}
}

int main()
{
	init();
	get_ans();
	return 0;	
} 
