#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int MAXN=512;
const int MAXK=100;
const int MAXM=15;
int n,m;
int map[MAXN][MAXN];
ll f[MAXM][MAXK][MAXN];//f[i][j][k]��i�У�����ȥj����������ǰ��״̬Ϊk 
int usable[MAXN];
int digit[MAXN];

int Usable(int x)
{
	if (x<<1&x || x>>1&x) return 0;else return 1;
	//���������ڵ�1 
}

int get_digit(int x)
{
	int ret=0;
	while (x) ret+=x&1,x>>=1;
	return ret;
}

int Judge(int x,int y)
{
	if (x&y || (x<<1)&y || (x>>1)&y) return 0;else return 1;
	/*�����е����������*/ 
}

void init()
{
	memset(usable,0,sizeof(usable));
	memset(map,0,sizeof(map));
	for (int i=0;i<1<<n;i++)
		if (Usable(i)) usable[++usable[0]]=i;
	/*Ԥ������е�״̬�����Ҳ��������ڵ�1��*/ 
	for (int i=1;i<=usable[0];i++)
		for (int j=1;j<=usable[0];j++)
		{ 
			if (Judge(usable[i],usable[j])) map[i][j]=1;
		} 
	/*Ԥ������е�״̬���ܹ�ת����״̬*/
	for (int i=1;i<=usable[0];i++) digit[i]=get_digit(usable[i]);
	/*Ԥ����ÿһ������״̬��1�ĸ���*/
}

ll dp()
{
	memset(f,0,sizeof(f));
	f[0][0][1]=1;
	for (int i=1;i<=n;i++)
		for (int j=0;j<=m;j++)
			for (int k=1;k<=usable[0];k++)
				if (digit[k]<=j)
				{
					for (int l=1;l<=usable[0];l++)
					{
						if (map[l][k] && digit[l]+digit[k]<=j) 
							f[i][j][k]+=f[i-1][j-digit[k]][l];
					}
				}
	ll ret=0;
	for (int i=1;i<=usable[0];i++) ret+=f[n][m][i];
	return ret;
}

int main()
{
	scanf("%d%d",&n,&m);
	init();
	cout<<dp()<<endl;
	return 0;	
} 
