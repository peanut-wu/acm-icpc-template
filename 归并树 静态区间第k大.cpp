#include<bits/stdc++.h>
#define log_max_n 23
using namespace std;
const int max_n=1e5+10;

int bit[log_max_n][max_n];
int a[max_n],n,m,mmin,mmax;

int merge(int l,int mid,int r){
	static int tmp[max_n];
	int lson=l,rson=mid+1,k=l;
	for (;lson<=mid&&rson<=r;)
		if (a[lson]<=a[rson])
			tmp[k++]=a[lson++];
		else tmp[k++]=a[rson++];
	for (;lson<=mid;)
		tmp[k++]=a[lson++];
	for (;rson<=r;)
		tmp[k++]=a[rson++];
	for (k=l;k<=r;++k)
		a[k]=tmp[k];
}
void build(int i,int l,int r){
	int mid=(l+r)>>1;
	if(l<r){
		build(i+1,l,mid);
		build(i+1,mid+1,r);
		merge(l,mid,r);
	}
	for (int q=l;q<=r;++q)
        bit[i][q]=a[q];
}
int query1(int i,int L,int R,int l,int r,int t){
   // cout<<i<<" "<<l<<" "<<r<<endl;
	if (L==l&&R==r)		return lower_bound(bit[i]+l,bit[i]+r+1,t)-bit[i]-l;
	int MID=(L+R)>>1;
	if (l>MID)  return query1(i+1,MID+1,R,l,r,t);
    if (r<=MID) return query1(i+1,L,MID,l,r,t);
    return  query1(i+1,MID+1,R,MID+1,r,t)+query1(i+1,L,MID,l,MID,t);
}
int query(int l,int r,int k){
   // return query1(0,0,n-1,l,r,k);
    int L=mmin,R=mmax,ans=0;
    for (;L<=R;){
        int mid=(L+R)>>1,kk=query1(0,0,n-1,l,r,mid);
        if (kk<=k){
            if (query1(0,0,n-1,l,r,mid+1)>=k)  ans=mid;
            L=mid+1;
        }
        else R=mid-1;
    }
    return ans;
}
void solve(){
    cin>>n>>m;
    cin>>a[0];mmin=a[0],mmax=a[0];
	for (int q=1;q<n;++q){
		cin>>a[q];mmin=min(mmin,a[q]);mmax=max(mmax,a[q]);
	}
	build(0,0,n-1);
	for (int q=0,i,j,k;q<m;++q){
		cin>>i>>j>>k;
		cout<<query(i-1,j-1,k-1)<<endl;
	}
}
int main(){
	cin.sync_with_stdio(false);cout.sync_with_stdio(false);
	int t; cin>>t;
	while (t--)solve();
	return 0;
}
