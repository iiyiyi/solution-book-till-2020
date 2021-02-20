#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath> 
#include<vector> 
using namespace std;
const int MAXN=70+5;
const int INF=0x7fffffff;
struct node
{
	int data,weight,frequency;
	bool operator < (const node& x) const
	{
		return data<x.data;
	}
}a[MAXN];
int n,K,hash[MAXN];
int f[MAXN][MAXN][MAXN];//f[i][j][w]由i~j组成的子树且每个点的权值都大于等于w的最小总代价 

void init()
{
	scanf("%d%d",&n,&K);
	for (int i=1;i<=n;i++) scanf("%d",&a[i].data); 
	for (int i=1;i<=n;i++) scanf("%d",&a[i].weight),hash[i]=a[i].weight; 
	for (int i=1;i<=n;i++) scanf("%d",&a[i].frequency);

	sort(hash+1,hash+n+1);
	sort(a+1,a+n+1);
	int d=unique(hash+1,hash+n+1)-(hash+1);
	for (int i=1;i<=n;i++)
	{
		a[i].weight=lower_bound(hash+1,hash+d+1,a[i].weight)-hash;
	}
	for (int i=2;i<=n;i++)
		a[i].frequency+=a[i-1].frequency;//求出前缀和
		
}

void dp()
{
	memset(f,0x3f,sizeof(f));
	for (int i=1;i<=n+1;i++)
		for (int w=0;w<=n;w++) f[i][i-1][w]=0;
	//这个初始化注意一下(!)，下方(i=k/j=k)时用到 
	for (int w=n;w;w--)//根据转移条件，显然w比较大的要先球出来，所以由大到小，放在最外层的循环 
		for (int i=n;i;i--)
			for (int j=i;j<=n;j++) 
				for (int k=i;k<=j;k++)
				{
					if (a[k].weight>=w) f[i][j][w]=min(f[i][j][w],f[i][k-1][a[k].weight]+f[k+1][j][a[k].weight]+(a[j].frequency-a[i-1].frequency));
					//因为新增根节点后，每个节点的深度都+1,所以要加上访问的频率和 
					//因为可以取实数，所以后面a[k].weight不需要+1，下面的w也是同理 
					f[i][j][w]=min(f[i][j][w],f[i][k-1][w]+f[k+1][j][w]+(a[j].frequency+K-a[i-1].frequency));
				}
	int ans=INF;
	for (int i=0;i<=n;i++)
		ans=min(ans,f[1][n][i]);
	printf("%d",ans); 
}

int main()
{
	init();
	dp();
	return 0; 
} 
