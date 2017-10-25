/*http://hihocoder.com/contest/hiho101/problem/1
搜索四·跳舞链
AC
G++
179ms
0MB
*/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<malloc.h>
#define M 105
#define N 105
using namespace std;
struct data{
	data *l,*r,*u,*d;
	int x,y;
}a[M],c[N*M];
data * b[N];
int n,m,ans[N],num;
bool s[N],f;
void charge(){
	for (int q=0;q<=m;q++){
		a[q].l=&a[q-1];
		a[q].r=&a[q+1];
		a[q].u=&a[q];
		a[q].d=&a[q];
		a[q].x=1;
		a[q].y=q;
	}
	a[0].l=&a[m];
	a[m].r=&a[0];
}
void remove(int i){
	data *p=&a[i],*q,*h;
	p->l->r=p->r;
	p->r->l=p->l;
	for (q=p->d;q!=p;q=q->d){
		for (h=q->r;h!=q;h=h->r){
			h->u->d=h->d;
			h->d->u=h->u;
		}
	}
}
void resume(int i){
	data *p=&a[i],*q,*h;
	p->l->r=p;
	p->r->l=p;
	for (q=p->d;q!=p;q=q->d){
		for (h=q->r;h!=q;h=h->r){
			h->u->d=h;
			h->d->u=h;
		}
	}
}
void dfs(int dep){
	data *p=a[0].r,*q,*h;
	if (p==&a[0]){
		f=true;
		return;
	}
	if (p->d==p||f){
		return;
	}
	remove(p->y);
	for (q=p->d;q!=p;q=q->d){
		ans[dep++]=q->x;
		for (h=q->r;h!=q;h=h->r){
			remove(h->y);
		}
		dfs(dep);
		//--dep;
		for (h=q->r;h!=q;h=h->r){
			resume(h->y);
		}
	}
	resume(p->y);
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
	scanf("%d%d",&n,&m);
	num=0;
	for(int q=1;q<=n;q++) s[q]=false;
	charge();
	data *temp;
	for (int q=1,i;q<=n;q++)
		for (int p=1;p<=m;p++){
			scanf("%d",&i);
			if (i==1){
				//temp=(struct data *)malloc(sizeof(data));
				temp=&c[num++];
				temp->x=q,temp->y=p;
				temp->u=a[p].u;
				temp->u->d=temp;
				a[p].u=temp;
				temp->d=&a[p];
				//列加入
				if(!s[q]){
					s[q]=true;
					temp->l=temp;
					temp->r=temp;
					b[q]=temp;
				}
				else {
					temp->l=b[q]->l;
					b[q]->l->r=temp;
					temp->r=b[q];
					b[q]->l=temp;
				}
				//行加入
			}
		}

	/*for (int q=1;q<=m;q++){
		for (data *p=b[q];p->r!=b[q];p=p->r)
			cout<<(p->x)<<","<<(p->y)<<"  ";
		cout<<endl;
	}*/
	f=false;
	dfs(0);
	if (f){
		printf("Yes\n");
	}
	else printf("No\n");
	}
	return 0;
}
