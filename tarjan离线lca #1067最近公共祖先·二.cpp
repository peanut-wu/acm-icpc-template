/*
http://hihocoder.com/problemset/problem/1067
tarjan����lca
���鼯Ⱦɫ+dfs
*/

#include<bits/stdc++.h>
using namespace std;
const int max_n=1e5+10;
const int max_m=1e5+10;
int f[max_n];//���鼯
vector<int>a[max_n];//��
int cols[max_n];//Ⱦɫ
struct Q{
    int to;
    int num;
};
vector<Q>b[max_n];//ѯ��
struct P{
    int ans;
    bool solve;
}lca[max_m];//ѯ�ʴ�;

int n;
int find_set(int i){
    return f[i]==i?i:f[i]=find_set(f[i]);
}
void merge_set(int i,int j){
    int fi=find_set(i),fj=find_set(j);
    f[fi]=fj;
}
void init(){
    for (int q=0;q<=n;++q)  cols[q]=0,f[q]=q;
}
void dfs(int i,int fa){
    cols[i]=1;//�����︳ֵ1 ��������Q�����ѯ�ʵ����
    int Qsize=b[i].size();
    for (int q=0;q<Qsize;++q)
        if (!lca[b[i][q].num].solve){
            if (cols[b[i][q].to]==1)
                lca[b[i][q].num].ans=b[i][q].to,  lca[b[i][q].num].solve=true;
            else if (cols[b[i][q].to]==2)
                    lca[b[i][q].num].ans=find_set(b[i][q].to),  lca[b[i][q].num].solve=true;
        }
    int Ssize=a[i].size();
    for (int q=0;q<Ssize;++q)
        if (a[i][q]!=fa){
            dfs(a[i][q],i);
            merge_set(a[i][q],i);
        }
    cols[i]=2;
}


string nam[max_n];
map<string,int> rname;
map<string,int>::iterator it;
int siz;
int read_string(){
    string tmp;
    cin>>tmp;
    it=rname.find(tmp);
    if (it==rname.end()){
        rname[tmp]=siz;
        nam[siz]=tmp;
        return siz++;
    }
    else return it->second;
}
void solve(){
    siz=0;
    rname.clear();
    string tmp;
    cin>>n;
    for(int q=0,i,j;q<n;++q){
        i=read_string();
        j=read_string();
        a[i].push_back(j);
    }
    int m;
    cin>>m;
    for (int q=0,i,j;q<m;++q){
        i=read_string();
        j=read_string();
        Q tmp;
        tmp.num=q;
        tmp.to=i;b[j].push_back(tmp);
        tmp.to=j;b[i].push_back(tmp);
        lca[q].solve=false;
    }
    n=siz;
    init();
    dfs(0,-1);
    for (int q=0;q<m;++q)
        cout<<nam[lca[q].ans]<<endl;
}
int main(){
    solve();

    return 0;
}
