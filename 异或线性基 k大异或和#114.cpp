/*
https://loj.ac/problem/114
线性基资料：http://blog.csdn.net/qaq__qaq/article/details/53812883

 Accepted
100
148 ms
436 K
C++ / 1.6 K
peanut-wu
2017-08-01 19:26:49

*/
#include<iostream>
#include<cstdio>
#include<cstring>
#define LL long long
#define MAX_L  62//最大位数-1
using namespace std;
struct L_B{
    LL a[MAX_L+10];
    bool zeros;
    L_B(){
        memset(a,0,sizeof(a));
        zeros=false;
    }
    bool insert(LL i){//插入数字到集合中
        for(int q=MAX_L;q>=0;--q)
            if (i&(1LL<<q)){
                if (!a[q]){
                    a[q]=i;
                    return true;
                }
                i^=a[q];
                if (i==0) zeros=true;
            }
        return false;
    }
    void rebuild(){//消元
        for (int q=MAX_L;q>=0;--q)
            for (int p=q-1;p>=0;--p)
                if (a[q]&(1LL<<p))
                    a[q]^=a[p];
    }
    LL findmax(){//能表达的最大值
        LL ans=0;
        for (int q=MAX_L;q>=0;--q)
            if ((ans^a[q])>ans)//括号  ^优先级小于<
                ans^=a[q];
        return ans;
    }
    LL findkth(LL k){//简单二进制 特判0
        if (zeros) --k;
        if (k==0) return 0;
        LL ans=0;
        for (int q=0;q<=MAX_L&&k;++q)
            if (a[q]){
                if (k&0x1) ans^=a[q];
                k>>=1;
            }
        if (k) return -1;
        else return ans;
    }
}a;
int main(){
    int n,m;
    scanf("%d",&n);
    for (LL q=0,i;q<n;++q){
        scanf("%lld",&i);
        a.insert(i);
    }
    a.rebuild();
    scanf("%d",&m);
    for (LL q=0,i;q<m;++q){
        scanf("%lld",&i);
        printf("%lld\n",a.findkth(i));
    }

    return 0;
}
