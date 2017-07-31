/*
http://acm.hdu.edu.cn/showproblem.php?pid=1163
九余数定理：求n^n的数根
数位不断相加为root(n) 
root(n)= n%9
证明：
假设，数d的根为d%9( 暂时不取0，整除时取9）
当d < 10时，1~9这9个数肯定成立;
当d >= 10时，d的根为d%9 = (d-1)%9+1，即d的前一个数的数根加1.

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
