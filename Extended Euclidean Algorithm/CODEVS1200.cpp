#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

void extgcd(int a,int b,int &x,int &y)
{
	if (b==0)
	{
		x=0;y=1;
		return;
	}
	extgcd(b,a%b,x,y);
	int tmp=x;
	x=y;
	y=tmp-(a/b)*y;
}

int main()
{
	int a,b;
	scanf("%d%d",&a,&b);
	int x,y;
	extgcd(a,b,x,y);
	while (x<=0) x+=b;
	printf("%d",x);
	return 0;
} 
