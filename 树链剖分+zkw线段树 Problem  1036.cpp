/*
  http://www.lydsy.com/JudgeOnline/problem.php?id=1036
	维护区间最值和权值和…… 
    Problem: 1036
    User: 597727533
    Language: C++
    Result: Accepted
    Time:2288 ms
    Memory:8568 kb
	丧心病狂！代码量和lct差不多就算了  速度竟然也只差一倍……可怕
	虽然懒得分类两个询问一起求了…… 但这速度也是没谁了…… 
*/
#include<iostream>
#include<cstdio>
#include<vector> 
#define LL int
#define MAX 100010
#define swap(a,b)(a^=b,b^=a,a^=b) 
#define max(a,b)(a>b?a:b)
using namespace std;
int n,m,Q;
LL val[MAX];//点权值 
vector<int>b[MAX];//存图 
int siz[MAX];//用来保存以x为根的子树节点个数
int top[MAX];//用来保存当前节点的所在链的顶端节点
int son[MAX];//用来保存重儿子
int dep[MAX];//用来保存当前节点的深度
int fa[MAX];//用来保存当前节点的父亲
int tid[MAX],tim=0;//用来保存树中每个节点剖分后的新编号
int rnk[MAX];//用来保存当前节点在线段树中的位置，也就是tid的反函数…… 


int sum[MAX],mmax[MAX],n_;
void dfs1(int i,int father,int d){
	//第一轮dfs 求出深度、节点子树节点数目、节点重儿子，节点父亲 
	dep[i]=d;
	fa[i]=father;
	siz[i]=1;
	son[i]=-1; 
	int l=b[i].size(); 
	for (int q=0;q<l;q++)
		if (b[i][q]!=father){
			dfs1(b[i][q],i,d+1);
			siz[i]+=siz[b[i][q]];
			if (son[i]==-1 || siz[son[i]]<siz[b[i][q]])
				son[i]=b[i][q]; 
		} 
} 
void dfs2(int i,int father,int tp){
	//第二轮dfs 求出i所在重链的顶端结点，重新编号及反映射.
	top[i]=tp;
	tid[i]=tim++;
	rnk[tid[i]]=i; 
	if (son[i]==-1) return ;
	dfs2(son[i],i,tp);
	int l=b[i].size();
	for (int q=0;q<l;q++)
		if (b[i][q]!=father){
			if (son[i]!=b[i][q])
				dfs2(b[i][q],i,b[i][q]); 
		} 
} 

void init(){
	tim=1; //新的节点从1开始 
	dfs1(1,1,1);//根节点，根节点的父亲（他自己），初始深度
	dfs2(1,1,1);//根节点，根节点的父亲（他自己），根节点重链顶端（他自己）；
	//以上乱搞之后……这棵树就变成了若干条链了，而且每条链的新编号都是连续的……
	//然后对链的维护 用线段树、非递归线段树、树状数组、分块乱搞 都可以 
	//以下是zkw线段树 
	n_=1;for (;n_<n+2;n_<<=1);
	for (int q=1;q<=n;q++){
		mmax[q+n_]=val[rnk[q]],sum[q+n_]=val[rnk[q]];
	}
	for(int q=n_-1;q>0;--q)  
		sum[q]=sum[q<<1]+sum[(q<<1)|1],mmax[q]=max(mmax[q<<1],mmax[(q<<1)|1]); 
} 
//注意！ 以下对线段树的操作针对的都是变换后的重新编号 
void chg(int i,int k){//zkw线段树的修改
	i+=n_;
	mmax[i]=k,sum[i]=k;
	i>>=1;
	for (;i;i>>=1){
		sum[i]=sum[i<<1]+sum[(i<<1)|1],mmax[i]=max(mmax[i<<1],mmax[(i<<1)|1]);
	}
} 
void find(int i,int j,int &s1,int &s2){
	i=i+n_-1,j=j+n_+1;
	s1=0,s2=-1000000;//和、 最值 
	for (;i^j^1;i>>=1,j>>=1){
		if (!(i&0x1))	s1+=sum[i+1],s2=max(s2,mmax[i+1]);
		if (j&0x1)		s1+=sum[j-1],s2=max(s2,mmax[j-1]); 
	}
}
void cal(int i,int j,int &s1,int &s2){ 
	s1=0,s2=-1000000;
	int t1,t2;
	while(top[i]!=top[j]){
		//链上路径要找lca,很显然是不断往重链上靠啊靠…… 
		if (dep[top[i]]<dep[top[j]]) swap(i,j);
		find(tid[top[i]],tid[i],t1,t2);
		s1+=t1,s2=max(s2,t2);
		i=fa[top[i]]; 
	}	 
	if (dep[i]>dep[j]) swap(i,j); 
	find(tid[i],tid[j],t1,t2);
	s1+=t1,s2=max(s2,t2);
} 
void solve(){
	scanf("%d",&n);
	for (int q=1,i,j;q<n;++q){
		scanf("%d%d",&i,&j);
		b[i].push_back(j);
		b[j].push_back(i);
	}
	for (int q=1;q<=n;q++) scanf("%d",&val[q]); 
	init();
	scanf("%d",&m);
	char s[20];
	for (int q=0,i,j;q<m;++q){
		scanf("%s",s);
		if (s[1]=='H'){
			scanf("%d%d",&i,&j);
			chg(tid[i],j);
		}
		else if (s[1]=='M'){
			scanf("%d%d",&i,&j);
			int s1,s2;
			cal(i,j,s1,s2);
			printf("%d\n",s2);
		}
		else {
			scanf("%d%d",&i,&j);
			int s1,s2;
			cal(i,j,s1,s2);
			printf("%d\n",s1);
		}
	}
}
int main(){
	solve();
	return 0;
}
