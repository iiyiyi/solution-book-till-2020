#include<iostream> 
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=1000+5;
double f[MAXN],g[MAXN],p,q;

void solve()
{
	int n;
	scanf("%d",&n);
	n=min(n,1000);
	//����n�ܴ��ʱ�򣬸��ʼ������ٷ����ı䣬��ֻ��Ҫȡ��1000�н�С�ļ��� 
    scanf("%lf%lf",&p,&q); 
    f[0]=0,g[0]=1;
    for(int i=1;i<=n;i++)
    {
        if(f[i-1]>g[i-1])p=1-p,q=1-q;
        //����p��q��ʾ�ĺ��������ⲻͬ������Ϊ��ǰͶ�������泯������ĸ���
		//�����ʣi-1��ʯͷʱ��A���ָ����������ڻ���i��ʯͷ��ʱ��Aϣ��B�õ���ǰʯͷ��BҲϣ��A�õ����ʾ�ϣ���������ϡ�
		//��������£����泯�ϵĸ��ʾ���1-p/1-q 
		//�����ʣi-1��ʯͷʱ��A���ָ��������������˶�ϣ���Լ���ѡ�����泯�ϵĸ��ʾ���p/q 
        f[i]=(p*g[i-1]+(1-p)*q*f[i-1])/(1-(1-p)*(1-q));
        g[i]=(q*f[i-1]+(1-q)*p*g[i-1])/(1-(1-p)*(1-q));
        if(f[i-1]>g[i-1])p=1-p,q=1-q;
    }
	printf("%.6lf\n",f[n]);
}

int main()
{
	int T;
    scanf("%d",&T);
    while (T--) solve();
    return 0;
}
