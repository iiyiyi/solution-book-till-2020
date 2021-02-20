#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAXN=1e5+5;
const int INF=2147483640;
pair<int,int> sum[MAXN];
int n,k,t;

void init()
{
	sum[0]=make_pair(0,0);
	int tmp=0;
	for (int i=1;i<=n;i++) 
	{
		int x;
		scanf("%d",&x);
		tmp+=x;
		sum[i]=make_pair(tmp,i);
	}
	sort(sum,sum+n+1); 	
}

void solve()
{
	scanf("%d",&t);
	int l=0,r=1,minans=INF,ans,ansl,ansr;
	while (r<=n && minans)//这里一开始写成了ans，以后变量名不要取那么相像orz 
	{
		int delta=sum[r].first-sum[l].first;
		if (abs(delta-t)<=minans)
		{
			minans=abs(delta-t);
			ans=delta;
			ansl=sum[l].second;
			ansr=sum[r].second;
		}
		if (delta<t) r++; 
		if (delta>t) l++;
		if (l==r) r++;//☆注意序列不能为空！
	}
	if (ansl>ansr) swap(ansl,ansr);//注意排序后是无序的，左右区间要调整回有序 
	printf("%d %d %d\n",ans,ansl+1,ansr); 
}

int main()
{
	while (scanf("%d%d",&n,&k)!=EOF) 
	{
		init();
		for (int i=1;i<=k;i++) solve();
	}
	return 0;
} 
