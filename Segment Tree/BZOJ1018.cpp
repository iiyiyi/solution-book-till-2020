#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
using namespace std;
struct LK
{
	int a[6];//�ֱ��ʾ�������ϣ��������£��������£��������£��������£��������� 
}link[MAXN<<2],s[2];
int c,x1,y1,x2,y2; 

void build(int rt,int l,int r)
{
	if (l==r) 
	{
		link[rt]=s[0];
		return;
	}
	int m=(l+r)>>1;
	build(lson);
	build(rson);
}

void change(int x1,int y1,int x2,int y2,int c,int l,int r,int rt)
{
	int m=(l+r)>>1,y=min(y1,y2);
	if (x1==x2 && y==mid)
}

void init()
{
	scanf("%d",&c);
	s[0]=(LK){1,1,0,0,0,0};//������һ�е�ʱ��ֻ���������ϡ�������������ͨ�ģ���Ϊ��һ���㣩 
	s[1]=(LK){1,1,1,1,1,1};
	build(1,1,n);
}

void solve()
{
	char str[4],;
	while (~scanf("%s",str))
	{
		if (str[0]=='E') return;
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		x1--,x2--;
		if (str[0]=='O') change(x1,y1,x2,y2,1,1,n,1);
		if (str[0]=='C') change(x1,y1,x2,y2,0,1,n,1);
		if (str[0]=='A') query(x1,y1,x2,y2);
	}
} 

int main()
{
	init(); 
	solve();
} 
