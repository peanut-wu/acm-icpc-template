/*
	两字符串的最长公共子串
*/
#include<bits/stdc++.h>
using namespace std;
const int max_n=1e5+10;
const int char_size=26;
int tran[2*max_n+10][char_size];
int slink[2*max_n+10];
int max_len[2*max_n+10],min_len[2*max_n+10];
int sam_len;

int new_state(int _max_len,int _min_len,int * _tran,int _slink){
    max_len[sam_len]=_max_len,min_len[sam_len]=_min_len,slink[sam_len]=_slink;
    if (_tran==NULL)
        for (int q=0;q<char_size;++q) tran[sam_len][q]=-1;
    else
        for (int q=0;q<char_size;++q) tran[sam_len][q]=_tran[q];
    return sam_len++;
}

int add_char(char i,int now){
    int c=i-'a';
    int next=new_state(max_len[now]+1,-1,NULL,-1);
    while (now!=-1&&tran[now][c]==-1){
        tran[now][c]=next;
        now=slink[now];
    }
    if (now==-1){
        slink[next]=0,min_len[next]=1;
        return next;
    }
    else {
        int p=tran[now][c];
        if (max_len[p]==max_len[now]+1){
            slink[next]=p,min_len[next]=max_len[p]+1;
            return next;
        }
        else {
            int temp=new_state(max_len[now]+1,min_len[p],tran[p],slink[p]);
            slink[p]=temp,min_len[p]=max_len[temp]+1;
            slink[next]=temp,min_len[next]=max_len[temp]+1;
            while (now!=-1 && tran[now][c]==p){
                tran[now][c]=temp;
                now=slink[now];
            }
            return next;
        }
    }
}

void sam(char *a,int len){
    sam_len=0;
    int st=new_state(0,0,NULL,-1);
    for (int q=0;q<len;++q)
        st=add_char(a[q],st);
}

char a[max_n],b[max_n];
int main(){
    scanf("%s%s",a,b);
    sam(a,strlen(a));
    int ans=0,st=0,i=0;
    for (int q=0,len=strlen(b),c;q<len;++q){
        c=b[q]-'a';
        if (tran[st][c]!=-1){
            ++i,st=tran[st][c];
        }
        else {
            while (st!=-1 &&tran[st][c]==-1)
                st=slink[st];
            if (st==-1){
                st=0,i=0;
            }
            else {
                i=max_len[st]+1;
                st=tran[st][c];
            }
        }
        ans=max(i,ans);
    }
    printf("%d",ans);
    return 0;
}
