/*http://acm.hdu.edu.cn/showproblem.php?pid=1754*/
/*懒得用树状数组花式修改了 还是用zkw线段树吧……当然其实分块最简单*/ 
#include<iostream>
#include<cstdio>
#define MAX 200005 
using namespace std;
int n,m,n_;
int a[MAX*8];
char s[4];
void tr(){
	for (int q=n_-1;q>0;--q)	a[q]=max(a[q<<1],a[(q<<1)|1]);
}
void chg(int i,int val){
	i+=n_,a[i]=val,i>>=1;
	for (;i;i>>=1)	a[i]=max(a[i<<1],a[(i<<1)|1]);
}
int find(int l,int r){
	int ans=0;
	l+=n_-1,r+=n_+1;
	for (;l^r^1;l>>=1,r>>=1){
		if (!(l&0x1))	ans=max(ans,a[l+1]);
		if (r&0x1)		ans=max(ans,a[r-1]); 
	}
	return ans;
}


void charge(){
	for (n_=1;n_<(n+2);n_<<=1);
	a[n_]=0;a[n_+n+1]=0;
	for (int q=n_+1;q<n_+1+n;++q)	scanf("%d",&a[q]);
	tr();
	for (int q=0,i,j;q<m;++q){
		scanf("%s%d%d",s,&i,&j);
		if (s[0]=='Q')	printf("%d\n",find(i,j));
		else chg(i,j);
	}
}
int main(){
	while (scanf("%d%d",&n,&m)!=EOF)	charge();
	return 0;
} 
