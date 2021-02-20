#include<bits/stdc++.h>
using namespace std;

int main()
{
	freopen("test.out","w",stdout);
	cout<<20<<endl;
	for (int t=1;t<=20;t++)
	{
		int m=rand()%10+1,n=rand()%10+1;
		cout<<m<<' '<<n<<endl;
		for (int i=1;i<=(2*n+1);i++) cout<<'#';cout<<endl;
		for (int i=1;i<=m;i++)
		{
			cout<<"# ";
			for (int j=1;j<n;j++)
			{
				int x=rand()%10;
				cout<<x<<' ';
			}
			cout<<"#"<<endl;
			if (i==m) break;
			cout<<'#';
			for (int j=1;j<=n;j++)
			{
				int x=rand()%10;
				cout<<x<<'#';
			}
			cout<<endl;
		}
		for (int i=1;i<=(2*n+1);i++) cout<<'#';cout<<endl;
	}
	return 0;
}
