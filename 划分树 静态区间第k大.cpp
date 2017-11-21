/*Accepted
2665
655MS
15796K
1723 B
G++
http://acm.hdu.edu.cn/showproblem.php?pid=2665
*/
#include<bits/stdc++.h>
#define log_max_n 27
using namespace std;
const int max_n=100000+10;

int bit[log_max_n][max_n],cnt[log_max_n][max_n];
int a[max_n];
void build(int i,int l,int r){
	int mid=(l+r)>>1,lson=l,rson=mid+1,midval=a[mid],equ=mid-l+1;
    for (int q=l;q<=r;++q) equ-=(bit[i][q]<midval);
	if (bit[i][l]<midval)
        bit[i+1][lson++]=bit[i][l],cnt[i][l]=1;
    else if (bit[i][l]==midval)
            bit[i+1][lson++]=bit[i][l],cnt[i][l]=1,--equ;
    else bit[i+1][rson++]=bit[i][l],cnt[i][l]=0;

	for (int q=l+1;q<=r;++q)
		if (bit[i][q]<midval)
			bit[i+1][lson++]=bit[i][q],cnt[i][q]=cnt[i][q-1]+1;
		else if (bit[i][q]==midval&&equ)
            bit[i+1][lson++]=bit[i][q],cnt[i][q]=cnt[i][q-1]+1,--equ;
        else bit[i+1][rson++]=bit[i][q],cnt[i][q]=cnt[i][q-1];
	if (mid>l)  build(i+1,l,mid);
	if (r>mid+1)build(i+1,mid+1,r);
}
int query(int i,int L,int R,int l,int r,int k){
	if (l==r)		return bit[i][l];
	int MID=(L+R)>>1;
	int LL=(l==L?0:cnt[i][l-1]),LR=(l-L)-LL;
	int RL=cnt[i][r],RR=(r-L+1)-RL;
    if (k<(RL-LL))
        return query(i+1,L,MID,L+LL,L+RL-1,k);
    else return query(i+1,MID+1,R,MID+1+LR,MID+1+RR-1,k-(RL-LL));
}
void solve(){
	int n,m;
	//cin>>n>>m;
	scanf("%d%d",&n,&m);
	for (int q=0;q<n;++q){
        scanf("%d",&a[q]);
		//cin>>a[q];
		bit[0][q]=a[q];
	}
	sort(a,a+n,less<int>());
	build(0,0,n-1);
	for (int q=0,i,j,k;q<m;++q){
		//cin>>i>>j>>k;
		//cout<<query(0,0,n-1,i-1,j-1,k-1)<<endl;
		scanf("%d%d%d",&i,&j,&k);
        printf("%d\n",query(0,0,n-1,i-1,j-1,k-1));
	}
}
int main(){
	//cin.sync_with_stdio(false);cout.sync_with_stdio(false);
	int t;//cin>>t;
	scanf("%d",&t);
	while (t--)solve();
	return 0;
}
