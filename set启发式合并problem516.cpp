/*
https://loj.ac/problem/516
#37540
#516. 「LibreOJ β Round #2」DP 一般看规律
 Accepted
100
5125 ms
33300 KiB

*/

#include<bits/stdc++.h>
using namespace std;
const int max_n=5e5+10;
const int mmax=2147483647;
map<int,int>b;
set<int>a[max_n];
int n,m,len,ans=mmax;
void merge(int fi,int fj,int &s){
    if (a[fi].size()>a[fj].size())  a[fi].swap(a[fj]);
    s=mmax;
    for (set<int>::iterator it=a[fi].begin(),tmp;it!=a[fi].end();it++){
        a[fj].insert(*it);
        tmp=a[fj].find(*it);
        tmp++;
        if (tmp!=a[fj].end()) s=min((*tmp)-(*it),s);
        tmp--;
        if (tmp!=a[fj].begin()) s=min((*it)-(*(--tmp)),s);
    }
    a[fi].clear();
}
void solve(){
    cin>>n>>m;
    for (int q=0,i;q<n;++q){
        cin>>i;
        if (b.find(i)==b.end()){
            b[i]=len;
            a[len].insert(q);
            len++;
        }
        else {
            int bi=b[i];
            a[bi].insert(q);
            set<int>::iterator tmp=a[bi].find(q);
            tmp++;
            if (tmp!=a[bi].end()) ans=min((*tmp)-q,ans);
            tmp--;
            if (tmp!=a[bi].begin()) ans=min(q-(*(--tmp)),ans);
        }
    }
    for (int q=0,i,j;q<m;++q){
        cin>>i>>j;
        if (b.find(j)==b.end()){
            if (b.find(i)!=b.end()){
                b[j]=b[i];
                b.erase(i);
            }
            cout<<ans<<endl;
        }
        else {
            if (b.find(i)==b.end()){
                cout<<ans<<endl;
            }
            else {
                int bi=b[i],bj=b[j],s;
                merge(bi,bj,s);
                b.erase(i);
                ans=min(ans,s);
                cout<<ans<<endl;
            }
        }
    }
}
int main(){
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    solve();
    return 0;
}
