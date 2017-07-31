/*
http://acm.hdu.edu.cn/showproblem.php?pid=1724
辛普森积分 裸题 求椭圆部分面积 
x^2/a+y^2/b=1

Problem : 1724 ( Ellipse )     Judge Status : Accepted
RunId : 20892268    Language : G++    Author : wrongnumber
Code Render Status : Rendered By HDOJ G++ Code Render Version 0.01 Beta
*/ 

#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
double a,b;
double F(double i){//函数值 
	return sqrt((1-i*i/a)*b);
}
#define Simpson(l,r)((F(l)+4*F((l+r)*0.5)+F(r))*(r-l)/6)//三点辛普森公式



double asr(double l,double r,double eps,double A){//要传A……否则多算一次 有时会超时 
	double mid=(l+r)*0.5;
	double ansl=Simpson(l,mid),ansr=Simpson(mid,r);
	if (fabs(A-ansl-ansr)>15*eps)
		return asr(l,mid,eps*0.5,ansl)+asr(mid,r,eps*0.5,ansr);
	else return ansl+ansr;
}


int main(){
	int n;
	scanf("%d",&n);
	while (n--){
		double c,d;
		scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
		a=a*a;b=b*b;
		printf("%.3f\n",asr(c,d,1e-6,Simpson(c,d))*2);
	} 
	
	return 0;
}
