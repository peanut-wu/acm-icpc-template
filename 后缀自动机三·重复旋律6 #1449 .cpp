/*
http://hihocoder.com/problemset/submitted
后缀自动机三·重复旋律6
AC
G++
1261ms
188MB
*/
#include<bits/stdc++.h>
using namespace std;
const int max_n=1e6+10;
const int char_size=26;
int tran[2*max_n+10][char_size];
int slink[2*max_n+10];
int max_len[2*max_n+10],min_len[2*max_n+10];

int edges[2*max_n+10];
int nums[2*max_n+10];
int add[2*max_n+10];
int sam_len;

int new_state(int _max_len,int _min_len,int *_tran,int _slink){
    max_len[sam_len]=_max_len,min_len[sam_len]=_min_len,slink[sam_len]=_slink;
    if (_tran==NULL)
        for (int q=0;q<char_size;++q)   tran[sam_len][q]=-1;
    else
        for (int q=0;q<char_size;++q)   tran[sam_len][q]=_tran[q];
    return sam_len++;
}
int add_char(char i,int _now){
    int next=new_state(max_len[_now]+1,-1,NULL,-1);
    int c=i-'a';
    edges[next]=0;
    add[next]=1;
    while (_now!=-1&&tran[_now][c]==-1){
        tran[_now][c]=next;
        _now=slink[_now];
    }
    if (_now==-1){
        min_len[next]=1,slink[next]=0;
        return next;
    }
    else {
        int p=tran[_now][c];
        if (max_len[p]==max_len[_now]+1){
            slink[next]=p,min_len[next]=max_len[p]+1;
            edges[p]++;
            return next;
        }
        else {
            int temp=new_state(max_len[_now]+1,min_len[p],tran[p],slink[p]);
            slink[p]=temp,min_len[p]=max_len[temp]+1;
            slink[next]=temp,min_len[next]=max_len[temp]+1;
            edges[temp]=2;
            while (_now!=-1 && tran[_now][c]==p){
                tran[_now][c]=temp;
                _now=slink[_now];
            }
            return next;
        }
    }
}
void cal_endpos(){
    queue<int> que;
    while (!que.empty()) que.pop();
    for (int q=1;q<sam_len;++q)
        if (!edges[q])
            que.push(q);

    while (!que.empty()){
        int t=que.front();
        nums[t]+=add[t];
        que.pop();
        if (slink[t]!=-1){
            if (!--edges[slink[t]])
                que.push(slink[t]);
            nums[slink[t]]+=nums[t];
        }
    }
}

char s[max_n];
int n;
int ans[max_n];
void sam(char *s){
    sam_len=0;
    n=strlen(s);
    int st=new_state(0,0,NULL,-1);
    nums[st]=1;
    for (int q=0;q<n;++q)
        st=add_char(s[q],st);
    cal_endpos();
}


int main(){
    scanf("%s",s);
    sam(s);
    for (int q=0;q<sam_len;++q) ans[max_len[q]]=max(ans[max_len[q]],nums[q]);
    for (int q=n-1,mm=0;q>0;--q) mm=ans[q]=max(ans[q],mm);

    for (int q=1;q<=n;++q)
        printf("%d\n",ans[q]);
    return 0;
}

/*暴力版本：
int add_char(char i,int _now){
    int next=new_state(max_len[_now]+1,-1,NULL,-1);
    int c=i-'a';
    nums[next]=1;
    while (_now!=-1&&tran[_now][c]==-1){
        tran[_now][c]=next;
        _now=slink[_now];
    }
    if (_now==-1){
        min_len[next]=1,slink[next]=0;
        return next;
    }
    else {
        int p=tran[_now][c];
        if (max_len[p]==max_len[_now]+1){
            slink[next]=p,min_len[next]=max_len[p]+1;
            while (p!=-1){
                nums[p]++;
                p=slink[p];
            }
            return next;
        }
        else {
            int temp=new_state(max_len[_now]+1,min_len[p],tran[p],slink[p]);
            slink[p]=temp,min_len[p]=max_len[temp]+1;
            slink[next]=temp,min_len[next]=max_len[temp]+1;
            nums[temp]=nums[p];
            while (_now!=-1 && tran[_now][c]==p){
                tran[_now][c]=temp;
                _now=slink[_now];
            }
            while (temp!=-1){
                nums[temp]++;
                temp=slink[temp];
            }
            return next;
        }
    }
}
*/
