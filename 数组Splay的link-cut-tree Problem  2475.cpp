/**************************************************************
    http://acm.hdu.edu.cn/viewcode.php?rid=19855081
	
	Problem : 2475 ( Box )     Judge Status : Accepted
	RunId : 19855081    Language : G++    Author : sfdarg
	Code Render Status : Rendered By HDOJ G++ Code Render Version 0.01 Beta
    
    link-cut-trer��̽���� 
     
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
int val[MAX_N]; //ֵ�� 
int n,m;
/*������lazy���亯��*/ 
//int size[MAX_N];//�ӽڵ���� 
//bool resv[MAX_N];//��ת��� 
inline void update(int p){//�·�����ϴ�
/*	p[size]=1;
	if (p[son][0]) p[size]+=p[son][0][size];
	if (p[son][1]) p[size]+=p[son][1][size];*/
} 
inline void pushdown(int p){//����·� 
/*	if (resv[p]){
		swap(p[son][0],p[son][1]);
		p[son][0][resv]^=1,p[son][1][resv]^=1;
		p[resv]=0; 
	} */
	
}

void rotate(int p){
	int k=flag(p);//���ӻ����Һ��� 
	int f=p[parent];//���� 
	int g=f[parent];//���׵ĸ���
	int kk=f>0?flag(f):0;//���������ӻ����Һ��� 
	//p������ ��   p�ұ߶��ӱ�ɸ���   p�Һ��ӱ�ɸ�������   ��һ�߶Գ�
	/*pushdown(f);
	pushdown(p);*///�Ż�2 �����۲��뻹��ɾ��֮ǰ�϶����Ѿ�push���� ������û�б�Ҫ��  ������Ż������ǶԵģ����û��Splay�Ļ��� ���Ҽ�����tm������ 
	int c=p[son][k^1];
	if (c) c[parent]=f;f[son][k]=c;
	p[son][k^1]=f,f[parent]=p;
	p[parent]=g;   if (g>0)	g[son][kk]=p; //<=0�Ķ��ǷǷ���   g��<0��Ϊ�˺�Link-cut-treeд��ͳһ 
	// ����Ϊʲô�� g > 0����Ҫ��Ϊ�˺���д Link/cut tree ʱ����
	//��Ϊ���ǿ����� parent ���һ������ֵ����ʾ�������һ��ƫ�ñߣ�preferred edge�������������ǾͲ������ر�ά��һ��path_parent �����ˣ�
	update(f);
//	update(p);    //�Ż�1 �ĵ�69�� ��Ȼ��֤����ȷ��  
}
void Splay(int p){	
	for (;p[parent]>0;rotate(p)){
		if (p[parent][parent]>0){
			if (flag(p)==flag(p[parent])) 
				rotate(p[parent]);
			else rotate(p);
		}
	}
	update(p); //�Ż�1���¼���ȥ�� 
	//�����һ��ֱ��,��ת�ְ�,Ȼ��ת�Լ�;����ת�����Լ� 
} 
/*void access(int p){//�ݹ�汾 
	Splay(p);
	if (p[son][1]){
		p[son][1][parent]=-p;
		p[son][1]=0;//�Ͽ�p�����������µĵ�
	}
	if (p[parent]<0){ 
		access(-p[parent]);
		p[parent]=-p[parent];
		p[parent][son][1]=p;
		rotate(p); 
	} 
}*/ 
void access(int p){//�ǵݹ� 
	Splay(p);
	if (p[son][1]){
		p[son][1][parent]=-p;
		p[son][1]=0;//�Ͽ����������µĵ� 
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
void move(int i,int j){//i����j 
	if (i==j)	return ;
	if (j){//�ų�j����i�ķǷ�״�� 
		access(j);
		access(i);
		Splay(j);
		if (j[parent]==-i) return ; 
	} 
	Splay(i);
	int prev=i[son][0];
	if(prev){//�Ͽ���������� 
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
