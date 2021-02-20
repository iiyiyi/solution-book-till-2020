#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define lnum 26
using namespace std;
const int MAXN=100000+50;
int  ppos[MAXN];//第i个P对应的栈顶位置编号
char str[MAXN];
int m,len,step,cnt=0,e[MAXN],start[MAXN],end[MAXN],ans[MAXN];
struct ACauto
{
	ACauto* next[lnum];
	ACauto* fail;
	int id,ed,order; 
	ACauto()
	{
		for (int i=0;i<lnum;i++) next[i]=NULL;
		fail=NULL;
		id=++cnt;
	}
};
struct node
{
	int to,id;
}; 
ACauto* rt=new ACauto();
ACauto* p[MAXN];//编号为i的节点指向的位置
vector<node> Q[MAXN];
vector<int> E[MAXN];

void addedge(int u,int v)
{
	E[u].push_back(v);
}

int lowbit(int x)
{
	return (x&(-x));
}

void modify(int p,int x)
{
	int i=p;
	while (i<=len)
	{
		e[i]+=x;
		i+=lowbit(i);
	}
}

int sum(int p)
{
	int s=0;
	int i=p;
	while (i>0)
	{
		s+=e[i];
		i-=lowbit(i);
	}
	return s;
}

void init()
{
	scanf("%s",str);
	len=strlen(str);
	int top=0,n=0;
	ACauto* stack[MAXN];
	stack[++top]=p[1]=rt;//不要忘记给p[1]赋值 
	for (int i=0;i<len;i++)
	{
		if (str[i]=='P') 
		{
			stack[top]->ed=++n;
			ppos[n]=stack[top]->id;
		}
			else if (str[i]=='B') top--;
				else
				{
					int index=str[i]-'a';
					if (stack[top]->next[index]==NULL) 
					{
						stack[top]->next[index]=new ACauto();
						p[cnt]=stack[top]->next[index];
					}
					stack[++top]=stack[top-1]->next[index];
				}
	}
	
	scanf("%d",&m);
	for (int i=0;i<m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		Q[y].push_back((node){ppos[x],i});
	}
} 

void buildfail()
{
    queue<ACauto*> que;
    que.push(rt);
    while (!que.empty())
    {
        ACauto* head=que.front();que.pop();
        for (int i=0;i<lnum;i++)
        {
            if (head->next[i]!=NULL)
            {
                if (head==rt)
                {
                    head->next[i]->fail=rt;
                    addedge(rt->id,head->next[i]->id);
                }
                else
                {
                    ACauto* tmp=head->fail;
                    while (tmp!=NULL)
                    {
                        if (tmp->next[i]!=NULL)
                        {
                            head->next[i]->fail=tmp->next[i];
                            addedge(tmp->next[i]->id,head->next[i]->id);
                            break;
                        }
                        else tmp=tmp->fail;
                    }
                    if (tmp==NULL) 
                    {
                        head->next[i]->fail=rt;
                        addedge(rt->id,head->next[i]->id);
                    }
                }
                que.push(head->next[i]);
            }
        }
    }
}

void dfs(int pos)
{
	ACauto* tmp=p[pos];
	tmp->order=++step;
	if (tmp->ed) start[tmp->ed]=step;
	for (int i=0;i<E[pos].size();i++) dfs(E[pos][i]);
	if (tmp->ed) end[tmp->ed]=step;
}

void query()
{
	memset(e,0,sizeof(e));
	int top=0,n=0;
	ACauto* stack[MAXN];
	stack[++top]=rt;
	for (int i=0;i<len;i++)
	{
		if (str[i]=='P')
		{
			n++;
			for (int i=0;i<Q[n].size();i++)
			{
				ACauto* to=p[Q[n][i].to];
				ans[Q[n][i].id]=sum(end[to->ed])-sum(start[to->ed]-1);
			}
		}
		else if (str[i]=='B')
		{
			modify(stack[top]->order,-1);
			top--;
		}
		else
		{
			int index=str[i]-'a';
			stack[++top]=stack[top-1]->next[index];
			modify(stack[top]->order,1);
		}
	}
}

void printans()
{
	for (int i=0;i<m;i++) printf("%d\n",ans[i]);
}

int main()
{
	init();
	buildfail();
	dfs(rt->id);
	query();
	printans();
	return 0;
}
