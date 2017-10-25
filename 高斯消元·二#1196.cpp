/*
高斯消元·二
AC
G++
0ms
0MB
http://hihocoder.com/problemset/problem/1196
*/
#include<bits/stdc++.h>
#define EPS 1e-7
using namespace std;
typedef bool DB;

void Swap(DB *a[],DB b[],int i,int j){
    if (i==j)   return ;
    DB *tmp=a[i];
    a[i]=a[j];
    a[j]=tmp;
    DB tmp2=b[i];
    b[i]=b[j];
    b[j]=tmp2;
}
bool Zeros(DB aa){
    return aa^1;
  //  return aa==0;
}
int Gauss(int n,int m,DB *a[],DB b[],DB value[]){//0唯一解 1无解 2多解
    bool Flag;
    bool Multiresult=false;
    bool Noresult=false;

    for (int q=1;q<=n;++q){
        Flag=false;
        for (int p=q;p<=m;++p)
            if (!Zeros(a[p][q])){
                Swap(a,b,q,p);
                Flag=true;
                break;
            }
        if (!Flag){
            Multiresult=true;
            continue;
        }
        for (int p=q+1;p<=m;++p)
            if(a[p][q]){
           // DB tmp=a[p][q];
            for (int qq=1;qq<=n;++qq)
                a[p][qq]^=a[q][qq];
            b[p]^=b[q];
        }
    }
/*
    for (int q=1;q<=n;++q){
        for(int p=1;p<=n;++p)
       // sum+=ans[q];
        cout<<a[q][p];
        cout<<endl;
       // else cout<<" ";
    }*/
    for (int q=1,p;q<=m;++q){
        for(p=1;p<=n;++p)
            if (!Zeros(a[q][p]))
                break;
        if (p==n+1 && !Zeros(b[p]))
            return 1;
    }
    if(Multiresult) return 2;
    for (int q=n;q;--q){
        for (int p=q+1;p<=n;++p){
            b[q]^=(a[q][p]*value[p]),a[q][p]=0;
        }
        value[q]=b[q]*a[q][q];
    }
    return 0;
}


const int max_n=31;
const int max_m=31;

char aa[7][7];
DB* a[max_n];
DB b[max_m][max_n];
DB c[max_m];
DB ans[max_n];
int n,m;
int adx[]={1,0,-1,0,0};
int ady[]={0,-1,0,1,0};
void solve(){
    n=6;
    for (int q=0;q<5;++q)
        cin>>aa[q];

    for (int q=0;q<5;++q)
        for (int p=0;p<6;++p){
            c[q*6+p+1]=(aa[q][p]-'0')^1;
            a[q*6+p+1]=b[1+q*6+p];
            for (int i=1;i<=30;++i)
                a[q*6+p+1][i]=0;
            for (int i=0;i<5;++i)
                if (q+adx[i]>=0&&q+adx[i]<5 && p+ady[i]>=0 && p+ady[i]<6)
                    a[q*6+p+1][(q+adx[i])*6+p+ady[i]+1]=1;
        }
    Gauss(30,30,a,c,ans);
    int sum=0;
    for (int q=1;q<=30;++q){
        sum+=ans[q];
    }
    cout<<sum<<endl;
    for (int q=1;q<=30;++q)
        if (ans[q])
            cout<<(q-1)/6+1<<" "<<(q-1)%6+1<<endl;
}
int main(){
    solve();
    return 0;
}
