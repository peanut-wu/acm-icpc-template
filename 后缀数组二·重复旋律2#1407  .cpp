/*
……写完才发现字符集合太大了……怒换map
出现次数至少为两次的子串最长是多少
*/
#include<bits/stdc++.h>
using namespace std;
const int max_n=1e5;
const int char_size=1001;
map<int,int> tran[2*max_n+10];
int max_len[2*max_n],min_len[2*max_n];
int slink[2*max_n];
int nums[2*max_n];
int edges[2*max_n];
int min_endpos[2*max_n],max_endpos[2*max_n];

int sam_len;
int new_state(int _max_len,int _min_len,map<int,int> *_tran,int _slink){
    max_len[sam_len]=_max_len,min_len[sam_len]=_min_len,slink[sam_len]=_slink;
    if (_tran==NULL)
        tran[sam_len].clear();
    else
        for (map<int,int>::iterator q=(*_tran).begin();q!=(*_tran).end();++q)
            tran[sam_len][q->first]=q->second;
    return sam_len++;
}
int add_char(int i,int pos,int now){
    int next=new_state(max_len[now]+1,-1,NULL,-1);
    edges[next]=0,nums[next]=1,min_endpos[next]=pos,max_endpos[next]=pos;
    while (now!=-1 && tran[now].find(i)==tran[now].end()){
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
            int temp=new_state(max_len[now]+1,min_len[p],&tran[p],slink[p]);
            slink[p]=temp,min_len[p]=max_len[temp]+1;
            slink[next]=temp,min_len[next]=max_len[temp]+1;
            min_endpos[temp]=max_endpos[temp]=pos;
            edges[temp]=2;
            while (now!=-1&&tran[now].find(i)!=tran[now].end()&&tran[now][i]==p){
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
            min_endpos[slink[t]]=min(min_endpos[slink[t]],min_endpos[t]);
            max_endpos[slink[t]]=max(max_endpos[slink[t]],max_endpos[t]);
            if (!--edges[slink[t]]) que.push(slink[t]);
        }
    }
}

void sam(int *a,int n){
    sam_len=0;
    int st=new_state(0,0,NULL,-1);
    edges[st]=0;
    for (int q=0;q<n;++q)
        st=add_char(a[q],q,st);
    cal_endpos();
}
int a[max_n],n;
int main(){
    scanf("%d",&n);
    for (int q=0;q<n;++q) scanf("%d",&a[q]);
    sam(a,n);
    int ans=0;
    for (int q=1;q<sam_len;++q){
        int len=max_endpos[q]-min_endpos[q];
        if (len>=min_len[q]){
            ans=max(ans,min(len,max_len[q]));
        }
    }
    printf("%d",ans);
    return 0;
}


