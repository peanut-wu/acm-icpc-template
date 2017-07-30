/*http://acm.hdu.edu.cn/showproblem.php?pid=3183*/
/*普通贪心，求区间最小值，ST表相较于线段树和分块 查询最多优化至O（1）空间消耗大预处理耗时高 鸡肋 不如不学*/ 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define MAX 1012
using namespace std;
char a[MAX];
int m,n,dp[MAX][10],pos[MAX][10];
const double LOG=log(2);
void init(){
	n=strlen(a);
	for (int q=0;q<n;++q)	dp[q][0]=a[q],pos[q][0]=q;
	for (int p=1,val=2;val<=n;++p,val<<=1)
		for (int q=0;q+val<=n;++q)
			if (dp[q][p-1]<=dp[q+(val>>1)][p-1])
				dp[q][p]=dp[q][p-1],pos[q][p]=pos[q][p-1];
			else dp[q][p]=dp[q+(val>>1)][p-1],pos[q][p]=pos[q+(val>>1)][p-1];
}
void find(int l,int r,int &ans,int &p){
	int val=2,le=0;
	for (;val<=(r-l+1);val<<=1,++le);
	if (dp[l][le]<=dp[r-(1<<le)+1][le])
		ans=dp[l][le],p=pos[l][le];
	else ans=dp[r-(1<<le)+1][le],p=pos[r-(1<<le)+1][le];
}

void charge(){
	init();
	bool flag=false;
	int l=0;
	for (int q=n-m-1,i,ipos;q>=0;--q){
		find(l,n-1-q,i,ipos);
		if (a[ipos]=='0'){
			if (flag)	cout<<"0";
		}	
		else {
			flag=true;
			cout<<a[ipos];
		}
		l=ipos+1;
	}
	if (!flag)cout<<"0";
	cout<<endl;
}
int main(){
	cin.sync_with_stdio(false);cout.sync_with_stdio(false);
	while (cin>>a>>m)	charge(); 

	return 0;
}
