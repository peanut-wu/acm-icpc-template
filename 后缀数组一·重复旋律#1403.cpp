/*
出现次数至少为K次的子串最长是多少
*/
#include<bits/stdc++.h>
using namespace std;
const int max_n=2e4;
const int char_size=101;
int tran[2*max_n+10][char_size];
int max_len[2*max_n],min_len[2*max_n];
int slink[2*max_n];
int nums[2*max_n];
int edges[2*max_n];
int sam_len;
int new_state(int _max_len,int _min_len,int* _tran,int _slink){
    max_len[sam_len]=_max_len,min_len[sam_len]=_min_len,slink[sam_len]=_slink;
    if (_tran==NULL)
        for (int q=0;q<char_size;++q)   tran[sam_len][q]=-1;
    else
        for (int q=0;q<char_size;++q)   tran[sam_len][q]=_tran[q];
    return sam_len++;
}
int add_char(int i,int now){
    int next=new_state(max_len[now]+1,-1,NULL,-1);
    edges[next]=0,nums[next]=1;
    while (now!=-1 && tran[now][i]==-1){
        tran[now][i]=next;
        now=slink[now];
    }
    if (now==-1){
        slink[next]=0,min_len[next]=1;
        return next;
    }
    else {
        int p=tran[now][i];
        if (max_len[p]==max_len[now]+1){
            slink[next]=p,min_len[next]=max_len[p]+1;
            edges[p]++;
            return next;
        }
        else {
            int temp=new_state(max_len[now]+1,min_len[p],tran[p],slink[p]);
            slink[p]=temp,min_len[p]=max_len[temp]+1;
            slink[next]=temp,min_len[next]=max_len[temp]+1;
            edges[temp]=2;
            while (now!=-1&&tran[now][i]==p){
                tran[now][i]=temp;
                now=slink[now];
            }
            return next;
        }

    }
}
void cal_endpos(){
    queue<int>que;
    while (!que.empty()) que.pop();
    for (int q=1;q<sam_len;++q)
        if (!edges[q])
            que.push(q);
    while (!que.empty()){
        int t=que.front();
        que.pop();
        if (slink[t]!=-1){
            nums[slink[t]]+=nums[t];
            if (!--edges[slink[t]]) que.push(slink[t]);
        }
    }
}

void sam(int *a,int n){
    sam_len=0;
    int st=new_state(0,0,NULL,-1);
    edges[st]=0;
    for (int q=0;q<n;++q)
        st=add_char(a[q],st);
    cal_endpos();
}
int a[max_n],n,k;
int main(){
    scanf("%d%d",&n,&k);
    for (int q=0;q<n;++q) scanf("%d",&a[q]);
    sam(a,n);
    int ans=0;
    for (int q=1;q<sam_len;++q)
        if (nums[q]>=k)
            ans=max(ans,max_len[q]);
    printf("%d",ans);
    return 0;
}

