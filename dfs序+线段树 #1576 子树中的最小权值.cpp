/*

http://hihocoder.com/problemset/problem/1576?sid=1204682
1576 子树中的最小权值 AC  G++ 829ms 32MB Leslie

*/

#include<bits/stdc++.h>
using namespace std;
#define ID(l,r) (l+r|l!=r)//传说中的二倍空间线段树,又一个鸡肋……
#define N 300005
#define LL long long
using namespace std;
LL a[N*2],mark[N*2],n;//线段树部分
bool marked[N*2];

vector<int>b[N];
int st[N],nd[N],tail;//dfs序部分
bool visited[N];
int val[N];

void tr(int l,int r){
	if (l==r){  marked[ID(l,r)]=false;  return ;}
	int mid=(l+r)>>1;
	tr(l,mid);
	tr(mid+1,r);
	marked[ID(l,r)]=false;
	a[ID(l,r)]=min(a[ID(l,mid)],a[ID(mid+1,r)]);
}

void pushdown(int l,int r){
	int mid=(l+r)>>1;
	if (marked[ID(l,r)]){
		mark[ID(l,mid)]=mark[ID(mid+1,r)]=mark[ID(l,r)];
		a[ID(l,mid)]=mark[ID(l,mid)]*(mid-l+1);
		a[ID(mid+1,r)]=mark[ID(mid+1,r)]*(r-mid);
		marked[ID(l,r)]=false;
	}
}

void chg(int l,int r,int i,int j,int k){
	int mid=(l+r)>>1;
	if (l==i&&r==j){
		mark[ID(l,r)]=k;marked[ID(l,r)]=true;
		a[ID(l,r)]=(r-l+1)*k;
		return;
	}
	pushdown(l,r);
	if (mid<i){
		chg(mid+1,r,i,j,k);
	}
	else if (mid>=j){
		chg(l,mid,i,j,k);
	}
	else {
		chg(l,mid,i,mid,k);chg(mid+1,r,mid+1,j,k);
	}
	a[ID(l,r)]=min(a[ID(l,mid)],a[ID(mid+1,r)]);//push up
}
LL find(int l,int r,int i,int j){
	int mid=(l+r)>>1;
	if (l==i&&r==j){
		return a[ID(l,r)];
	}
	pushdown(l,r);
	if (mid<i){
		return find(mid+1,r,i,j);
	}
	if (mid>=j){
		return find(l,mid,i,j);
	}
	return min(find(l,mid,i,mid),find(mid+1,r,mid+1,j));
}

void dfs(int i){
    visited[i]=true;
    st[i]=tail;
    a[ID(tail,tail)]=val[i];//来自二倍空间线段树导致的耦合
    ++tail;
    int siz=b[i].size();
    for (int q=0;q<siz;++q)
        if (!visited[b[i][q]]){
            dfs(b[i][q]);
        }
    nd[i]=tail;
    a[ID(tail,tail)]=val[i];
    ++tail;//来自二倍空间线段树导致的耦合
}
void solve(){
    cin>>n;
    for (int q=1;q<=n;q++){
        cin>>val[q];
    }
    for (int q=2,i;q<=n;++q){
        cin>>i;
        b[i].push_back(q);
    }
    tail=0;
    memset(visited,0,sizeof(bool)*(n+1));
    dfs(1);
    tr(0,tail-1);
    int m;
    cin>>m;
    for (int q=0,i,j;q<m;++q){
        cin>>i;
        if (i==1){
            cin>>i>>j;
            chg(0,tail-1,st[i],st[i],j);
            chg(0,tail-1,nd[i],nd[i],j);
        }
        else {
            cin>>j;
            cout<<find(0,tail-1,st[j],nd[j])<<endl;
        }
    }

}
int main(){
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    solve();
    return 0;
}
