#include<bits/stdc++.h>

int main()
{
	freopen("test.out","w",stdout);
	for (int i=1;i<=20;i++)
	{
		int n=rand()%98+2;
		printf("%d\n",n);
		for (int j=1;j<=n;j++)
		{
			int x=rand()%2001-1000,y=rand()%2001-1000;
			printf("%d %d ",x,y);
			x=rand()%2001-1000,y=rand()%2001-1000;
			printf("%d %d\n",x,y);
		}
	}
	return 0;
}
