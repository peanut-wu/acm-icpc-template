#include<iostream>
#include<cstdio>
#include<algorithm>
#define MAX 100005 
using namespace std;
struct node{
	int num;//出现的次数 
	node *l;
	node *r;
}; 
node mem_poor[MAX*20],*tail;//内存池
node*root[MAX];//根
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
void built(int l,int r,node *t){
	int mid=(l+r)>>1;
	t->l=tail++,t->r=tail++;
	t->l->num=0,t->r->num=0;
	if (mid>l)	built(l,mid,t->l);
	if (r>mid+1)built(mid+1,r,t->r);
}
void add(int val,node *now,node *prev){
	int l=1,r=n_,mid;
	for (;;){
		mid=(l+r)>>1;
		if (val<=mid){
			now->r=prev->r;
			now->l=tail++;
			now=now->l,prev=prev->l;
			now->num=prev->num+1;
			r=mid;	 
		}
		else {
			now->l=prev->l;
			now->r=tail++;
			now=now->r,prev=prev->r;
			now->num=prev->num+1;
			l=mid+1;
		}
		if (l==r) break; 
	} 
}
void init(){
	tail=mem_poor;root[0]=tail++;
	for (int q=1;q<=n;q++){
		scanf("%d",&a[q].val);
		a[q].id=q;root[q]=tail++; 
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
	built(1,n_,root[0]);
	for (int q=1;q<=n;q++)
		add(a[q].val,root[q],root[q-1]);
} 
int find(node* i,node* j,int l,int r,int k){
/*	if (l==r) return l;
	int mid=(l+r)>>1,temp=(j->l->num)-(i->l->num);
	if (temp>=k)	return find(i->l,j->l,l,mid,k);
	else return find(i->r,j->r,mid+1,r,k-temp);*/
	int mid,temp;
	for (;;){
		if (l==r)	return l;
		mid=(l+r)>>1;temp=(j->l->num)-(i->l->num);
		if (temp>=k)	i=i->l,j=j->l,r=mid;
		else i=i->r,j=j->r,l=mid+1,k-=temp;
	}
}
int main(){
	cout<<sizeof(mem_poor)/1024<<endl;
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
