/*
http://hihocoder.com/problemset/problem/1445?sid=1161410
1445 后缀自动机二·重复旋律5
AC
G++
993ms
208MB
不同子串数目
*/
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int max_n=1e6+10;
const int char_size=26;//字符集合大小

int slink[2*max_n+10];
int tran[2*max_n+10][char_size];
int max_len[2*max_n+10],min_len[2*max_n+10];
int sam_len=0;


int new_state(int _max_len,int _min_len,int *_tran,int _slink){
    slink[sam_len]=_slink;
    if (_tran==NULL)
        for (int q=0;q<char_size;++q) tran[sam_len][q]=-1;
    else
        for (int q=0;q<char_size;++q) tran[sam_len][q]=_tran[q];
    max_len[sam_len]=_max_len,min_len[sam_len]=_min_len;
    return sam_len++;
}

int add_char(char i,int _now){
    int _next=new_state(max_len[_now]+1,0,NULL,-1);
    int c=i-'a';
    while (_now!=-1 && tran[_now][c]==-1){
        tran[_now][c]=_next;
        _now=slink[_now];
    }
    if (_now==-1){
        slink[_next]=0,min_len[_next]=1;
        return _next;
    }
    else {
        int p= tran[_now][c];
        if (max_len[p]==max_len[_now]+1){
            min_len[_next]=max_len[p]+1;
            slink[_next]=p;
            return _next;
        }
        else {
            int _temp=new_state(max_len[_now]+1,min_len[_now]+1,tran[p],slink[p]);
            slink[p]=_temp,min_len[p]=max_len[_temp]+1;
            slink[_next]=_temp,min_len[_next]=max_len[_temp]+1;
            min_len[_temp]=max_len[slink[_temp]]+1;
            while (_now!=-1 && tran[_now][c]==p){
                tran[_now][c]=_temp;
                _now=slink[_now];
            }
            return _next;
        }
    }

}
void SAM(char *s){
    sam_len=0;
    int now=new_state(0,0,NULL,-1);
    int str_len=strlen(s);
    for (int q=0;q<str_len;++q){
        now=add_char(s[q],now);
    }
}


char s[max_n];
int main(){
    scanf("%s",s);
    SAM(s);
    long long ans=0;
    for (int q=1;q<sam_len;++q) ans+=max_len[q]-min_len[q]+1;
    cout<<ans;
    return 0;
}
