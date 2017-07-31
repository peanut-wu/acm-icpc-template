/*
http://acm.hdu.edu.cn/showproblem.php?pid=1163
������������n^n������
��λ�������Ϊroot(n) 
root(n)= n%9
֤����
���裬��d�ĸ�Ϊd%9( ��ʱ��ȡ0������ʱȡ9��
��d < 10ʱ��1~9��9�����϶�����;
��d >= 10ʱ��d�ĸ�Ϊd%9 = (d-1)%9+1����d��ǰһ������������1.

Problem : 1163 ( Eddy's digital Roots )     Judge Status : Accepted
RunId : 20892552    Language : G++    Author : leslie
Code Render Status : Rendered By HDOJ G++ Code Render Version 0.01 Beta
*/ 

#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int main(){
	int n;
	while (scanf("%d",&n)){
		if (n==0) break;
		int ans=n;
		for (int q=1;q<n;++q) ans=(ans*n)%9;
		printf("%d\n",ans==0?9:ans);
	}
	return 0;
}
