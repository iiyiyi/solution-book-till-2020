#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<bitset>
using namespace std;
const int MAXN=1000+50;
const int MAXM=2000+50;
bitset<MAXN> map[MAXM];
int n,m;
int times=-1;

void Gauss()
{
	for (int i=1;i<=n;i++)
	{
		int t=i;
		for (;t<=m && !map[t][i];t++);
		if (t>m) 
		{
			times=-1;//这里times要清成-1 
			return;
		}
		if (t!=i) swap(map[i],map[t]);
		times=max(times,t);
		for (int j=1;j<=m;j++) 
			if (i!=j && map[j][i])
				map[j]^=map[i];
	}
	
}

void init()
{
	scanf("%d%d",&n,&m);
	for (int i=0;i<m;i++)
	{
		char str[MAXN];
		int mapans;
		scanf("%s%d",str,&mapans);
		map[i+1][n+1]=mapans;
		for (int j=0;j<n;j++) map[i+1][j+1]=str[j]-'0';
	}
}

void print_ans()
{
	if (times==-1) cout<<"Cannot Determine"<<endl;
		else
		{
			printf("%d\n",times);
			for (int i=1;i<=n;i++)
				puts((map[i][n+1])?"?y7M#":"Earth");
		}
}

int main()
{
	init();
	Gauss();
	print_ans();
}
