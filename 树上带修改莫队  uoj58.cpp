/*
	http://uoj.ac/problem/58
		带修改莫队上树
	神tm这题意
	求树上路径中  一个数字i出现次数nums[i]*w[i]加权求和 带修改
*/
#include<bits/stdc++.h>
#define MAX 200005
#define QMAX 200005
#define LOG 25
#define LL long long
using namespace std;
int n,m,QU;
vector<int>a[MAX];//存树
int id[MAX];//存树所在块
//int root[MAX];//存某块块根
int size[MAX];//块大小
int blocksize,num;//块大小，块数目
bool used[MAX];//dfs所用
int stk[MAX],top;//栈和栈顶
int fa[MAX][LOG];//倍增法求lca所用
int dep[MAX];//结点的深度

/*以下是莫队内容*/
//int pos[MAX],rpos[MAX],now;//这玩意存的是dfs序的双向映射，不带修改的莫队要存 带修改的不用……
struct Q{
	int time,nid,u,v;
	friend bool operator <(const struct Q &aa,const struct Q &bb){
		if (id[aa.u]<id[bb.u])	return true;
		if (id[aa.u]==id[bb.u]){
			if (id[aa.v]<id[bb.v])	return true;//带修改的第二关键字也要用所在块 用dfs序第三关键字就没什么卵用了……
			if (id[aa.v]==id[bb.v]&&aa.nid<bb.nid)	return true;
		}
		return false;
	}
}b[QMAX]; //询问序列
LL ans[QMAX]; //答案
struct CH{
	int pos,now,prev;
}change[QMAX];//修改序列
int qulen,chlen;//询问数目，修改数目



/*以下是题目要存的信息*/
LL v[MAX];//糖果
LL w[MAX];//游客对糖果的抗药性
int c[MAX],dc[MAX];//某个位置是啥糖果，以及它的拷贝序列

bool vis[MAX];//莫队遍历时候用的临时数组，存点是否被遍历
int numb[MAX];//莫队遍历时候用的，存糖果第几次被访问
LL thissum;//莫队遍历时候用的，存当前解

void chg(int i,int k){//将某个点的糖果改为k
	if (i==-1) return ;
	if (vis[i]){
		thissum-=((LL)w[numb[c[i]]]*v[c[i]]);
		--numb[c[i]],++numb[k];
		thissum+=((LL)w[numb[k]]*v[k]);
	}
	c[i]=k;
}
void resv(int i){//将某个点的存在性取反
	if(vis[i]){
		thissum-=((LL)w[numb[c[i]]]*v[c[i]]);
		--numb[c[i]];
	}
	else {
		++numb[c[i]];
		thissum+=((LL)w[numb[c[i]]]*v[c[i]]);
	}
	vis[i]^=1;
}


void dfs1(int i){
	used[i]=true;
	//pos[i]=++now;rpos[now]=i;
	int le=a[i].size(),bot=top;

	for (int q=0;q<le;q++)
		if (!used[a[i][q]]){
			fa[a[i][q]][0]=i,dep[a[i][q]]=dep[i]+1;
			dfs1(a[i][q]);
			if (top-bot>=blocksize){
				++num;
				//root[num]=i;
				for (;;){
					id[stk[top]]=num;--top;
					if (top==bot)	break;
				}
			}
		}
	stk[++top]=i;
}

int lca(int aa,int bb){
	if (dep[aa]<dep[bb]) aa^=bb,bb^=aa,aa^=bb;
	int q,p;
	for (q=0;(1<<q)<=dep[aa];q++);
	--q;
	for (p=q;p>=0;p--)
		if (dep[aa]-(1<<p)>=dep[bb])
			aa=fa[aa][p];
	if (aa==bb) return aa;
	for (p=q;p>=0;p--)
		if (fa[aa][p]!=-1&&fa[aa][p]!=fa[bb][p])
			aa=fa[aa][p],bb=fa[bb][p];
	return fa[aa][0];
	/*倍增法求lca，道理就是2进制能表示所有数字，和优化多重背包一个道理，从大到小减*/
}

void init(){
	fa[1][0]=-1;//根节点没有父亲，根节点为1
	memset(used,0,n+2);
	blocksize=pow(n,0.6666666666),num=0;//带修改的块大小要取n^2/3才能保证复杂度
	id[1]=0,size[0]=1,dep[1]=0,top=0;//num是第一块，设置根节点
	//root[0]=1,now=-1；//没必要存root和dfs序
	dfs1(1);
	for (;top;) id[stk[top--]]=num;
	/*把最后一块取出来，用栈才不会被菊花树卡成o(n)*/

	for (int q=1;(1<<q)<=n;q++)
		for (int p=1;p<=n;p++)
			if (fa[p][q-1]!=-1)
				fa[p][q]=fa[fa[p][q-1]][q-1];
	/*倍增法求lca*/
}

void modui(){
	int t=0,u=0,v=0;
	thissum=0;


	for (t=1;t<=b[0].nid;++t) chg(change[t].pos,change[t].now);
	u=b[0].u,v=b[0].v;
	int tmp=lca(u,v);
	while (u!=tmp){resv(u);	u=fa[u][0];}
	while (v!=tmp){resv(v); v=fa[v][0];}
    resv(v);
    ans[b[0].time]=thissum;
    u=b[0].u,v=b[0].v;
	//搞定第一个询问

	for (int i=1; i<qulen; ++i){
        for (;t<=b[i].nid;++t)
			chg(change[t].pos,change[t].now);
		for (;t>b[i].nid;--t){
			chg(change[t].pos,change[t].prev);
		}//处理修改操作
		int uu=b[i].u,vv=b[i].v,tmp1,tmp2;
		tmp1=lca(u,uu),tmp2=lca(v,vv);
		resv(lca(u,v));
		while (u!=tmp1){resv(u);u=fa[u][0];}
        while (v!=tmp2){resv(v);v=fa[v][0];}
		while (uu!=tmp1){resv(uu);uu=fa[uu][0];}
        while (vv!=tmp2){resv(vv);vv=fa[vv][0];}
        u=b[i].u,v=b[i].v;
        resv(lca(u,v));
		//转移询问，利用对称差  s(u,v)为u,v路径去掉lca  则s(u,vv)=s(u,v) xor s(v,vv)
		//所以去掉lca搞完在补上lca就行……
		ans[b[i].time]=thissum;
    }
}

int main(){
	//cout.sync_with_stdio(false);
	//while (scanf("%d%d%d",&n,&m,&QU)!=EOF){
		scanf("%d%d%d",&n,&m,&QU);
		for (int q=1;q<=m;q++)
			scanf("%lld",&v[q]);
		for (int q=1;q<=n;q++)
			scanf("%lld",&w[q]);
		for (int q=1,i,j;q<n;q++){
			scanf("%d%d",&i,&j);
			a[i].push_back(j);
			a[j].push_back(i);
		}
		for (int q=1;q<=n;q++){
			scanf("%d",&c[q]);dc[q]=c[q];
		}
		init();
		chlen=0,qulen=0;
		change[0].pos=-1;
		for (int q=0,k;q<QU;q++){
			scanf("%d",&k);
			if (k==0){
				++chlen;
				scanf("%d%d",&change[chlen].pos,&change[chlen].now);
				change[chlen].prev=dc[change[chlen].pos],dc[change[chlen].pos]=change[chlen].now;//拷贝数组的应用，存的得是上一次修改完的结果
			}
			else {
				scanf("%d%d",&b[qulen].u,&b[qulen].v);
				if (id[b[qulen].v]<id[b[qulen].u])
					b[qulen].u^=b[qulen].v,b[qulen].v^=b[qulen].u, b[qulen].u^=b[qulen].v;
				b[qulen].nid=chlen;
				b[qulen].time=qulen;
				++qulen;
			}
		}
		sort(b,b+qulen,less<Q>());
		modui();
		for (int q=0;q<qulen;q++){
			printf("%lld\n",ans[q]);
		}
	//}
	return 0;
}

