/*
  http://www.lydsy.com/JudgeOnline/problem.php?id=1036
	ά��������ֵ��Ȩֵ�͡��� 
    Problem: 1036
    User: 597727533
    Language: C++
    Result: Accepted
    Time:2288 ms
    Memory:8568 kb
	ɥ�Ĳ��񣡴�������lct��������  �ٶȾ�ȻҲֻ��һ����������
	��Ȼ���÷�������ѯ��һ�����ˡ��� �����ٶ�Ҳ��û˭�ˡ��� 
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
LL val[MAX];//��Ȩֵ 
vector<int>b[MAX];//��ͼ 
int siz[MAX];//����������xΪ���������ڵ����
int top[MAX];//�������浱ǰ�ڵ���������Ķ��˽ڵ�
int son[MAX];//���������ض���
int dep[MAX];//�������浱ǰ�ڵ�����
int fa[MAX];//�������浱ǰ�ڵ�ĸ���
int tid[MAX],tim=0;//������������ÿ���ڵ��ʷֺ���±��
int rnk[MAX];//�������浱ǰ�ڵ����߶����е�λ�ã�Ҳ����tid�ķ��������� 


int sum[MAX],mmax[MAX],n_;
void dfs1(int i,int father,int d){
	//��һ��dfs �����ȡ��ڵ������ڵ���Ŀ���ڵ��ض��ӣ��ڵ㸸�� 
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
	//�ڶ���dfs ���i���������Ķ��˽�㣬���±�ż���ӳ��.
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
	tim=1; //�µĽڵ��1��ʼ 
	dfs1(1,1,1);//���ڵ㣬���ڵ�ĸ��ף����Լ�������ʼ���
	dfs2(1,1,1);//���ڵ㣬���ڵ�ĸ��ף����Լ��������ڵ��������ˣ����Լ�����
	//�����Ҹ�֮�󡭡�������ͱ�������������ˣ�����ÿ�������±�Ŷ��������ġ���
	//Ȼ�������ά�� ���߶������ǵݹ��߶�������״���顢�ֿ��Ҹ� ������ 
	//������zkw�߶��� 
	n_=1;for (;n_<n+2;n_<<=1);
	for (int q=1;q<=n;q++){
		mmax[q+n_]=val[rnk[q]],sum[q+n_]=val[rnk[q]];
	}
	for(int q=n_-1;q>0;--q)  
		sum[q]=sum[q<<1]+sum[(q<<1)|1],mmax[q]=max(mmax[q<<1],mmax[(q<<1)|1]); 
} 
//ע�⣡ ���¶��߶����Ĳ�����ԵĶ��Ǳ任������±�� 
void chg(int i,int k){//zkw�߶������޸�
	i+=n_;
	mmax[i]=k,sum[i]=k;
	i>>=1;
	for (;i;i>>=1){
		sum[i]=sum[i<<1]+sum[(i<<1)|1],mmax[i]=max(mmax[i<<1],mmax[(i<<1)|1]);
	}
} 
void find(int i,int j,int &s1,int &s2){
	i=i+n_-1,j=j+n_+1;
	s1=0,s2=-1000000;//�͡� ��ֵ 
	for (;i^j^1;i>>=1,j>>=1){
		if (!(i&0x1))	s1+=sum[i+1],s2=max(s2,mmax[i+1]);
		if (j&0x1)		s1+=sum[j-1],s2=max(s2,mmax[j-1]); 
	}
}
void cal(int i,int j,int &s1,int &s2){ 
	s1=0,s2=-1000000;
	int t1,t2;
	while(top[i]!=top[j]){
		//����·��Ҫ��lca,����Ȼ�ǲ����������Ͽ��������� 
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
