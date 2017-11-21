#include<bits/stdc++.h>
//#define double float
using namespace std;
int n,m;
double r;
const int max_n=502;
double a[max_n*max_n*4];
struct comp{
    double r,i;comp(double _r=0,double _i=0){r=_r,i=_i;}
    comp operator+(const comp &x){return comp(r+x.r,i+x.i);}
    comp operator-(const comp &x){return comp(r-x.r,i-x.i);}
    comp operator*(const comp &x){
        return comp(r*x.r-i*x.i,r*x.i+i*x.r);
    }
};
const double pi=acos(-1.0);
void change(comp y[],int len)
{
    int i,j,k;
    for(i = 1, j = len/2;i < len-1;i++)
    {
        if(i < j)swap(y[i],y[j]);
        k = len/2;
        while( j >= k)
        {
            j -= k;
            k /= 2;
        }
        if(j < k)j += k;
    }
}
void fft(comp y[],int len,int on)
{
    change(y,len);
    for(int h = 2;h <= len;h <<= 1)
    {
        comp wn(cos(-on*2*pi/h),sin(-on*2*pi/h));
        for(int j = 0;j < len;j += h)
        {
            comp w(1,0);
            for(int k = j;k < j+h/2;k++)
            {
                comp u = y[k];
                comp t = w*y[k+h/2];
                y[k] = u+t;
                y[k+h/2] = u-t;
                w = w*wn;
            }
        }
    }
    if(on == -1)
        for(int i = 0;i < len;i++)
            y[i].r /= len;
}
comp aa[max_n*max_n*8],bb[max_n*max_n*8],cc[max_n*max_n*8];
//double rr[max_n*max_n*7];
void solve(){
    r*=r;
    //memset(aa,0,sizeof(aa));
    //memset(bb,0,sizeof(bb));
   // memset(rr,0,sizeof(rr));
    int add=2*n*m+m;
    int n_=1;
    int len=4*m*n+2*m+1;

    for (;n_<len;n_<<=1);
    for (int q=0;q<n_;++q)
        aa[q]=comp(0,0),bb[q]=comp(0,0);

    for (int q=0;q<n;++q)
        for (int p=0;p<m;++p){
            //cin>>a[q*m*2+p];
            scanf("%lf",&a[q*m*2+p]);
            aa[q*m*2+p]=comp(a[q*m*2+p],0);
        }
    double ans=0;

    for (int q=-n;q<=n;++q)
        for (int p=-m;p<=m;++p){
            double d=q*q+p*p;
            if ( (q||p) && r>d){
                bb[(q+n)*2*m+p+m].r=1.0/(1+sqrt(d));
             //   cout<<" f"<<add+q*m+p<<"  "<<rr[add+q*m+p]<<endl;
            }
            //else bb[(q+2*n)*2*m+p]=0;
           // if (add+q*m+p==9) cout<<q<<" "<<p<<endl;
            //cout<<"q "<<q<<" "<<p<<" "<<d<<" "<<r<<endl;
        }


   // for (int q=0;q<n_;++q){
     //   aa[q]=comp(a[q],0);
      //  bb[q]=comp(rr[q],0);
     //   cout<<q<<" "<<rr[q]<<endl;
    //}
    /*for (int q=0;q<len;++q)
        for (int p=0;p<len;++p)
            cc[q+p]=cc[q+p]+(aa[q]*bb[p]);*/

    fft(aa,n_,1);
    fft(bb,n_,1);
    for (int q=0;q<n_;++q)
        cc[q]=aa[q]*bb[q];
    fft(cc,n_,-1);
    for (int p=0;p<n;++p)
        for (int q=0;q<m;++q)
            ans=max(ans,a[p*m*2+q]+cc[p*m*2+q+add].r);
    printf("%.3f\n",ans);
}
int main(){
   // cin.sync_with_stdio(false);
    //cout.sync_with_stdio(false);
    while (scanf("%d%d%lf",&n,&m,&r)!=EOF){
        solve();
    }


    return 0;
}
