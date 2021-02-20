#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int MAXN=100000+50;
char str[MAXN],s[MAXN*2+2];
int len,p[MAXN],l[MAXN],r[MAXN];

void init()
{
	scanf("%s",str);
	s[0]='$',s[1]='#';
	len=strlen(str);
	for (int i=0,j=1;i<len;i++)
	{
		s[++j]=str[i];
		s[++j]='#';
	}
}

void solve()
{
	int mx=0,mxid=0;
	for (int i=1;i<2*len+2;i++)
	{
		if (i<mx) p[i]=(p[2*mxid-i]<=(mx-i))?p[2*mxid-i]:(mx-i);
			else p[i]=1;
		while (s[i+p[i]]==s[i-p[i]]) p[i]++;
		if (i+p[i]-1>mx) mx=i+p[i]-1,mxid=i;
	}
}

void dp()
{
	queue<int> que1;
	for (int i=1;i<2*len+2;i++)
	{
		while (!que1.empty() && que1.front()+p[que1.front()]-1<i) que1.pop();
		que1.push(i);
		l[i]=2*(i-que1.front()+1)-1;
	}
	
	queue<int> que2;
	for (int i=2*len+1;i>=1;i--)
	{
		while (!que2.empty() && que2.front()-p[que2.front()]+1>i) que2.pop();
		que2.push(i);
		r[i]=2*(que2.front()-i+1)-1;
	}
}

void printans()
{
	int ans=-1;
	for (int i=1;i<2*len+2;i++) 
		if (s[i]=='#')
		{
			ans=max(ans,(l[i]-1)/2+(r[i]-1)/2);
		}
	printf("%d",ans);
}

int main()
{
	init();
	solve();
	dp();
	printans();
	return 0;
}
