//https://vjudge.net/problem/UVA-11107

#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
const int alpha = 256;

unsigned char s[N];
int n;
int suff[N], rnk[N], newrnk[N],len, newSuff[N], bst[N];
int LCP[N];

int pos[N];

void buildSuffix_N_logN(){
    int *head=newSuff, *nxt = newrnk;
    memset(head, -1, alpha*sizeof(head[0]));
    for(len=0;!len||s[len-1];++len){
        suff[len]=len;
        nxt[len] = head[s[len]];
        head[s[len]]=len;
    }
    int p=0, b=-1;

    for(int i=0;i<alpha;i++){
        if(head[i]==-1)
            continue;
        bst[++b]=p;

        for(int j=head[i];~j;j=nxt[j])
        {
            rnk[j]=b;
            suff[p++] = j;
        }
    }
    int cur=1;
    newrnk[0]=0;
    newSuff[0]=suff[0];
    do{
        auto cmp = [cur](int a , int b){return rnk[a]<rnk[b] || rnk[a]==rnk[b]&& rnk[a+cur]<rnk[b+cur];};

        for(int i=0;i<len;++i){
            int j = suff[i]-cur;
            if(j<0)
                continue;
            newSuff[bst[rnk[j]]++]=j;

        }
        for(int i=1;i<len;++i){
            suff[i] = newSuff[i];
            bool cmpres =  (cmp(suff[i-1], suff[i]));
            newrnk[i] = newrnk[i-1] + cmpres ;
            if(cmpres)
                bst[newrnk[i]]=i;
        }
        for(int i=0;i<len;++i){
            rnk[suff[i]] = newrnk[i];
        }
        cur<<=1;
    }while(newrnk[len-1]!=len-1);
}

void buildLCP(){
    int cnt=0;
    for(int i=0;s[i];++i){
        int j = suff[rnk[i]-1];
        while(s[i+cnt]==s[j+cnt])
            cnt++;
        LCP[rnk[i]] = cnt;
        if(cnt)
            cnt--;
    }

}

struct monotonicStack{
    stack<pair<int,int> > stk;
    void push(int x){
        stk.emplace(x, min(x,getMin()));
    }

    void pop(){
        stk.pop();
    }

    int top(){
        return stk.top().first;
    }

    bool empty(){
        return stk.empty();
    }

    int size(){
        return stk.size();
    }

    int getMin(){
        if(stk.empty())
            return INT_MAX;
        return stk.top().second;
    }
};

struct monotonicQueue{
    monotonicStack psh, pp;

    void move(){
        if(pp.empty()){
            while(psh.size()){
                pp.push(psh.top());
                psh.pop();
            }
        }
    }

    void push(int x){
        psh.push(x);
    }
    void pop(){
        move();
        pp.pop();
    }
    int top(){
        move();
        return pp.top();
    }
    bool empty(){
        return pp.empty() && psh.empty();
    }
    int size(){
        return psh.size()+pp.size();
    }

    int getMin(){
        return min(psh.getMin(), pp.getMin());
    }
};

int main()
{
    int tsts=0;
    while(1){
        scanf("%d",&n);
        if(!n)
            break;
        if(tsts++)
            puts("");
        char*str = (char*) s;
        int j=0;
        for(int i=0;i<n;i++){
            scanf("%s",str);
            while(*str){
                pos[j++]=i;
                str++;
            }
            pos[j++]=i;
            *str = i+128;
            str++;
        }
        if(n==1){
            *--str=0;
            printf("%s",s);
            continue;
        }
        *str=0;
        buildSuffix_N_logN();
        buildLCP();
        monotonicQueue mq;
        set<string> stt;
        int mx=0;
        int st=1, en=1, cnt=0;
        int freq[105]= {0};
        while(en<len){
            while(en<len && 2*cnt<=n){
                mq.push(LCP[en]);
                if(!freq[pos[suff[en++]]]++){
                    cnt++;
                }
            }

            if(2*cnt<=n)
                break;
            while(2*cnt>n){
                mq.pop();
                if(!--freq[pos[suff[st++]]]){
                    cnt--;
                }
            }
            if(mq.getMin()>mx){
                stt.clear();
                mx=mq.getMin();
            }
            if(mq.getMin()==mx &&mx){
                unsigned char c = s[suff[st]+mx];
                s[suff[st]+mx] = 0;
                stt.insert((char *)s+suff[st]);
                s[suff[st]+mx]=c;
            }
        }
        if(stt.empty()){
            puts("?");
        }else{
            for(auto & ss:stt){
                printf("%s\n", ss.c_str());
            }
        }
    }
    return 0;
}
