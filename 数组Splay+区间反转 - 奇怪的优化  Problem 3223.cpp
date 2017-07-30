/**************************************************************
	http://www.lydsy.com/JudgeOnline/problem.php?id=3223
    Problem: 3223
    User: 597727533
    Language: C++
    Result: Accepted
    Time:2712 ms
    Memory:3344 kb
    Ps:大概用结构体可以快一点点 指针版又可以快一点点  然而并没有什么卵用 速度和块链基本一个级别、、、、、 
    
    
    选择加入了一些奇怪的优化： 
	 
	 1.在 rotate 过程中不 update 当前节点。显然，只需要在 splay 到根之后 update 即可。
	 2.在 rotate 过程中不需要下放标记。显然，在找到点之前，就一定会有自上而下的过程。在这里下放标记即可。
     3.尽量使用自己 define 的 max，swap 之类的为所用很多的函数，大数据下稍有改变即可快 0.2 秒。
     4.插入之后 splay 所插入的最低深度的点。如果将一条链 splay 成四分之一以下的深度，常数将巨大优化。
    
    在lazy操作不多时 用处不大 
     
****************************************************************/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#define flag(p)(p[parent][son][1]==p)
#define NEW()(son[tail][0]=0,son[tail][1]=0,tail++)
#define swap(i,j)(i^=j,j^=i,i^=j)
//#define FREE(i)(i)
//#pragma comment(linker, "/STACK:102400000,102400000")
#define MAX_N 100010
using namespace std;
int son[MAX_N][2],parent[MAX_N];//孩子 父亲
int val[MAX_N]; 
int size[MAX_N];//子节点个数 
bool resv[MAX_N];//反转标记 
int root,tail,n,m;
inline void update(int p){//下方标记上传
	p[size]=1;
	if (p[son][0]) p[size]+=p[son][0][size];
	if (p[son][1]) p[size]+=p[son][1][size];
} 
inline void pushdown(int p){//标记下放 
	if (resv[p]){
		swap(p[son][0],p[son][1]);
		p[son][0][resv]^=1,p[son][1][resv]^=1;
		p[resv]=0; 
	} 
}
void rotate(int p){
	int f=p[parent];//父亲 
	int g=f[parent];//父亲的父亲
	int kk=g>0?flag(f):0;//父亲是左孩子还是右孩子 
	//p是左孩子 ：   p右边儿子变成父亲   p右孩子变成父亲左孩子   另一边对称
	/*pushdown(f);
	pushdown(p);*///优化2 ，无论插入还是删除之前肯定都已经push过了 这里是没有必要的  但这个优化不总是对的（如果没有Splay的话） 而且加入完tm变慢了 
	int k=flag(p);//左孩子还是右孩子 反转完孩子可能变了 所以要在后面 
	int c=p[son][k^1];
	if (c) c[parent]=f;f[son][k]=c;
	p[son][k^1]=f,f[parent]=p;
	p[parent]=g;   if (g>0)	g[son][kk]=p; //<=0的都是非法点   g用<0是为了和Link-cut-tree写法统一 
	update(f);
//	update(p);    //优化1 改到69行 显然保证了正确性  
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
	update(p); //优化1，新加上去的 
	if (fa==0) root=p;
	//如果在一条直线,就转爸爸,然后转自己;否则转两次自己 
} 
int insert(int p,int i){
	pushdown(p);//优化2 本来就有的 
	Splay(p,0);		
	int q;
	if (p[val]>i){
		if (p[son][0]==0){
			p[son][0]=q=NEW();
			q[parent]=p,q[val]=i,q[size]=1;
			//插入新节点 更新信息 
			return q;
		}
		else q=insert(p[son][0],i);
	}
	else {
		if (p[son][1]==0){
			int q;
			p[son][1]=q=NEW();
			q[parent]=p,q[val]=i,q[size]=1; 
			//插入新节点 更新信息 
			return q;
		}
		else q=insert(p[son][1],i);
	}
	update(p);
	return q;
}

int find(int p,int i){
	for (;;){
		pushdown(p);//优化2 本来就有的 
		int siz=(p[son][0]==0?0:p[son][0][size]);
		if (siz==i-1)	return p;
		else if (siz>=i) p=p[son][0];
		else p=p[son][1],i=i-siz-1;
	}
} 
void Q(int l,int r){
	++l,++r;
	--l,++r;
	int aa=find(root,l);
	Splay(aa,0);
	int bb=find(root,r);
	Splay(bb,0);
	Splay(aa,0);Splay(bb,aa);
	bb[son][0][resv]^=1;
}

int build(int l,int r){
	if (l>r)	return 0;
	if (l==r){
		int q=NEW();
		q[val]=l;
		q[size]=1;
		return q;
	}
	int mid=(l+r)>>1;
	int q=NEW();
	val[q]=mid;
	int lson=build(l,mid-1),rson=build(mid+1,r);
	lson[parent]=q,rson[parent]=q;
	q[son][0]=lson,q[son][1]=rson;
	update(q);
	return q;
}
void init(){
	scanf("%d%d",&n,&m);
	tail=1;
	root=build(1,n+1);
	insert(root,-1);
}
void show(int i){
	pushdown(i);
	if (i==0) return ;
	show(i[son][0]);
	if (i[val]!=-1&&i[val]!=n+1) printf("%d ",i[val]);
	show(i[son][1]);
}
int main(){
	init();//cout<<"aaa"<<root[val]<<" "<<root[size]<<" "<<root[son][0][son][0][size]<<endl;
	for (int q=0,aa,bb,cc,dd;q<m;q++){
		scanf("%d%d",&aa,&bb);
		Q(aa,bb); 
	//	show(root);cout<<endl;
	}
	show(root);
	return 0;
}
