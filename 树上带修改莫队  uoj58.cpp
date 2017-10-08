/*
	http://uoj.ac/problem/58
		���޸�Ī������
	��tm������
	������·����  һ������i���ִ���nums[i]*w[i]��Ȩ��� ���޸�
*/
#include<bits/stdc++.h>
#define MAX 200005
#define QMAX 200005
#define LOG 25
#define LL long long
using namespace std;
int n,m,QU;
vector<int>a[MAX];//����
int id[MAX];//�������ڿ�
//int root[MAX];//��ĳ����
int size[MAX];//���С
int blocksize,num;//���С������Ŀ
bool used[MAX];//dfs����
int stk[MAX],top;//ջ��ջ��
int fa[MAX][LOG];//��������lca����
int dep[MAX];//�������

/*������Ī������*/
//int pos[MAX],rpos[MAX],now;//����������dfs���˫��ӳ�䣬�����޸ĵ�Ī��Ҫ�� ���޸ĵĲ��á���
struct Q{
	int time,nid,u,v;
	friend bool operator <(const struct Q &aa,const struct Q &bb){
		if (id[aa.u]<id[bb.u])	return true;
		if (id[aa.u]==id[bb.u]){
			if (id[aa.v]<id[bb.v])	return true;//���޸ĵĵڶ��ؼ���ҲҪ�����ڿ� ��dfs������ؼ��־�ûʲô�����ˡ���
			if (id[aa.v]==id[bb.v]&&aa.nid<bb.nid)	return true;
		}
		return false;
	}
}b[QMAX]; //ѯ������
LL ans[QMAX]; //��
struct CH{
	int pos,now,prev;
}change[QMAX];//�޸�����
int qulen,chlen;//ѯ����Ŀ���޸���Ŀ



/*��������ĿҪ�����Ϣ*/
LL v[MAX];//�ǹ�
LL w[MAX];//�οͶ��ǹ��Ŀ�ҩ��
int c[MAX],dc[MAX];//ĳ��λ����ɶ�ǹ����Լ����Ŀ�������

bool vis[MAX];//Ī�ӱ���ʱ���õ���ʱ���飬����Ƿ񱻱���
int numb[MAX];//Ī�ӱ���ʱ���õģ����ǹ��ڼ��α�����
LL thissum;//Ī�ӱ���ʱ���õģ��浱ǰ��

void chg(int i,int k){//��ĳ������ǹ���Ϊk
	if (i==-1) return ;
	if (vis[i]){
		thissum-=((LL)w[numb[c[i]]]*v[c[i]]);
		--numb[c[i]],++numb[k];
		thissum+=((LL)w[numb[k]]*v[k]);
	}
	c[i]=k;
}
void resv(int i){//��ĳ����Ĵ�����ȡ��
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
	/*��������lca���������2�����ܱ�ʾ�������֣����Ż����ر���һ�������Ӵ�С��*/
}

void init(){
	fa[1][0]=-1;//���ڵ�û�и��ף����ڵ�Ϊ1
	memset(used,0,n+2);
	blocksize=pow(n,0.6666666666),num=0;//���޸ĵĿ��СҪȡn^2/3���ܱ�֤���Ӷ�
	id[1]=0,size[0]=1,dep[1]=0,top=0;//num�ǵ�һ�飬���ø��ڵ�
	//root[0]=1,now=-1��//û��Ҫ��root��dfs��
	dfs1(1);
	for (;top;) id[stk[top--]]=num;
	/*�����һ��ȡ��������ջ�Ų��ᱻ�ջ�������o(n)*/

	for (int q=1;(1<<q)<=n;q++)
		for (int p=1;p<=n;p++)
			if (fa[p][q-1]!=-1)
				fa[p][q]=fa[fa[p][q-1]][q-1];
	/*��������lca*/
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
	//�㶨��һ��ѯ��

	for (int i=1; i<qulen; ++i){
        for (;t<=b[i].nid;++t)
			chg(change[t].pos,change[t].now);
		for (;t>b[i].nid;--t){
			chg(change[t].pos,change[t].prev);
		}//�����޸Ĳ���
		int uu=b[i].u,vv=b[i].v,tmp1,tmp2;
		tmp1=lca(u,uu),tmp2=lca(v,vv);
		resv(lca(u,v));
		while (u!=tmp1){resv(u);u=fa[u][0];}
        while (v!=tmp2){resv(v);v=fa[v][0];}
		while (uu!=tmp1){resv(uu);uu=fa[uu][0];}
        while (vv!=tmp2){resv(vv);vv=fa[vv][0];}
        u=b[i].u,v=b[i].v;
        resv(lca(u,v));
		//ת��ѯ�ʣ����öԳƲ�  s(u,v)Ϊu,v·��ȥ��lca  ��s(u,vv)=s(u,v) xor s(v,vv)
		//����ȥ��lca�����ڲ���lca���С���
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
				change[chlen].prev=dc[change[chlen].pos],dc[change[chlen].pos]=change[chlen].now;//���������Ӧ�ã���ĵ�����һ���޸���Ľ��
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

