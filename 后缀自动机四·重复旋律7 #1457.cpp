/*
但是所有的作品有一个共同特征：只用了十个音符，所有的音符都表示成0-9的数字。
现在小Hi想知道这部作品中所有不同的旋律的“和”（也就是把串看成数字，在十进制下的求和，允许有前导0）。答案有可能很大，我们需要对（10^9 + 7)取摸。

*/
#include<bits/stdc++.h>
using namespace std;
const int max_n=2e6+10;
const int char_size=11;
int tran[max_n*2+10][char_size];
int slink[max_n*2+10];
int max_len[max_n*2+10],min_len[max_n*2+10];
int edges[max_n*2+10];
int nums[max_n*2+10];
char prevs[max_n*2+10];
int sam_len;

long long ans[max_n];
const int mod=1e9+7;
int new_state(int _max_len,int _min_len,int *_tran,int _slink){
    sam_len[max_len]=_max_len,sam_len[min_len]=_min_len,sam_len[slink]=_slink;
    if (_tran==NULL)
        for (int q=0;q<char_size;++q)   tran[sam_len][q]=-1;
    else
        for (int q=0;q<char_size;++q)   tran[sam_len][q]=_tran[q];
    return sam_len++;
}
int add_char(char i,int now){
    int c=i-'0';
    int next=new_state(now[max_len]+1,-1,NULL,-1);
    edges[next]=0;
    prevs[next]=i;
    while (now!=-1 && tran[now][c]==-1){
        tran[now][c]=next;
        edges[next]++;
        now=slink[now];
    }
    if (now==-1){
        next[min_len]=1,next[slink]=0;
        return next;
    }
    else {
        int p=tran[now][c];
        if (p[max_len]==now[max_len]+1){
            next[min_len]=p[max_len]+1,next[slink]=p;
            return next;
        }
        else {
            int temp=new_state(now[max_len]+1,p[min_len],tran[p],slink[p]);
            p[slink]=temp,p[min_len]=temp[max_len]+1;
            next[slink]=temp,next[min_len]=temp[max_len]+1;
            edges[temp]=0;
            prevs[temp]=prevs[p];
            for (int q=0;q<char_size;++q)
                if (tran[temp][q]!=-1)
                    edges[tran[temp][q]]++;
            while (now!=-1 && tran[now][c]==p){
                tran[now][c]=temp;
                edges[temp]++,edges[p]--;
                now=now[slink];
            }
            return next;
        }
    }
}
long long bfs(){
    queue<int>que;
    for (;!que.empty();) que.pop();
    que.push(0);
    memset(ans,0,sizeof(int)*sam_len);
    memset(nums,0,sizeof(int)*sam_len);
    nums[0]=1;
    prevs[0]='0';
    long long sum=0;
    for (;!que.empty();){
        int t=que.front();
        if (prevs[t]==':')  ans[t]=nums[t]=0;
        ans[t]+=(nums[t]*((int)prevs[t]-'0'));
        sum+=ans[t];
        sum%=mod;
        que.pop();
        for (int q=0;q<char_size;++q)
            if (tran[t][q]!=-1){
                if (q!=10){
                    ans[tran[t][q]]+=(ans[t]*10);
                    nums[tran[t][q]]+=nums[t];
                    ans[tran[t][q]]%=mod;
                }
                //cout<<tran[t][q]<<"  "<<edges[tran[t][q]]<<"   ,";
                if (!(--edges[tran[t][q]])){
                    que.push(tran[t][q]);
                }
            }//cout<<endl;

          //  cout<<endl;
    }
   // cout<<ans[3]<<" "<<min_len[2]<<" "<<(int)prev[2]<<endl;
    return sum;
}
char a[max_n];
void sam(){
    int n;
    scanf("%d",&n);
    sam_len=0;
    int state=new_state(0,0,NULL,-1);
    for (int q=0;q<n;++q){
        scanf("%s",a);
        //cout<<a<<endl;
        for (int p=0,len=strlen(a);p<len;++p)
            state=add_char(a[p],state);
        state=add_char(':',state);
    }
    cout<<bfs();
}

int main(){
    sam();
    return 0;
}
