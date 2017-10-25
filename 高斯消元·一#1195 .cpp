/*高斯消元·一
AC
G++
326ms
4MB
4秒前
http://hihocoder.com/problemset/problem/1195?sid=1217782
*/
#include<bits/stdc++.h>
#define EPS 1e-7
using namespace std;
typedef double DB;

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
    return fabs(aa)<EPS;
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
        for (int p=q+1;p<=m;++p){
            DB tmp=a[p][q]/a[q][q];
            for (int qq=1;qq<=n;++qq)
                a[p][qq]-=(tmp*a[q][qq]);
            b[p]-=(tmp*b[q]);
        }
    }


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
            b[q]-=(a[q][p]*value[p]),a[q][p]=0;
        }
        value[q]=b[q]/a[q][q];
    }
    return 0;
}


const int max_n=502;
const int max_m=1003;

DB *a[max_m];
DB b[max_m][max_n];
DB ans[max_n];
DB s[max_n];
int n,m;
void solve(){
    cin>>n>>m;
    for (int q=1;q<=m;++q){
        for (int p=1;p<=n;++p)
            cin>>b[q][p];
        cin>>s[q];
    }
    for (int q=1;q<=m;++q)
        a[q]=b[q];
    int pr=Gauss(n,m,a,s,ans);
    if(pr==0){
        for (int q=1;q<=n;++q)
            cout<<(int)(ans[q]+0.5)<<endl;
    }
    else if (pr==1){
        cout<<"No solutions"<<endl;
    }
    else cout<<"Many solutions"<<endl;
}
int main(){
    solve();
    return 0;
}
