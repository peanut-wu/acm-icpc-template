/*
https://loj.ac/problem/113
线性基资料：http://blog.csdn.net/qaq__qaq/article/details/53812883

#21636
#113. 最大异或和
 Accepted
100
18 ms
500 K
C++ / 1.1 K
peanut-wu
2017-08-01 18:19:23
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#define LL long long
#define MAX_L  62//最大位数-1
using namespace std;
struct L_B{
    LL a[MAX_L+10];
    L_B(){
        memset(a,0,sizeof(a));
    }
    bool insert(LL i){//插入数字到集合中
        for(int q=MAX_L;q>=0;--q)
            if (i&(1LL<<q)){
                if (!a[q]){
                    a[q]=i;
                    return true;
                }
                i^=a[q];
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
}a;
int main(){
    int n;
    scanf("%d",&n);
    for (LL q=0,i;q<n;++q){
        scanf("%lld",&i);
        a.insert(i);
    }
    printf("%lld",a.findmax());


    return 0;
}
