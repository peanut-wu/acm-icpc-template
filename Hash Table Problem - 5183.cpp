/* http://acm.hdu.edu.cn/showproblem.php?pid=5183*/
/*辣鸡OJ 卡我stl……随便手写了一个挂链hash 非常粗糙 不过能水过*/
/*后来试了试分层hash  爆炸了……不知道是哪里的锅*/ 
#include<iostream>
#include<cstdio>
#include<set>
#include<cstring>
#define LL long long 
#define ULL unsigned long long 
#define MAX 1000002
using namespace std;
int N,num,n,k;
int a[MAX];
#define MOD 1000007
struct HASH{
	LL val;
	HASH *next;
};
HASH*tb[MOD];
void insert(LL t){
	ULL val=(ULL)t;
	val%=MOD;
	HASH*temp=new HASH;
	temp->val=t;
	temp->next=tb[val];
	tb[val]=temp;
}
bool find(LL t){
	ULL val=(ULL)t;
	val%=MOD;
	HASH *temp=tb[val];
	while (temp!=NULL){
		if (temp->val==t)	return true;
		temp=temp->next;
	}
	return false;
}
void delet(LL t){
	ULL val=(ULL)t;
	val%=MOD;
	HASH *temp2=tb[val];
	while (temp2->next!=NULL){
		if (temp2->next->val==t){
			HASH *temp=temp2->next;
			temp2->next=temp->next;
			delete temp; 
			return ;
		}
		temp2=temp2->next;
	}
}
void clear(){
	for (int q=0;q<MOD;q++){
		HASH *temp=tb[q];
		for (;temp!=NULL;){
			tb[q]=temp->next;
			delete temp;
			temp=tb[q];
		} 
	} 
}
//set<long long>jud;
void charge(){
	scanf("%d%d",&n,&k);
	/*jud.clear();*/clear();
	LL sum=0,temp;
	for (int q=0;q<n;q++){
		scanf("%d",&a[q]);
		if (q&0x1) sum-=a[q];
		else sum+=a[q];
		/*jud.insert(sum);*/insert(sum);
		if (sum==k){
			printf("Case #%d: Yes.\n",num);
			return ;
		}
	}
	sum=0;
	for (int q=0;q<n;q++){
		if (q&0x1) sum-=a[q],temp=k+sum;
		else sum+=a[q],temp=-k+sum;
		/*jud.erase(sum);*/delet(sum);
		if (/*jud.find(temp)!=jud.end()*/find(temp)){
			printf("Case #%d: Yes.\n",num);
			return ;
		}
	}
	
	printf("Case #%d: No.\n",num);
}
int main(){
	for (int q=0;q<MOD;q++) tb[q]=NULL; 
	scanf("%d",&N);
	for (num=1;num<=N;++num) charge();
	return 0;
}
