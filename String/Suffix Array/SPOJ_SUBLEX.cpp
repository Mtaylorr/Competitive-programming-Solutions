//https://www.spoj.com/problems/SUBLEX/

#include <bits/stdc++.h>

using namespace std;
const int N = 3e5 + 5;
const int alpha = 128;

typedef long long ll;

int suff[N], newsuff[N], rnk[N], newrnk[N], nxt[N], head[alpha+2];
char s[N];
int len;
int bst[N];
int LCP[N];

void buildSuffix(){
    char *str =s;
    memset(head, -1, sizeof(head));
    for(len=0;!len || s[len-1];len++,str++){
        nxt[len]=head[*str];
        head[*str]=len;
        rnk[len]=*str;
    }
    int b=-1;
    int p=0;
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
        auto cmp =  [cur](int a, int b){return (rnk[a]<rnk[b]) ||(rnk[a]==rnk[b] && rnk[a+cur]<rnk[b+cur]);};
        for(int i=0;i<len;i++){
            int j=suff[i]-cur;
            if(j<0)
                continue;
            newsuff[bst[rnk[j]]++]=j;
        }
        for(int i=1;i<len;i++){
            suff[i]=newsuff[i];
            int diff  = cmp(suff[i-1], suff[i]);
            newrnk[i]=newrnk[i-1] + diff;
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
        while(s[j+cur]==s[i+cur])
            cur++;
        LCP[rnk[i]]=cur;
        if(cur)
            --cur;
    }
}


int t;
int q,x;
ll kth[N];

int main(){
    freopen("input.txt", "r", stdin);
    scanf("%s",s);
    buildSuffix();
    buildLCP();
    ll cur=0;
    for(int i=1;i<len;i++){
        int sz = len-1-suff[i];
        kth[i]=cur+1;
        cur+=sz-LCP[i];
    }
    scanf("%d",&q);
    while(q--){
        scanf("%d",&x);
        int p = lower_bound(kth, kth+len, x+1) - kth;
        p--;
        int l = suff[p];
        int r = suff[p] + LCP[p] + x-kth[p];
        for(int i=l;i<=r;i++){
            printf("%c" ,s[i]);
        }
        puts("");
    }
    return 0;
}
