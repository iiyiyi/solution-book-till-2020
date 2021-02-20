#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1000000+50;
char p[MAXN],t[MAXN],s[MAXN];
int next[MAXN],a[MAXN],len,lenp;

void getnext()
{
    int i=0,j=-1;
    next[i]=j;
    for (int i=1;i<len;i++)
    {
    	while (j!=-1 && p[i]!=p[j+1]) j=next[j];
    	if (p[i]==p[j+1]) ++j;
    	next[i]=j;
    }
}

void solve()
{
	int top=0;
	for (int i=0;i<len;i++)
	{
		int j=a[top];
		s[++top]=t[i];
		while (j!=-1 && p[j+1]!=s[top]) j=next[j];
		if (p[j+1]==s[top]) ++j;
		a[top]=j;
		if (a[top]==lenp-1) top-=lenp;
	}
	s[top+1]='\0';
	puts(s+1);
}

int main()
{
	scanf("%s%s",t,p);
	len=strlen(t),lenp=strlen(p);
	getnext();
	solve();
	return 0;
}
