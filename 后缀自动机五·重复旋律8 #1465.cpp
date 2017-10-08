
/*
 字符串B（重复便多次计）和给定串A是“循环相似”的匹配数目
*/
#include<bits/stdc++.h>
using namespace std;
const int max_n=1e5+10;
const int char_size=26;
int max_len[max_n*2+10],min_len[max_n*2+10];
int slink[max_n*2+10];
int tran[max_n*2+10][char_size];
int sam_len;

int nums[max_n*2+10];
int t_edges[max_n*2+10];

int new_state(int _max_len,int _min_len,int *_tran,int _slink){
    max_len[sam_len]=_max_len,min_len[sam_len]=_min_len,slink[sam_len]=_slink;
    if (_tran==NULL)
        for (int q=0;q<char_size;++q)   tran[sam_len][q]=-1;
    else
        for (int q=0;q<char_size;++q)   tran[sam_len][q]=_tran[q];
    return sam_len++;
}
int add_char(char i,int now){
    int next=new_state(max_len[now]+1,-1,NULL,-1);
    int c=i-'a';
    nums[next]=1;

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
            min_len[next]=max_len[p]+1,slink[next]=p;
            t_edges[p]++;
            return next;
        }
        else {
            int temp=new_state(max_len[now]+1,min_len[p],tran[p],slink[p]);
            slink[p]=temp,min_len[p]=max_len[temp]+1;
            slink[next]=temp,min_len[next]=max_len[temp]+1;
            t_edges[temp]=2;
            while (now!=-1 && tran[now][c]==p){
                tran[now][c]=temp;
                now=slink[now];
            }
            return next;
        }
    }
}

void bfs(){
    queue<int>que;
    while (!que.empty())que.pop();
    for (int q=1;q<sam_len;++q)
        if (!t_edges[q])
            que.push(q);
    while (!que.empty()){
        int t=que.front();
        que.pop();
        if (slink[t]!=-1){
            nums[slink[t]]+=nums[t];
            if (!(--t_edges[slink[t]]))
                que.push(slink[t]);
        }
    }
}
void sam(char *a,int len){
    sam_len=0;
    int st=new_state(0,0,NULL,-1);
    for (int q=0;q<len;++q)
        st=add_char(a[q],st);
    bfs();
}
char a[max_n];
bool exist[max_n*2+10];
int main(){
    scanf("%s",a);
    sam(a,strlen(a));
    int n;
    scanf("%d",&n);
    while (n--){
        scanf("%s",a);
        memset(exist,0,sizeof(bool)*(sam_len+1));
        int len=strlen(a),st=0,matchlen=0,ans=0;
        for (int p=0;p<2;++p)
            for (int q=0,c;q<len;++q){
                c=a[q]-'a';
             //   cout<<"aaa :"<<st<<" "<<matchlen<<endl;
                if (tran[st][c]!=-1){
                    matchlen++;
                    st=tran[st][c];
                    if (matchlen>=len){
                        while (slink[st]!=-1 && max_len[slink[st]]>=len) st=slink[st];
                        if (!exist[st])  exist[st]=true,ans+=nums[st];
                        matchlen=max_len[st];
                    }
                }
                else{
                    while (st!=-1 &&tran[st][c]==-1)
                        st=slink[st];
                    if (st==-1) matchlen=0,st=0;
                    else {
                        matchlen=max_len[st]+1;
                        st=tran[st][c];
                        if (matchlen>=len){
                            while (slink[st]!=-1 && max_len[slink[st]]>=len) st=slink[st];
                            if (!exist[st])  exist[st]=true,ans+=nums[st];
                            matchlen=max_len[st];
                        }
                    }
                }
            }
        printf("%d\n",ans);
    }
    return 0;
}

