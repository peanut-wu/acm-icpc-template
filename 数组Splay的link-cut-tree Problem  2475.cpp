/**************************************************************
    http://acm.hdu.edu.cn/viewcode.php?rid=19855081
	
	Problem : 2475 ( Box )     Judge Status : Accepted
	RunId : 19855081    Language : G++    Author : sfdarg
	Code Render Status : Rendered By HDOJ G++ Code Render Version 0.01 Beta
    
    link-cut-trer初探…… 
     
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
int val[MAX_N]; //值域 
int n,m;
/*以下是lazy及其函数*/ 
//int size[MAX_N];//子节点个数 
//bool resv[MAX_N];//反转标记 
inline void update(int p){//下方标记上传
/*	p[size]=1;
	if (p[son][0]) p[size]+=p[son][0][size];
	if (p[son][1]) p[size]+=p[son][1][size];*/
} 
inline void pushdown(int p){//标记下放 
/*	if (resv[p]){
		swap(p[son][0],p[son][1]);
		p[son][0][resv]^=1,p[son][1][resv]^=1;
		p[resv]=0; 
	} */
	
}

void rotate(int p){
	int k=flag(p);//左孩子还是右孩子 
	int f=p[parent];//父亲 
	int g=f[parent];//父亲的父亲
	int kk=f>0?flag(f):0;//父亲是左孩子还是右孩子 
	//p是左孩子 ：   p右边儿子变成父亲   p右孩子变成父亲左孩子   另一边对称
	/*pushdown(f);
	pushdown(p);*///优化2 ，无论插入还是删除之前肯定都已经push过了 这里是没有必要的  但这个优化不总是对的（如果没有Splay的话） 而且加入完tm变慢了 
	int c=p[son][k^1];
	if (c) c[parent]=f;f[son][k]=c;
	p[son][k^1]=f,f[parent]=p;
	p[parent]=g;   if (g>0)	g[son][kk]=p; //<=0的都是非法点   g用<0是为了和Link-cut-tree写法统一 
	// 至于为什么用 g > 0，主要是为了后面写 Link/cut tree 时方便
	//因为我们可以在 parent 里存一个负的值来表示这个不是一个偏好边（preferred edge）。这样，我们就不用再特别维护一个path_parent 数组了，
	update(f);
//	update(p);    //优化1 改到69行 显然保证了正确性  
}
void Splay(int p){	
	for (;p[parent]>0;rotate(p)){
		if (p[parent][parent]>0){
			if (flag(p)==flag(p[parent])) 
				rotate(p[parent]);
			else rotate(p);
		}
	}
	update(p); //优化1，新加上去的 
	//如果在一条直线,就转爸爸,然后转自己;否则转两次自己 
} 
/*void access(int p){//递归版本 
	Splay(p);
	if (p[son][1]){
		p[son][1][parent]=-p;
		p[son][1]=0;//断开p这条链条以下的点
	}
	if (p[parent]<0){ 
		access(-p[parent]);
		p[parent]=-p[parent];
		p[parent][son][1]=p;
		rotate(p); 
	} 
}*/ 
void access(int p){//非递归 
	Splay(p);
	if (p[son][1]){
		p[son][1][parent]=-p;
		p[son][1]=0;//断开这条链以下的点 
	}
	while(p[parent]<0){
		int temp=-p[parent];
		Splay(temp);
		if (temp[son][1]){
			temp[son][1][parent]=-temp;
		} 
		temp[son][1]=p,p[parent]=temp;
		Splay(p);
	} 
} 
void init(){
	for (int q=1,i;q<=n;q++){
		scanf("%d",&i);
		q[son][0]=q[son][1]=0;
		q[parent]=-i;
	}
}
void move(int i,int j){//i连向j 
	if (i==j)	return ;
	if (j){//排除j连向i的非法状况 
		access(j);
		access(i);
		Splay(j);
		if (j[parent]==-i) return ; 
	} 
	Splay(i);
	int prev=i[son][0];
	if(prev){//断开了链上面的 
		while (prev[son][1]) 	prev=prev[son][1];
		access(prev);
	}
	if (j){
		access(j);
		if (j[son][1]){
			j[son][1][parent]=-j;
			j[son][1]=0;
		} 
		j[son][1]=i;
	}
	i[parent]=j;
	
}
int Q(int i){
	access(i);
	while (i[son][0]) i=i[son][0];
	return i;
}
int main(){
	char s[12];
	bool flag=false;
	while (scanf("%d",&n)!=EOF){
		init();
		if (flag)	printf("\n");
		scanf("%d",&m);
		for (int q=0,i,j;q<m;q++){
			scanf("%s",s);
			if (s[0]=='M'){
				scanf("%d%d",&i,&j);move(i,j);
			}
			else {
				scanf("%d",&i);printf("%d\n",Q(i));
			}
		}
		flag=true;
	} 
	return 0;
}
