#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define mod 10000019
#define p 20011
using namespace std;
typedef long long ll;
const int MAXN=10;
const int MAXLEN=2000+50;
int n,minl;
ll hash[MAXN][MAXLEN];
char str[MAXLEN];
int len[MAXN];
int vis[mod+1],times[mod+1];

int check(int x)
{ 
	memset(vis,0,sizeof(vis));
	memset(times,0,sizeof(times));
	ll mul=1;
	for (int i=1;i<=x;i++) mul=(mul*p)%mod; 
	for (int i=1;i<=n;i++)
		for (int j=x;j<=len[i];j++)
		{
			ll nowhash=(hash[i][j]-(hash[i][j-x]*mul)%mod+mod)%mod;
			if (vis[nowhash]!=i)
			{
				times[nowhash]++;
				vis[nowhash]=i;
				if (times[nowhash]==n) return 1;
			}
		}
	return 0;
}

void init()
{
	minl=0x7fffffff;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%s",str);
		len[i]=strlen(str);
		if (len[i]<minl) minl=len[i];
		hash[i][1]=str[0]-'a'+1;
		
		for (int j=2;j<=len[i];j++)
			hash[i][j]=(hash[i][j-1]*p+(str[j-1]-'a'+1))%mod;
	}		
}

void search_ans()
{
	int lb=0,ub=minl+1;
	while (lb<ub)
	{
		int mid=(lb+ub)>>1;
		if (check(mid)) lb=mid+1;else ub=mid;
	}
	printf("%d",lb-1);
}

int main()
{
	init();
	search_ans();
	return 0;
}
