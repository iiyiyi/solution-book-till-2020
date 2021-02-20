#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100000+50;
const double eps=1.0e-6;
int n,k,v[MAXN],w[MAXN];
int ansqueue[MAXN];
struct node
{
	double rem;
	int id;
	bool operator < (const node &x) const
	{
		return (rem>x.rem);
	}
};
node queue[MAXN];

int check(double x)
{
	for (int i=1;i<=n;i++) 
	{
		queue[i].rem=v[i]-x*w[i];
		queue[i].id=i;
	}
	sort(queue+1,queue+n+1);
	double sum=0;
	for (int i=1;i<=k;i++) sum+=queue[i].rem;
	if (sum>=0.0) return 1;
		else return 0;
}

void solve()
{
	for (int i=1;i<=n;i++) scanf("%d%d",&v[i],&w[i]);
	double lb=0.0,ub=0x3f3f3f3f;
	while (ub-lb>eps)
	{
		double mid=(lb+ub)/2;
		if (check(mid)) lb=mid;
			else ub=mid;
	}
	for (int i=1;i<=k;i++)
	{
		printf("%d",queue[i].id);
		if (i!=k) cout<<' ';
	}
	/*��ԭ����check(mid)=1֮������ansqueue��Ȼ�����������wa�ˡ�
	 Ȼ���ĳ�ֱ��������һ��check�����У����ܷ�����0����1����������Ϊʲô��*/ 
	cout<<endl;
}

int main()
{
	while (scanf("%d%d",&n,&k)!=EOF) solve();
	return 0;
}
