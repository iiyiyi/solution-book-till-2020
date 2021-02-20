#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int MAXN=100000+50;
char str[MAXN];
int n,cnt;
struct ACauto
{
	ACauto* next[26];
	ACauto* fail;
	int id;
	int sign;
	ACauto()
	{
		for (int i=0;i<26;i++) next[i]=NULL;
		fail=NULL;
		id=++cnt;
		sign=0;
	}
};

ACauto* rt=new ACauto();

void insert(char* s,ACauto* rt)
{
	ACauto* tmp=rt;
	for (int i=0;s[i];i++)
	{
		int index=s[i]-'a';
		if (tmp->next[index]==NULL)
			tmp->next[index]=new ACauto();
		tmp=tmp->next[index];
	}
	tmp->sign=strlen(s);
}

void buildfail(ACauto* rt)//这里我们建立Trie图而不是Trie树的AC自动机 
{
    queue<ACauto*> que;
    que.push(rt);
    while (!que.empty())
    {
        ACauto* head=que.front();que.pop();
        for (int i=0;i<26;i++)
        {
            if (head->next[i]==NULL)
            {
                if (head==rt) head->next[i]=rt;
                    else head->next[i]=head->fail->next[i];
            }
            else
            {
                if (head==rt) head->next[i]->fail=rt;
                    else
                    {
                        head->next[i]->fail=head->fail->next[i];
                        //if (head->next[i]->fail->sign) head->next[i]->sign=head->next[i]->fail->sign;/*注意！*/
                    }
                que.push(head->next[i]);
            }
        }
    }
} 

void init()
{
	cnt=0;
	scanf("%s",str);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		char s[MAXN];
		scanf("%s",s);
		insert(s,rt);
	}
	buildfail(rt);
}

void solve()
{
	ACauto* a[MAXN];
	char stack[MAXN];
	int top=0;
	a[top]=rt;
	for (int i=0;str[i];i++)
	{
		ACauto* j=a[top];
		stack[++top]=str[i];
		int index=str[i]-'a';
		a[top]=j->next[index];
		if (a[top]->sign) top-=a[top]->sign;
	}
	stack[top+1]='\0';
	puts(stack+1);
}

int main()
{
	init();
	solve();
	return 0;
} 
