/* http://hihocoder.com/problemset/problem/1080*/
/*	345ms	11MB*/
/*算是lazy里挺神的入门题吧*/ 
#include<iostream>
#include<cstdio>
#define ID(l,r) (l+r|l!=r)//传说中的二倍空间线段树,又一个鸡肋…… 
#define N 100005 
#define LL long long
using namespace std;
LL a[N*2],mark[N*2],add[N*2],n;

void tr(int l,int r){
	if (l==r)	return ;
	int mid=(l+r)>>1;
	tr(l,mid);
	tr(mid+1,r);
	a[ID(l,r)]=a[ID(l,mid)]+a[ID(mid+1,r)];
}

void pushdown(int l,int r){
	if (l==r)	return ;
	int mid=(l+r)>>1;
	int fa=ID(l,r),lson=ID(l,mid),rson=ID(mid+1,r); 
	if (mark[fa]){
		mark[lson]=mark[rson]=mark[fa];
		add[lson]=add[rson]=0;
		a[lson]=mark[lson]*(mid-l+1);
		a[rson]=mark[rson]*(r-mid);
		mark[fa]=0;
	}
	if (add[fa]){
		add[lson]+=add[fa],add[rson]+=add[fa];
		a[lson]+=add[fa]*(mid-l+1);
		a[rson]+=add[fa]*(r-mid);
		add[fa]=0;
	}
}

void chg(int l,int r,int i,int j,int k,bool f){
	int mid=(l+r)>>1,fa=ID(l,r);
	if (l==i&&r==j){
		if (f)	mark[fa]=k,add[fa]=0,a[fa]=(r-l+1)*k;
		else add[fa]+=k,a[fa]+=(r-l+1)*k;
		return;
	}
	pushdown(l,r);
	if (mid<i){
		chg(mid+1,r,i,j,k,f);
	}
	else if (mid>=j){
		chg(l,mid,i,j,k,f);
	} 
	else {
		chg(l,mid,i,mid,k,f);chg(mid+1,r,mid+1,j,k,f);
	}
	a[fa]=a[ID(l,mid)]+a[ID(mid+1,r)];//push up
}

/*
LL find(int l,int r,int i,int j){
	int mid=(l+r)>>1;
	if (l==i&&r==j){
		return a[ID(l,r)];
	}
	pushdown(l,r);
	if (mid<i){
		return find(mid+1,r,i,j);
	}
	if (mid>=j){
		return find(l,mid,i,j);
	} 
	return find(l,mid,i,mid)+find(mid+1,r,mid+1,j);
}
*/

int main(){
	int m;
	scanf("%lld%lld",&n,&m);
	++n;
	for (int q=0;q<n;q++)	scanf("%lld",&a[q<<1]);
	tr(0,n-1);
	for (int q=0,i,j,k,f;q<m;q++){
		scanf("%d%d%d%d",&f,&i,&j,&k);
		chg(0,n-1,i,j,k,f);
		printf("%lld\n",a[ID(0,n-1)]);
	}
	return 0;
} 
