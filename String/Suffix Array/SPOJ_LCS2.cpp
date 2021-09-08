//https://www.spoj.com/problems/LCS2/
#include <bits/stdc++.h>

using namespace std;
const int N = 1e6 + 1e5;
const int alpha = 256;

typedef long long ll;

int suff[N], newsuff[N], rnk[N], newrnk[N], nxt[N], head[alpha], bst[N];
int LCP[N];
char s[N];
int len;

void buildSuffix(){
    len=0;
    memset(head, -1, sizeof(head));
    char *str=s;
    for(len=0; !len || s[len-1];len++, str++){
        nxt[len]=head[*str];
        head[*str]=len;
        rnk[len]=*str;
    }
    int b=-1, p=0;
    for(int i=0;i<alpha;i++){
        if(head[i]==-1)
            continue;
        bst[++b]=p;
        for(int j=head[i];j!=-1;j=nxt[j]){
            rnk[j]=b;
            suff[p++]=j;
        }
    }
    newrnk[0]=0;
    newsuff[0]=suff[0];
    int cur=1;
    do{
        auto cmp  = [cur](int a, int b){return (rnk[a]<rnk[b]) || (rnk[a]==rnk[b] && rnk[a+cur]<rnk[b+cur]);};
        for(int i=0;i<len;i++){
            int j=suff[i]-cur;
            if(j<0)
                continue;
            newsuff[bst[rnk[j]]++]=j;
        }
        for(int i=1;i<len;i++){
            suff[i]=newsuff[i];
            int diff = cmp(suff[i-1], suff[i]);
            newrnk[i]=newrnk[i-1]+diff;
            if(diff)
                bst[newrnk[i]]=i;
        }
        for(int i=0;i<len;i++){
            rnk[suff[i]]=newrnk[i];
        }
        cur*=2;
    }while(newrnk[len-1]!=len-1);

}

void buildLCP(){
    int cur=0;
    LCP[0]=0;
    for(int i=0;s[i];i++){
        int j = suff[rnk[i]-1];
        while(s[i+cur]==s[j+cur])
            cur++;
        LCP[rnk[i]]=cur;
        if(cur)
            --cur;
    }
}

deque<pair<int,int> > mq;
int id[N];
int sz=0;
int nb=0;
int cnt[N];
int cn=0;

void add(int ind){
    cnt[id[suff[ind]]]++;
    cn+=(cnt[id[suff[ind]]]==1);
    while((!mq.empty() )&& mq.back().first>=LCP[ind]){
        mq.pop_back();
    }
    mq.push_back({LCP[ind], ind});
}

void rem(int ind){
    cnt[id[suff[ind]]]--;
    while((!mq.empty()) && mq.front().second<=ind+1)
        mq.pop_front();
}

int main(){
    freopen("input.txt", "r", stdin);
    int cur=0;
    char *str = s;
    while(~scanf("%s",s+cur)){
        while(*str){
            str++;
            sz++;
        }
        s[sz]='0'+nb;
        for(int j=cur;s[j];j++)
            id[j]=nb;
        nb++;
        cur = sz+1;
    }
    buildSuffix();
    buildLCP();
    int l=1;
    int ans=0;
    cnt[id[suff[1]]]++;
    cn=1;
    for(int r=2;r<len;r++){
        add(r);
        while(cn==nb){
            if(cnt[id[suff[l]]]==1)
                break;
            rem(l++);
        }
        if(cn==nb)
            ans=max(ans, mq.front().first);
    }
    printf("%d",ans);
    return 0;
}
