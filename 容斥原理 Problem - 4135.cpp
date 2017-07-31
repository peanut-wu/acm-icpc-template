/*
http://acm.hdu.edu.cn/showproblem.php?pid=4135
�ݳ�ԭ��
 
��[a,b]�����ں�c���ʵ����ָ��� 

Problem : 4135 ( Co-prime )     Judge Status : Accepted
RunId : 20892507    Language : G++    Author : leslie
Code Render Status : Rendered By HDOJ G++ Code Render Version 0.01 Beta
*/

#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
long long a,b,c,ans;
int len;
vector<int>prime;
long long cal(long long aa,long long bb,long long cc){//aa��bb֮���ж��ٸ����ְ���cc 
	long long ans1=(aa-1)/cc,ans2=bb/cc;
	return ans2-ans1;
}
void dfs(int i,int total,long long now,long long sum){
	if (i==len){
		if (total&0x1) ans+=sum;
		else ans-=sum;
		return ;
	}
	dfs(i+1,total,now,sum);
	dfs(i+1,total+1,now*prime[i],cal(a,b,now*prime[i]));
}

long long solve(){
	if (c==1) return b-a+1;//���⿴����1������wa��  ��ʹ 
	prime.clear();
	for (int q=2;q*q<=c;++q){
		if (c%q==0){
			prime.push_back(q);
		}
		while (c%q==0) c/=q;
	}
	if (c>1) prime.push_back(c);
	len=prime.size();
	//�������ֽ�
	ans=0;
	dfs(0,0,1,0);//�ҳ������ʵ����� 
	return b-a+1-ans;
}
int main(){
	int n;
	scanf("%d",&n);
	for (int q=1;q<=n;++q){
		scanf("%I64d%I64d%I64d",&a,&b,&c);
		printf("Case #%d: %I64d\n",q,solve());
	}
	return 0;
} 
