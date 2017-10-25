//hhhhhhhhÄ£ÄâÍË»ðË®¹ý¡­¡­
//http://hihocoder.com/problemset/problem/1142
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
using namespace std;
double a,b,c,INF=1e18;
struct point{
	double x,y;
}p,ans;
double dis(point aa,point bb){
	return sqrt((aa.x-bb.x)*(aa.x-bb.x)+(aa.y-bb.y)*(aa.y-bb.y));
}
double f(double x0){
	return a*x0*x0+b*x0+c;
}
double Rand(){
	return (rand()%1000)/1000.0;
}
double S(point aa){
	double s=dis(aa,p);
	if (s<INF){
		INF=s;
		ans=aa;
	}
	return s;
}
int main(){
	scanf("%lf%lf%lf%lf%lf",&a,&b,&c,&p.x,&p.y);
	point now=(point){p.x,f(p.x)},next;
	double T=200,c=0.99,dE,TMIN=1e-4,mx;
	srand(553);
	while (T>TMIN){
		mx=now.x+(Rand()-0.5)*T*2;
		next.x=mx,next.y=f(next.x);
		dE=S(now)-S(next);
		if (dE>0||exp(dE/T)>Rand())
			now=next;
		T*=c;
	}
	T=1e-4;
	for (int q=0;q<10000;q++){
		mx=ans.x+(Rand()-0.5)*T*2;
		next.x=mx,next.y=f(next.x);
		S(next);
	}
	printf("%.3lf\n",dis(ans,p));
	return 0; 
}
