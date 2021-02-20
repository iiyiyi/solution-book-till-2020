#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=50000+50;
struct node
{
	int l,r; 
	bool operator < (const node &x) const
	{
		return (r<x.r);
	}
}cow[MAXN];
int n;

int main()
{
	scanf("%d",&n);
	for (int i=0;i<n;i++) scanf("%d%d",&cow[i].l,&cow[i].r);
	sort(cow,cow+n);
	int r=-1,ans=0;
	for (int i=0;i<n;i++)
	{
		if (cow[i].l>=r)
		{
			r=cow[i].r;
			ans++;
		}
	}
	cout<<ans<<endl;
	return 0;
}
