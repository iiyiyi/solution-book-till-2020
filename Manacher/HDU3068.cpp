#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
const int MAXN=110000+50;
char str[MAXN],s[MAXN*2];
int p[MAXN*2]; 

void init()
{
	s[0]='$';s[1]='#';
	int j=1;
	for (int i=0;str[i];i++)
	{
		s[++j]=str[i];
		s[++j]='#';
	}
	//cout<<s<<endl;
}

void solve()
{
	int mx=0,mxid=0;
	memset(p,0,sizeof(p));
	for (int i=1;s[i];i++)
	{
		if (mx>i) p[i]=(p[2*mxid-i]<(mx-i)?p[2*mxid-i]:(mx-i));
			else p[i]=1;
		while(s[i-p[i]]==s[i+p[i]]) p[i]++;
		if (i+p[i]>mx)
		{
			mx=i+p[i];
			mxid=i;
		}
	}
}

int getans()
{
	int len=strlen(str)*2+2;
	int ans=-1;
	for (int i=1;i<len;i++) ans=max(ans,p[i]);
	ans--;
	return ans;
}

int main()
{
	while (scanf("%s",str)!=EOF)
	{
		init();
		solve();
		cout<<getans()<<endl;
	}
	return 0;
}
