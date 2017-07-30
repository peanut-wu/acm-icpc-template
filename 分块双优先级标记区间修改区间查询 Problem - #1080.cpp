/* http://hihocoder.com/problemset/problem/1080*/
/*	656ms	7MB*/
/*·Ö¿é´ó·¨ºð*/ 
#include<iostream>
#include<cstdio>
#include<cmath>
#define N 100005
using namespace std;
int n,m,temp,b[N],sum[N],add[N];
bool f[N];

void T(int i){
	if (f[i]){
		f[i]=false;
		for (int q=i*temp;q<i*temp+temp;q++)
			b[q]=sum[i]/temp+add[i];
	}
	else {
		for (int q=i*temp;q<i*temp+temp;q++)
			b[q]+=add[i];
	}
	sum[i]+=add[i]*temp;
	add[i]=0;	
} 
void change(int l,int r,int t){
	if (l/temp==r/temp){
		T(l/temp);
		for (int q=l;q<=r;q++){
			sum[l/temp]=sum[l/temp]-b[q]+t;
			b[q]=t;
		}
	}
	else {
		T(l/temp);
		T(r/temp);
		for (int q=l;q<((l/temp)+1)*temp;q++){
			sum[l/temp]=sum[l/temp]-b[q]+t;
			b[q]=t;
		}
		for (int q=(r/temp)*temp;q<=r;q++){
			sum[r/temp]=sum[r/temp]-b[q]+t;
			b[q]=t;
		}
		for (int q=(l/temp)+1;q<(r/temp);q++){
			sum[q]=t*temp;
			f[q]=true;
			add[q]=0;
		}		 
	}
} 

void Add(int l,int r,int t){
	if (l/temp==r/temp){
		T(l/temp);
		for (int q=l;q<=r;q++){
			sum[l/temp]=sum[l/temp]+t;
			b[q]+=t;
		}
	}
	else {
		T(l/temp);
		T(r/temp);
		for (int q=l;q<((l/temp)+1)*temp;q++){
			sum[l/temp]=sum[l/temp]+t;
			b[q]+=t;
		}
		for (int q=(r/temp)*temp;q<=r;q++){
			sum[r/temp]=sum[r/temp]+t;
			b[q]+=t;
		}
		for (int q=(l/temp)+1;q<(r/temp);q++){
			add[q]+=t;
		}		 
	}
} 

void show(){
	for (int q=0;q<n;q++){
		if (f[q/temp])
			cout<<q<<":"<<sum[q/temp]/temp<<" ";
		else cout<<q<<":"<<b[q]<<" ";
	}cout<<endl;
}
long long getans(){
	long long ans=0;
	for (int q=0;q<n;q++)
		if (q+temp<n)
			ans+=sum[q/temp]+add[q/temp]*temp,q+=temp-1;
		else ans+=b[q]+add[q/temp];
	return ans;
}

int main(){
	//cin.sync_with_stdio(false);
//	cout.sync_with_stdio(false);
	scanf("%d%d",&n,&m);
	//cin>>n>>m; 
	++n;
	temp=sqrt(n*1.0);
	for (int q=0;q<n;q++){
		scanf("%d",&b[q]);
		//cin>>b[q];
		//b[q]=a[q];
		sum[q/temp]+=b[q];
	}
	//cout<<getans()<<endl;
	for (int q=0,i,j,k,t;q<m;q++){
		scanf("%d%d%d%d",&k,&i,&j,&t);
		//cin>>k>>i>>j>>t; 
		if (k){
			change(i,j,t);
		} 
		else Add(i,j,t);
		//show();
		printf("%d\n",getans());
		//cout<<getans()<<endl;
	}

	return 0;
} 
