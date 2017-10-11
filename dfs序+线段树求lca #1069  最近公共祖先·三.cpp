/*
http://hihocoder.com/problemset/problem/1069?sid=1206976


*/
#include<bits/stdc++.h>
using namespace std;
#define LL int
#define INF 10000000
#define ID(i) (i+n_)
using namespace std;
const int max_n=2e5+10;
int n_,n;
struct data{
    int i,pos;
}a[max_n*8];//zkw线段树  从1开始标号

vector<int>b[max_n];
int nd[max_n],tail;//dfs序部分
int rnk[max_n];
int dep[max_n];

void init(){
    for (n_=1;n_<=(n*2+4);n_<<=1);
    for (int q=n_;q<(n_*2);++q)
        a[q].pos=q-n_,a[q].i=INF;
}
void tr(){
    for (int q=n_-1;q>0;--q)
        if (a[q<<1].i>a[q<<1|1].i)
            a[q]=a[q<<1|1];
    else a[q]=a[q<<1];
}
void find(int i,int j,int &pos){
	i=i+n_-1,j=j+n_+1;
	int s=INF;
	for (;i^j^1;i>>=1,j>>=1){
		if (!(i&0x1))	if (s>a[i+1].i) s=a[i+1].i,pos=a[i+1].pos;
		if (j&0x1)		if (s>a[j-1].i) s=a[j-1].i,pos=a[j-1].pos;
	}
}

void dfs(int i,int fa){
    nd[i]=tail,rnk[tail]=i;
    a[ID(tail)].i=dep[i];
    ++tail;
    int siz=b[i].size();
    for (int q=0;q<siz;++q)
        if (b[i][q]!=fa){
            dep[b[i][q]]=dep[i]+1;
            dfs(b[i][q],i);
            nd[i]=tail,rnk[tail]=i;
            a[ID(tail)].i=dep[i];
            ++tail;
        }
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
    cin>>n;
    for(int q=0,i,j;q<n;++q){
        i=read_string();
        j=read_string();
        b[i].push_back(j);
    }
    n=siz;
    tail=1;
    init();
    memset(dep,0,sizeof(dep));
    dfs(0,-1);
    tr();
    /*for (int q=n_+1;q<=n_+n*2;++q)
        cout<<nam[rnk[q-n_]]<<" , "<<endl;*/
    int m;
    cin>>m;
    for (int q=0,i,j;q<m;++q){
        i=read_string();
        j=read_string();
        int pos;
        if (nd[i]>nd[j]) swap(i,j);
        find(nd[i],nd[j],pos);
     // cout<<i<<" "<<j<<" "<<nd[i]<<" "<<nd[j]<<" "<<pos<<"aaaaaaa"<<endl;
        cout<<nam[rnk[pos]]<<endl;
    }
}
int main(){
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    solve();
    return 0;
}
