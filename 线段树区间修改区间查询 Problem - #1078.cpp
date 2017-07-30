/* http://hihocoder.com/problemset/problem/1078*/
/*fzu炸了  用另一题代替*/
#include<iostream>
#include<cstdio>
#define ID(l,r) (l+r|l!=r)//传说中的二倍空间线段树,又一个鸡肋…… 
#define N 100005 
#define LL long long
using namespace std;
LL a[N*2],mark[N*2],n;

void tr(int l,int r){
	if (l==r)	return ;
	int mid=(l+r)>>1;
	tr(l,mid);
	tr(mid+1,r);
	a[ID(l,r)]=a[ID(l,mid)]+a[ID(mid+1,r)];
}

void pushdown(int l,int r){
	int mid=(l+r)>>1; 
	if (mark[ID(l,r)]){
		mark[ID(l,mid)]=mark[ID(mid+1,r)]=mark[ID(l,r)];
		a[ID(l,mid)]=mark[ID(l,mid)]*(mid-l+1);
		a[ID(mid+1,r)]=mark[ID(mid+1,r)]*(r-mid);
		mark[ID(l,r)]=0;
	}
}

void chg(int l,int r,int i,int j,int k){
	int mid=(l+r)>>1;
	if (l==i&&r==j){
		mark[ID(l,r)]=k;
		a[ID(l,r)]=(r-l+1)*k;
		return;
	}
	pushdown(l,r);
	if (mid<i){
		chg(mid+1,r,i,j,k);
	}
	else if (mid>=j){
		chg(l,mid,i,j,k);
	} 
	else {
		chg(l,mid,i,mid,k);chg(mid+1,r,mid+1,j,k);
	}
	a[ID(l,r)]=a[ID(l,mid)]+a[ID(mid+1,r)];//push up
}
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
int main(){
	scanf("%d",&n);
	for (int q=0;q<n;q++)	scanf("%lld",&a[q<<1]);
	tr(0,n-1);
	int m;
	scanf("%d",&m);
	for (int q=0,i,j,k,f;q<m;q++){
		scanf("%d",&f);
		if (f){
			scanf("%d%d%d",&i,&j,&k);
			chg(0,n-1,i-1,j-1,k);
		}
		else {
			scanf("%d%d",&i,&j);
			printf("%lld\n",find(0,n-1,i-1,j-1));
		}
	}
	return 0;
} 
