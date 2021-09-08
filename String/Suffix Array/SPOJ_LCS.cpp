//https://www.spoj.com/problems/LCS/
#include <bits/stdc++.h>

using namespace std;
const int N = 6e5 + 5;
const int alpha = 128;

typedef long long ll;

int suff[N], newsuff[N], rnk[N], newrnk[N], head[N], nxt[N], bst[N];
int LCP[N];
char s[N];
int len;

void buildSuffix(){
    char *str = s;
    memset(head, -1, sizeof(head));
    for(len=0;!len || s[len-1];str++, len++){
        nxt[len]=head[*str];
        head[*str]=len;
        rnk[len]=*str;
    }
    int p=0;
    int b=-1;
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
        auto cmp = [cur](int a, int b){return (rnk[a]<rnk[b])|| (rnk[a]==rnk[b] && rnk[a+cur]<rnk[b+cur]);};
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


void builLCP(){
    int cur=0;
    LCP[0]=0;
    for(int i=0;s[i];i++){
        int j = suff[rnk[i]-1];
        while(s[j+cur]==s[i+cur])
            cur++;
        LCP[rnk[i]]=cur;
        if(cur)
            cur--;
    }
}

int sz;
int main(){
    scanf("%s",s);
    sz=strlen(s);
    scanf("%s", s+sz);
    buildSuffix();
    builLCP();
    int ans=0;
    for(int i=1;i<len;i++){
        if((suff[i]<sz)!=(suff[i-1]<sz)){
            ans=max(ans, LCP[i]);
        }
    }
    printf("%d\n", ans);
    return 0;
}
