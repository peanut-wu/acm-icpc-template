/*http://acm.fzu.edu.cn/problem.php?pid=1608*/ 
/*大概是BIT差分求和再求和 先用分块水过吧 有空再补正常解法*/ 
/*神tm题意*/ 
/*fzu炸了 还没跑过*/ 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define NMAX 50005
#define MMAX 500005
#define lowbit (i&-i) 
using namespace std;
int n,m,a[NMAX],c[300],SQRT;
struct Q{
	int i,j,k;
	friend bool operator <(const struct Q &aa,const struct Q &bb){
		return aa.k<bb.k;
	}
}b[MMAX];
void chg(int i,int j,int k){
	if (i/SQRT==j/SQRT){
		for (int q=i;q<=j;++q)
			a[q]=k;
	}
	else {
		for (int q=i;q<(i/SQRT+1)*SQRT;++q)	a[q]=k;
		for (int q=i/SQRT+1;q<j/SQRT;++q)	c[q]=k;
		for (int q=j/SQRT*SQRT;q<=j;++q)	a[q]=k;
	}
	if (c[i/SQRT]!=-1){
		for (int q=i/SQRT*SQRT;q<i;++q)
			a[q]=c[i/SQRT];
	}
	if (c[j/SQRT]!=-1){
		for (int q=j+1;q<(j/SQRT+1)*SQRT;++q)
			a[q]=c[j/SQRT];
	}
	c[i/SQRT]=-1;c[j/SQRT]=-1;
}
void charge(){
	for (int q=0;q<m;q++)
		scanf("%d%d%d",&b[q].i,&b[q].j,&b[q].k);
	sort(b,b+m,less<Q>());
	memset(c,0,sizeof(c));
	++n;
	SQRT=sqrt(n*1.0);
	for (int q=0;q<m;q++){
		chg(b[q].i,b[q].j-1,b[q].k);
	}
	int ans=0;
	for (int q=0;q<=(n-1)/SQRT;q++){
		if (c[q]==-1)
			for (int p=q*SQRT;p<min(q*SQRT+SQRT,n);++p)
				ans+=a[p];
		else ans+=(min(q*SQRT+SQRT,n)-q*SQRT)*c[q];
	}
	printf("%d\n",ans);
}
int main(){
	while (scanf("%d%d",&n,&m)!=EOF)	charge();
	return 0;
} 
