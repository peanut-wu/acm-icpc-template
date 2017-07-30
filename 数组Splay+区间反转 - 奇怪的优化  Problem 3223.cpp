/**************************************************************
	http://www.lydsy.com/JudgeOnline/problem.php?id=3223
    Problem: 3223
    User: 597727533
    Language: C++
    Result: Accepted
    Time:2712 ms
    Memory:3344 kb
    Ps:����ýṹ����Կ�һ��� ָ����ֿ��Կ�һ���  Ȼ����û��ʲô���� �ٶȺͿ�������һ�����𡢡������� 
    
    
    ѡ�������һЩ��ֵ��Ż��� 
	 
	 1.�� rotate �����в� update ��ǰ�ڵ㡣��Ȼ��ֻ��Ҫ�� splay ����֮�� update ���ɡ�
	 2.�� rotate �����в���Ҫ�·ű�ǡ���Ȼ�����ҵ���֮ǰ����һ���������϶��µĹ��̡��������·ű�Ǽ��ɡ�
     3.����ʹ���Լ� define �� max��swap ֮���Ϊ���úܶ�ĺ����������������иı伴�ɿ� 0.2 �롣
     4.����֮�� splay ������������ȵĵ㡣�����һ���� splay ���ķ�֮һ���µ���ȣ��������޴��Ż���
    
    ��lazy��������ʱ �ô����� 
     
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
int son[MAX_N][2],parent[MAX_N];//���� ����
int val[MAX_N]; 
int size[MAX_N];//�ӽڵ���� 
bool resv[MAX_N];//��ת��� 
int root,tail,n,m;
inline void update(int p){//�·�����ϴ�
	p[size]=1;
	if (p[son][0]) p[size]+=p[son][0][size];
	if (p[son][1]) p[size]+=p[son][1][size];
} 
inline void pushdown(int p){//����·� 
	if (resv[p]){
		swap(p[son][0],p[son][1]);
		p[son][0][resv]^=1,p[son][1][resv]^=1;
		p[resv]=0; 
	} 
}
void rotate(int p){
	int f=p[parent];//���� 
	int g=f[parent];//���׵ĸ���
	int kk=g>0?flag(f):0;//���������ӻ����Һ��� 
	//p������ ��   p�ұ߶��ӱ�ɸ���   p�Һ��ӱ�ɸ�������   ��һ�߶Գ�
	/*pushdown(f);
	pushdown(p);*///�Ż�2 �����۲��뻹��ɾ��֮ǰ�϶����Ѿ�push���� ������û�б�Ҫ��  ������Ż������ǶԵģ����û��Splay�Ļ��� ���Ҽ�����tm������ 
	int k=flag(p);//���ӻ����Һ��� ��ת�꺢�ӿ��ܱ��� ����Ҫ�ں��� 
	int c=p[son][k^1];
	if (c) c[parent]=f;f[son][k]=c;
	p[son][k^1]=f,f[parent]=p;
	p[parent]=g;   if (g>0)	g[son][kk]=p; //<=0�Ķ��ǷǷ���   g��<0��Ϊ�˺�Link-cut-treeд��ͳһ 
	update(f);
//	update(p);    //�Ż�1 �ĵ�69�� ��Ȼ��֤����ȷ��  
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
	update(p); //�Ż�1���¼���ȥ�� 
	if (fa==0) root=p;
	//�����һ��ֱ��,��ת�ְ�,Ȼ��ת�Լ�;����ת�����Լ� 
} 
int insert(int p,int i){
	pushdown(p);//�Ż�2 �������е� 
	Splay(p,0);		
	int q;
	if (p[val]>i){
		if (p[son][0]==0){
			p[son][0]=q=NEW();
			q[parent]=p,q[val]=i,q[size]=1;
			//�����½ڵ� ������Ϣ 
			return q;
		}
		else q=insert(p[son][0],i);
	}
	else {
		if (p[son][1]==0){
			int q;
			p[son][1]=q=NEW();
			q[parent]=p,q[val]=i,q[size]=1; 
			//�����½ڵ� ������Ϣ 
			return q;
		}
		else q=insert(p[son][1],i);
	}
	update(p);
	return q;
}

int find(int p,int i){
	for (;;){
		pushdown(p);//�Ż�2 �������е� 
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
