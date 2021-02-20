#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lnum 3
using namespace std;
const int MAXK=1000;
const int MAXN=20*15+1;
int cnt=-1;
struct ACauto
{
    int id;
    ACauto* next[lnum];
    ACauto* fail;
    ACauto()
    {
        id=++cnt;
        for (int i=0;i<lnum;i++) next[i]=NULL;
        fail=NULL;
    }
};
ACauto* rt=new ACauto();
int go[MAXN][lnum];//���Ϊi�Ľڵ��������̵ı�ţ������������Ϊ0
int combo[MAXN];//���Ϊi�Ľڵ㼰���׺�ܹ����������ƥ����
int dp[MAXN][MAXK];//�ڱ��Ϊi�Ľڵ�������j���ܹ��ﵽ�����ֵ
int n,k;

void insert(ACauto* rt,char* str)
{
    int len=strlen(str);
    ACauto* now=rt;
    for (int i=0;i<len;i++)
    {
        int index=str[i]-'A';
        if (now->next[index]==NULL)
        {
            now->next[index]=new ACauto();
        }
        go[now->id][index]=now->next[index]->id;
        now=now->next[index];
    }
    combo[now->id]=1;
    //�ڲ�������׺������£���ǰ��β���Բ���һ��ƥ��
}

void buildfail(ACauto* rt)
{
    queue<ACauto*> que;
    que.push(rt);
    while (!que.empty())
    {
        ACauto* head=que.front();que.pop();
        for (int i=0;i<lnum;i++)
        {
            if (head->next[i]==NULL) continue;
            if (head==rt)
                head->next[i]->fail=rt;
            else
            {
                ACauto* tmp=head->fail;
                while (tmp!=NULL)
                {
                    if (tmp->next[i]!=NULL)
                    {
                        head->next[i]->fail=tmp->next[i];
                        break;
                    }
                    else
                    tmp=tmp->fail;
                }
                if (tmp==NULL) head->next[i]->fail=rt;
            }
            combo[head->next[i]->id]+=combo[head->next[i]->fail->id];
            //��ǰ�ڵ㼰���ַ�����׺�Ľڵ������Ϊģʽ������ÿ�ζ�Ҫ����ָ�������һ���ܹ��������µ�ƥ���������ڼ���ʱ�ۼӵģ�ֻ����failָ����һ�����ɡ�
            que.push(head->next[i]);
        }
    }
}

void init()
{
    memset(go,0,sizeof(go));
    memset(combo,0,sizeof(combo));
    scanf("%d%d",&n,&k);
    for (int i=0;i<n;i++)
    {
        char str[1000];
        scanf("%s",str);
        insert(rt,str);
    }
    buildfail(rt);
}

void dp_process()
{
    memset(dp,0,sizeof(dp));
    for (int i=0;i<=cnt;i++) dp[0][i]=combo[i];
    int cur=0;
    for (int l=1;l<=k;l++)
    {
        cur^=1;
        for (int i=0;i<=cnt;i++)
        {
            dp[cur][i]=0;
            for (int j=0;j<lnum;j++)
                dp[cur][i]=max(dp[cur][i],combo[i]+dp[cur^1][go[i][j]]);
        }
    }
    printf("%d",dp[cur][0]);
}

int main()
{
    init();
    dp_process();
    return 0;
}