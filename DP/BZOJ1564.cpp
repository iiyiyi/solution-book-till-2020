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
int f[MAXN][MAXN][MAXN];//f[i][j][w]��i~j��ɵ�������ÿ�����Ȩֵ�����ڵ���w����С�ܴ��� 

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
		a[i].frequency+=a[i-1].frequency;//���ǰ׺��
		
}

void dp()
{
	memset(f,0x3f,sizeof(f));
	for (int i=1;i<=n+1;i++)
		for (int w=0;w<=n;w++) f[i][i-1][w]=0;
	//�����ʼ��ע��һ��(!)���·�(i=k/j=k)ʱ�õ� 
	for (int w=n;w;w--)//����ת����������Ȼw�Ƚϴ��Ҫ��������������ɴ�С������������ѭ�� 
		for (int i=n;i;i--)
			for (int j=i;j<=n;j++) 
				for (int k=i;k<=j;k++)
				{
					if (a[k].weight>=w) f[i][j][w]=min(f[i][j][w],f[i][k-1][a[k].weight]+f[k+1][j][a[k].weight]+(a[j].frequency-a[i-1].frequency));
					//��Ϊ�������ڵ��ÿ���ڵ����ȶ�+1,����Ҫ���Ϸ��ʵ�Ƶ�ʺ� 
					//��Ϊ����ȡʵ�������Ժ���a[k].weight����Ҫ+1�������wҲ��ͬ�� 
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
