/*
Problem : 2665 ( Kth number )     Judge Status : Accepted
RunId : 22327560    Language : G++    Author : wrongnumber
Code Render Status : Rendered By HDOJ G++ Code Render Version 0.01 Beta
区间第k大
http://acm.split.hdu.edu.cn/showproblem.php?pid=2665
*/
#include<bits/stdc++.h>
#define MAX 100005
using namespace std;
struct node{
	int num;//出现的次数
	int l,r;
}pool[MAX*20];//内存池
int tail;//内存池指针
int new_node(){
    pool[tail].num=pool[tail].l=pool[tail].r=0;
    return tail++;
}

int root[MAX];//根


int rnk[MAX],n_;//离散化后反映射
struct data{
	int id,val;
}a[MAX];



int n,m;
bool c1(const data &a,const data &b){
	return a.id<b.id;
}
bool c2(const data &a,const data &b){
	return a.val<b.val;
}

void built(int l,int r,int t){
	int mid=(l+r)>>1;
	pool[t].l=new_node();
	pool[t].r=new_node();
	if (mid>l)	built(l,mid,pool[t].l);
	if (r>mid+1)built(mid+1,r,pool[t].r);
}

void add(int val,int now,int prev){
	int l=1,r=n_,mid;
	for (;;){
		mid=(l+r)>>1;
		if (val<=mid){
			pool[now].r=pool[prev].r;
            pool[now].l=new_node();
			now=pool[now].l,prev=pool[prev].l;
			pool[now].num=pool[prev].num+1;
			r=mid;
		}
		else {
			pool[now].l=pool[prev].l;
            pool[now].r=new_node();
			now=pool[now].r,prev=pool[prev].r;
			pool[now].num=pool[prev].num+1;
			l=mid+1;
		}
		if (l==r) break;
	}
}
void init(){
	for (int q=1;q<=n;q++){
		scanf("%d",&a[q].val);
		a[q].id=q;
	}
	sort(a+1,a+n+1,c2);
	n_=1;
	for (int q=1;q<=n;q++){//离散化
		for(;q<=n&&a[q].val==a[q+1].val;){
			a[q].val=n_;
			q++;
		}
		rnk[n_]=a[q].val;
		a[q].val=n_++;
	}
	sort(a+1,a+n+1,c1);

	tail=1;
	for (int q=0;q<=n;++q){
        root[q]=new_node();
	}
	built(1,n_,root[0]);
	for (int q=1;q<=n;q++)
		add(a[q].val,root[q],root[q-1]);
}
int find(int i,int j,int l,int r,int k){
/*	if (l==r) return l;
	int mid=(l+r)>>1,temp=(j->l->num)-(i->l->num);
	if (temp>=k)	return find(i->l,j->l,l,mid,k);
	else return find(i->r,j->r,mid+1,r,k-temp);*/
	int mid,temp;
	for (;;){
		if (l==r)	return l;
		mid=(l+r)>>1;
		temp=(pool[pool[j].l].num)-(pool[pool[i].l].num);
		if (temp>=k)	i=pool[i].l,j=pool[j].l,r=mid;
		else i=pool[i].r,j=pool[j].r,l=mid+1,k-=temp;
	}
}
int main(){
	int T;
	scanf("%d",&T);
	while (T--){
		scanf("%d%d",&n,&m);
		init();
		int i,j,k;
		while (m--){
			scanf("%d%d%d",&i,&j,&k);
			printf("%d\n",rnk[find(root[i-1],root[j],1,n_,k)]);
		}
	}
}
