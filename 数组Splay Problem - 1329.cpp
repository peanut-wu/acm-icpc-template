/* http://hihocoder.com/problemset/problem/1329
	��ָ��汾����  ��ͬС��  Splay��rotate�о�д�������һ��
	 699ms	19MB	
*/ 
#include<iostream>
#include<cstdio>
#define flag(p)(p[parent][son][1]==p)
//#define NEW()(son[tail][0]=0,son[tail][1]=0,tail++)
//#define FREE(i)(i)
#define MAX_N 1000010
using namespace std;
int son[MAX_N][2],parent[MAX_N];//���� ����
int val[MAX_N]; 
int stack[MAX_N],top;//ջ 
int root,tail;
inline int NEW(){
	int i=top?stack[--top]:tail++;
	son[i][0]=son[i][1]=0;
	return i;
}
inline void FREE(int i){
	stack[top++]=i;
} 
void rotate(int p){
	int k=flag(p);//���ӻ����Һ��� 
	int f=p[parent];//���� 
	int g=f[parent];//���׵ĸ���
	int kk=f>0?flag(f):0;//���������ӻ����Һ��� 
	//p������ ��   p�ұ߶��ӱ�ɸ���   p�Һ��ӱ�ɸ�������   ��һ�߶Գ�
	int c=p[son][k^1];
	if (c) c[parent]=f;f[son][k]=c;
	p[son][k^1]=f,f[parent]=p;
	p[parent]=g;   if (g>0)	g[son][kk]=p; //<=0�Ķ��ǷǷ���   g��<0��Ϊ�˺�Link-cut-treeд��ͳһ 
}
void Splay(int p,int fa){	
	for (;p[parent]!=fa;rotate(p)){
		if (p[parent][parent]==fa){
			rotate(p); break;
		}
		if (flag(p)==flag(p[parent])) 
			rotate(p[parent]);
		else rotate(p);
	}
	if (fa==0) root=p;
	//�����һ��ֱ��,��ת�ְ�,Ȼ��ת�Լ�;����ת�����Լ� 
} 
int insert(int i){
	int p=root,f,q;
	for (;;){
		f=p;
		if (val[p]>i){
			p=p[son][0];
			if (p==0){
				f[son][0]=q=NEW();
				break;
			}
		} 
		else{
			p=p[son][1];
			if (p==0){
				f[son][1]=q=NEW();
				break;
			}
		}
	}
	q[parent]=f,q[val]=i;
	Splay(q,0);
	return q;
}

int find(int i){
	int p=root;
	for (;p!=0;){
		if (val[p]==i){
			Splay(p,0);
			return p;
		}
		if (val[p]>i) p=son[p][0];
		else p=son[p][1];
	}
	return -1;
} 
void delet(int i){
	int q=find(i);
	if (q==-1) return ;
	int l=q[son][0],r=q[son][1];
	while (l[son][1]!=0) l=l[son][1];
	while (r[son][0]!=0) r=r[son][0];
	Splay(l,0); Splay(r,l);	
	FREE(r[son][0]);
	r[son][0]=0;
}
void init(){
	root=1,val[1]=1000000002,root[parent]=0,root[son][1]=0,root[son][2]=0;
	tail=2;
	top=0;
	insert(-1);
}
int Q(int k){//������k���������
	int q=find(k);
	if (q>0)	return k;
	insert(k); 
	int s=root[son][0];
	while (s[son][1]!=0) s=s[son][1];
	delet(k);
	return s[val];	
}
void D(int a,int b){
	bool f1=false,f2=false;
	--a,++b;
	int l=find(a),r=find(b);
	if (l==-1){
		f1=true;insert(a);l=find(a);
	}
	if (r==-1){
		f2=true;insert(b);r=find(b);
	}
	Splay(l,0);
	Splay(r,l);
	r[son][0]=0;
	if (f1==true) delet(a);
	if (f2==true) delet(b);
}
/*void show(int i){
	if (!i) return ;
	show(i[son][0]);
	cout<<i[val]<<" ";
	show(i[son][1]);
}*/
int main(){
	cin.sync_with_stdio(false);cout.sync_with_stdio(false);
	int n;
	init();
	cin>>n;
	char i;
	int k,kk;
	for (int q=0;q<n;q++){
		cin>>i;
		if (i=='I'){
			cin>>k;
			insert(k);	
		}
		else if (i=='Q'){
			cin>>k;
			cout<<Q(k)<<endl; 
			} 
		else {
			cin>>k>>kk;
			D(k,kk);
		}
	//	show(root);
	//	cout<<endl<<find(k)<<" "<<val[find(k)]<<endl;
	}
	return 0;
}
