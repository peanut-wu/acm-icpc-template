/**************************************************************
    http://www.lydsy.com/JudgeOnline/problem.php?id=1036
    
	//��ʵ�������һ�����ʵ���= = 
    
    link-cut-trerά��������ֵ��Ȩֵ�͡��� 
    
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
int son[MAX_N][2],parent[MAX_N];//���� ����
int val[MAX_N]; //ֵ�� 
int n,m;

/*������lazy���亯��*/ 
bool resv[MAX_N];
int sum[MAX_N],mmax[MAX_N]; 
inline void update(int p){//�·�����ϴ�
	p[sum]=p[val],p[mmax]=p[val];
	if (p[son][0])	p[sum]+=p[son][0][sum],p[mmax]=max(p[mmax],p[son][0][mmax]);
	if (p[son][1])	p[sum]+=p[son][1][sum],p[mmax]=max(p[mmax],p[son][1][mmax]);
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
	int kk=f>0?flag(f):0;//���������ӻ����Һ��� 
	//p������ ��   p�ұ߶��ӱ�ɸ���   p�Һ��ӱ�ɸ�������   ��һ�߶Գ�
	pushdown(f);
	pushdown(p);//lct�����Ż������á����Ż�2 �����۲��뻹��ɾ��֮ǰ�϶����Ѿ�push���� ������û�б�Ҫ��  ������Ż������ǶԵ� �������������tm������ 
	int k=flag(p);//���ӻ����Һ��� 
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
void access(int p){//�ǵݹ�  
	pushdown(p);//������ 
	Splay(p);
	if (p[son][1]){
		p[son][1][parent]=-p;
		p[son][1]=0;//�Ͽ����������µĵ� 
		update(p);
	}
	while(p[parent]<0){
		int temp=-p[parent];
		pushdown(temp);//������ 
		Splay(temp);
		if (temp[son][1]){
			temp[son][1][parent]=-temp;
		} 
		temp[son][1]=p,p[parent]=temp;
		update(temp);
		p=temp;
	} 
} 
void makeroot(int i){//��תi�����ĵ㣬��iΪ�� 
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

