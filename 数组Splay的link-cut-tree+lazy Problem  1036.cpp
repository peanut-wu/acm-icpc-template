/**************************************************************
    http://www.lydsy.com/JudgeOnline/problem.php?id=1036
    
	//其实这好像是一道链剖的题= = 
    
    link-cut-trer维护区间最值和权值和…… 
    
    Problem: 1036
    User: 597727533
    Language: C++
    Result: Accepted
    Time:4628 ms
    Memory:7100 kb
     
****************************************************************/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
#define flag(p)(p[parent][son][1]==p)
//#define NEW()(son[tail][0]=0,son[tail][1]=0,tail++)
#define swap(i,j)(i^=j,j^=i,i^=j)
//#pragma comment(linker, "/STACK:102400000,102400000")
#define MAX_N 100010
#define max(a,b)(a>b?a:b)
using namespace std;
int son[MAX_N][2],parent[MAX_N];//孩子 父亲
int val[MAX_N]; //值域 
int n,m;

/*以下是lazy及其函数*/ 
bool resv[MAX_N];
int sum[MAX_N],mmax[MAX_N]; 
inline void update(int p){//下方标记上传
	p[sum]=p[val],p[mmax]=p[val];
	if (p[son][0])	p[sum]+=p[son][0][sum],p[mmax]=max(p[mmax],p[son][0][mmax]);
	if (p[son][1])	p[sum]+=p[son][1][sum],p[mmax]=max(p[mmax],p[son][1][mmax]);
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
	int kk=f>0?flag(f):0;//父亲是左孩子还是右孩子 
	//p是左孩子 ：   p右边儿子变成父亲   p右孩子变成父亲左孩子   另一边对称
	pushdown(f);
	pushdown(p);//lct里这优化不能用……优化2 ，无论插入还是删除之前肯定都已经push过了 这里是没有必要的  但这个优化不总是对的 而且有题加入完tm变慢了 
	int k=flag(p);//左孩子还是右孩子 
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
void access(int p){//非递归  
	pushdown(p);//不能少 
	Splay(p);
	if (p[son][1]){
		p[son][1][parent]=-p;
		p[son][1]=0;//断开这条链以下的点 
		update(p);
	}
	while(p[parent]<0){
		int temp=-p[parent];
		pushdown(temp);//不能少 
		Splay(temp);
		if (temp[son][1]){
			temp[son][1][parent]=-temp;
		} 
		temp[son][1]=p,p[parent]=temp;
		update(temp);
		p=temp;
	} 
} 
void makeroot(int i){//翻转i到根的点，换i为根 
	access(i);
	Splay(i);
	i[resv]^=1;
}
vector<int>tr[MAX_N];
void init(int i,int fa){
	int siz=tr[i].size();
	for (int q=0;q<siz;++q)
		if (tr[i][q]!=fa){
			tr[i][q][parent]=-i;
			init(tr[i][q],i);
		}
	return ;
} 
int main(){
	scanf("%d",&n);
	for (int q=1,i,j;q<n;++q){
		scanf("%d%d",&i,&j);
		tr[i].push_back(j);
		tr[j].push_back(i);
	}
	init(1,-1);
	for (int q=1;q<=n;q++){
		scanf("%d",&val[q]);
		mmax[q]=sum[q]=val[q];
		son[q][0]=son[q][1]=0;
	}
	scanf("%d",&m);
	char s[20];
	for (int q=0,i,j;q<m;++q){
		scanf("%s",s);
		if (s[1]=='H'){
			scanf("%d%d",&i,&j);
			access(i);
			val[i]=j;
			update(i);
		}
		else if (s[1]=='M'){
			scanf("%d%d",&i,&j);
			makeroot(i);
			access(j);
			Splay(j);
			printf("%d\n",mmax[j]);
		}
		else {
			scanf("%d%d",&i,&j);
			makeroot(i);
			access(j);
			Splay(j);
			printf("%d\n",sum[j]);
		}
	}
	return 0;
}

